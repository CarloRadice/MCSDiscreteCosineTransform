#include "mydialog.h"
#include "functions.cpp"
#include <QApplication>
#include <iostream>
#include <QDebug>
#include <stdio.h>
#include <algorithm>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fname;
    int F, d, i, j;
    QImage original_image;

    // open dialog interface
    MyDialog mDialog;
    //mDialog.setModal(true);
    //mDialog.exec();

    // cycling untill the parameters are correct
    while(!(mDialog.start())) {
        if ( mDialog.exec() == QDialog::Accepted && mDialog.start()) {
            F = mDialog.getF();
            d = mDialog.getD();
            fname = mDialog.getFilename();
        }

    }

    // debug prints
    qDebug() << fname;
    qDebug() << "F: " << F << " d: " << d;

    /* GET PARAMETERS FROM THE IMAGE */

    cv::Mat image;
    image = cv::imread(fname.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    unsigned int width, height;
    //rgb_t colour;
    width = image.rows;
    height = image.cols;

    std::vector< std::vector<double> > data_vec (width, std::vector<double> (height, 0.0));
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            data_vec[i][j] = double(image.at<unsigned char>(i, j));
        }
    }

    // debug print
    qDebug() << "data_vec inizialized";


    // scarto avanzi
    unsigned int cropped_width, cropped_height;
    cropped_width = width - (width % F);
    cropped_height = height - (height % F);

    // debug print
    qDebug() << "cropped_width: " << cropped_width << " cropped_height " << cropped_height;

    std::vector< std::vector<double> > data_vec_cropped (cropped_width, std::vector<double> (cropped_height, 0.0));
    // creo vettore bidimensionale che verrà utilizzato per eseguire la DCT2
    std::vector< std::vector<double> > c (F, std::vector<double> (F));
    std::vector< std::vector<double> > ff (F, std::vector<double> (F));

    int temp_i, temp_j;
    for (i = 0; i < cropped_width; i = i + F) {
        for (j = 0; j < cropped_height; j = j + F) {
            temp_i = i;
            temp_j = j;
            for (int k = 0; k < F; k++) {
                for (int l = 0; l < F; l++) {
                    c[k][l] = data_vec[temp_i][temp_j];
                    if ((abs(j - temp_j) + 1) < F)
                        temp_j += 1;
                    else
                        temp_j = j;
                }
                temp_i += 1;
            }

            // applicare DCT2 libreria
            c = functions::dct2_NxN(c, F);

            // remove frequences
            c = functions::removeFreqs(c, F, d);

            // applicare IDCT2 fatta da me su array modificato
            ff = functions::idct2_NxN(c, F);

            // arrotondare i valori, a zero i valori < 0, 255 i valori > 255
            ff = functions::round(ff, F);

            // salvare nella sua posizione il blocco appena calcolato ricomponendo l'immagine
            temp_i = i;
            temp_j = j;
            for (int k = 0; k < F; k++) {
                for (int l = 0; l < F; l++) {
                    data_vec_cropped[temp_i][temp_j] = ff[k][l];
                    if ((abs(j - temp_j) + 1) < F)
                        temp_j += 1;
                    else
                        temp_j = j;
                }
                temp_i += 1;
            }
        }
    }

    // debug print
    qDebug() << "computed transformation";

    cv::Mat new_image(cropped_width, cropped_height, image.type());
    for (i = 0; i < cropped_width; i++) {
        for (j = 0; j < cropped_height; j++) {
            new_image.at<unsigned char>(i, j) = char(data_vec_cropped[i][j]);
        }
    }

    cv::Size s1 = image.size();
    cv::Size s2 = new_image.size();

    cv::Mat output(s1.height, s1.width + s2.width, image.type()); // put in the type of your mat

    cv::Mat help1(output, cv::Rect(0,0, s1.width, s1.height));
    cv::Mat help2(output, cv::Rect(s1.width, 0, s2.width, s2.height));

    image.copyTo(help1);
    new_image.copyTo(help2);
    cv::namedWindow("Real vs Transformed", 0);
    if (s1.height > s1.width)
        cv::resizeWindow("Real vs Transformed", 800, 1200);
    else {
        cv::resizeWindow("Real vs Transformed", 1200, 800);
    }
    cv::imshow("Real vs Transformed", output);


    // debug print
    qDebug() << "image saved";

    qDebug() << "end";

    qDebug() << "restart";
    // restart application
    QProcess::startDetached(a.arguments()[0], a.arguments());

    return a.exec();
}
