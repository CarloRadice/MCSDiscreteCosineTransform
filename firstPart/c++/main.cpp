// Carlo Radice 807159
// Metodi del calcolo scientifico
// A.A 2018/2019

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <complex>
#include <fftw3.h>
#include <fstream>
#include "FastDctFft.hpp"
#include "mydct.h"

void dct_8() {

    unsigned int N, i;
    N = 8;

    std::vector< int > f (N);
    std::vector<double> c (N, 0.0);

    f = {231, 32, 233, 161, 24, 71, 140, 245};

    auto start = std::chrono::high_resolution_clock::now();
    c = mydctlibrary::mydct(f, N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    for(i = 0; i < N; i++)
       std::cout << c[i] << " ";
    std::cout << std::endl;

    std::cout << "mydct time: " << duration.count() << " microseconds" << std::endl;

    std::cout << std::endl;

/*  USING NAYUKI FUNCTION */

    std::vector<double> ff (N);

    ff = {231, 32, 233, 161, 24, 71, 140, 245};

    start = std::chrono::high_resolution_clock::now();
    FastDctFft::transform(ff);

    for(i = 0; i < N; i++) {
        if (i != 0)
            ff[i] = ff[i] * sqrt(2.0 / double(N));
        else
            ff[i] = ff[i] * (1.0 / sqrt(double(N)));
    }

    stop = std::chrono::high_resolution_clock::now();
    auto durationlibrary = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    for(i = 0; i < N; i++)
       std::cout << ff[i] << " ";
    std::cout << std::endl;

    std::cout << "dctlibrary time: " << durationlibrary.count() << " microseconds \n" << std::endl;

}

void idct_8() {

    unsigned int N, i;
    N = 8;

    std::vector< int > f (N, 0);
    std::vector<double> c (N);

    c = {401.99, 6.60002, 109.167, -112.786, 65.4074, 121.831, 116.656, 28.8004};

    auto start = std::chrono::high_resolution_clock::now();
    f = mydctlibrary::myidct(c, N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    for(i = 0; i < N; i++)
       std::cout << f[i] << " ";
    std::cout << std::endl;

    std::cout << "myidct time: " << duration.count() << " microseconds" << std::endl;

    std::cout << std::endl;

    /*  USING NAYUKI FUNCTION */

        std::vector<double> cc (N);

        cc = {401.99, 6.60002, 109.167, -112.786, 65.4074, 121.831, 116.656, 28.8004};

        start = std::chrono::high_resolution_clock::now();
        FastDctFft::inverseTransform(cc);

//        for(i = 0; i < N; i++) {
//            if (i != 0)
//                cc[i] = cc[i] / (1 / (sqrt(2.0 / double(N))));
//            else
//                cc[i] = cc[i] / (1 / (1.0 / sqrt(double(N))));
//        }

        stop = std::chrono::high_resolution_clock::now();
        auto durationlibrary = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        for(i = 0; i < N; i++)
            std::cout << cc[i] << " ";
        std::cout << std::endl;

        std::cout << "idctlibrary time: " << durationlibrary.count() << " microseconds \n" << std::endl;
}

void dct2_8x8() {

    unsigned int N, i, j;
    N = 8;

    std::vector< std::vector<int> > f (N, std::vector<int> (N, 0));
    std::vector< std::vector<double> > c (N, std::vector<double>(N, 0.0));


    f = {{231,  32, 233, 161,  24,  71, 140, 245},
         {247,  40, 248, 245, 124, 204,  36, 107},
         {234, 202, 245, 167,   9, 217, 239, 173},
         {193, 190, 100, 167,  43, 180,   8,  70},
         { 11,  24, 210, 177,  81, 243,   8, 112},
         { 97, 195, 203,  47, 125, 114, 165, 181},
         {193,  70, 174, 167,  41,  30, 127, 245},
         { 87, 149,  57, 192,  65, 129, 178, 228}};


    auto start = std::chrono::high_resolution_clock::now();
    c = mydctlibrary::mydct2(f, N, N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "mydct2 time: " << duration.count() << " microseconds" << std::endl;

    std::cout << std::endl;

    /* USING NAYUKI ALGORITHM */


    std::vector< std::vector<double> > ff (N, std::vector<double> (N, 0.0));
    std::vector< double > support (N);

    ff = {{231,  32, 233, 161,  24,  71, 140, 245},
          {247,  40, 248, 245, 124, 204,  36, 107},
          {234, 202, 245, 167,   9, 217, 239, 173},
          {193, 190, 100, 167,  43, 180,   8,  70},
          { 11,  24, 210, 177,  81, 243,   8, 112},
          { 97, 195, 203,  47, 125, 114, 165, 181},
          {193,  70, 174, 167,  41,  30, 127, 245},
          { 87, 149,  57, 192,  65, 129, 178, 228}};

    start = std::chrono::high_resolution_clock::now();

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            support[j] = ff[j][i];
        }
        FastDctFft::transform(support);
        for(j = 0; j < N; j++) {
            ff[j][i] = support[j];
        }
    }

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            support[j] = ff[i][j];
        }
        FastDctFft::transform(support);
        for(j = 0; j < N; j++) {
            ff[i][j] = support[j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (i == 0 && j == 0) {
                ff[i][j] = ff[i][j] / (double(N));
            }
            else if (i == 0 || j == 0) {
                ff[i][j] = ff[i][j] / 2.0 * (1.0 / sqrt(double(N)));
            }
            else if (i != 0 && j != 0) {
                ff[i][j] = ff[i][j] / (double(N) / 2);
            }
        }
    }

    stop = std::chrono::high_resolution_clock::now();
    auto durationlibrary = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            std::cout << ff[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "dct2library time: " << durationlibrary.count() << " microseconds" << std::endl;


}

void dct_N(unsigned int N) {

    unsigned int i;

    std::vector< int > f (N);
    std::vector<double> c (N, 0.0);

    for (i = 0; i < N; i++) {
              f[i] = std::rand() % 255;
    }

    auto start = std::chrono::high_resolution_clock::now();
    c = mydctlibrary::mydct(f, N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

//    for(i = 0; i < N; i++)
//       std::cout << c[i] << " ";
//    std::cout << std::endl;

    std::cout << "mydct time: " << duration.count() << " microseconds" << std::endl;

    std::cout << std::endl;

    /*  USING NAYUKI ALGORITHM */

    std::vector<double> ff (N);

    for (i = 0; i < N; i++) {
          ff[i] = f[i];
    }

    start = std::chrono::high_resolution_clock::now();

    FastDctFft::transform(ff);

    for(i = 0; i < N; i++) {
        if (i != 0)
            ff[i] = ff[i] * sqrt(2.0 / double(N));
        else
            ff[i] = ff[i] * (1.0 / sqrt(double(N)));
    }

    stop = std::chrono::high_resolution_clock::now();
    auto durationlibrary = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

//    for(i = 0; i < N; i++)
//        std::cout << ff[i] << " ";
//    std::cout << std::endl;

    std::cout << "dctlibrary time: " << durationlibrary.count() << " microseconds" << std::endl;

}

void dct2_NxN(unsigned int N) {

    unsigned int i, j;

    std::vector< std::vector<int> > f (N, std::vector<int> (N, 0));
    std::vector< std::vector<double> > ff (N, std::vector<double> (N, 0.0));
    std::vector< std::vector<double> > c (N, std::vector<double>(N, 0.0));

    for (i = 0; i < N; i++) {
          for (j = 0; j < N; j++) {
              f[i][j] = std::rand() % 255;
              ff[i][j] = f[i][j];
          }
    }

    auto start = std::chrono::high_resolution_clock::now();
    c = mydctlibrary::mydct2(f, N, N);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

//    for(i = 0; i < N; i++) {
//        for(j = 0; j < N; j++) {
//            std::cout << c[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    //std::cout << "mydct2 time: " << duration.count() << " microseconds" << "\n" << std::endl;

    /* USING NAYUKI ALGORITHM */

    std::vector< double > support (N);

    start = std::chrono::high_resolution_clock::now();

    // DCT through columms

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            support[j] = ff[j][i];
        }
        FastDctFft::transform(support);
        for(j = 0; j < N; j++) {
            ff[j][i] = support[j];
        }
    }

    // DCT through rows

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            support[j] = ff[i][j];
        }
        FastDctFft::transform(support);
        for(j = 0; j < N; j++) {
            ff[i][j] = support[j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (i == 0 && j == 0) {
                ff[i][j] = ff[i][j] / (double(N));
            }
            else if (i == 0 || j == 0) {
                ff[i][j] = ff[i][j] / (double(N) * 2.0 * (1.0 / sqrt(double(8))));
            }
            else if (i != 0 && j != 0) {
                ff[i][j] = ff[i][j] / (double(N) / 2);
            }
        }
    }

    stop = std::chrono::high_resolution_clock::now();
    auto durationlibrary = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

//    for(i = 0; i < N; i++) {
//        for(j = 0; j < N; j++) {
//            std::cout << ff[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

//  std::cout << "dct2 library time: " << durationlibrary.count() << " microseconds" << std::endl;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if (fabs(c[i][j] - ff[i][j]) > 0.00001) {
                    std::cout << "!!! MATRICI DIVERSE !!! \n";
                    exit(EXIT_FAILURE);
            }
        }
    }

    std::ofstream myfile;
    myfile.open("/home/carloradice/Documents/magistrale/metodi_del_calcolo_scientifico/MCSDiscreteCosineTransform/data.txt", std::ios_base::app);
    myfile << N << " " << duration.count() << " " << durationlibrary.count() << "\n";
    myfile.close();

}

int main()
{
    //dct_8();
    //idct_8();

    //std::cout << std::endl;

    //dct2_8x8();


    unsigned int N = 10;

    //dct_NxN(N);

    //std::cout << std::endl;

   for(N = 8; N < 500;) {
        std::cout << N << "\n" << std::endl;
        dct2_NxN(N);
        N = N + (N / 4);
   }

   std::cout << "end \n" << std::endl;

}


