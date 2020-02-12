#include "mydialog.h"
#include "ui_mydialog.h"
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QIntValidator>
#include <QMessageBox>

QString filename;
bool flag = false;
int F, d;

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}


void MyDialog::on_loadimage_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    "/home/carloradice/Documents/magistrale/metodi_del_calcolo_scientifico/images",
                                                    tr("Image files (*.bmp)"));
}

QString MyDialog::getFilename() {
    return filename;
}


int MyDialog::getF() {
    return F;
}


int MyDialog::getD() {
    return d;
}

bool MyDialog::start() {
    return flag;
}

void MyDialog::on_buttonBox_accepted()
{
    QRegExp re("\\d+");
    QString fstring = ui->fLine->text();
    QString dstring = ui->dLine->text();

    if (filename == "") {
        QMessageBox::information(this, "Error message", "image not loaded");
    }
    else {
        if (!re.exactMatch(fstring) || !re.exactMatch(dstring)) {
        QMessageBox::information(this, "Error message", "not a number");
        }
        else {
            F = fstring.toInt();
            d = dstring.toInt();
            if (d <= 0 || d > (2 * F - 2)) {
                QMessageBox::information(this, "Error message", "wrong value for d");
            }
            else {
                flag = true;
            }
        }
    }
}

void MyDialog::on_buttonBox_rejected()
{
    ui->fLine->setText("");
    ui->dLine->setText("");
    filename = "";
}
