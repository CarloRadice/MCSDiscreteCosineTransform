// Carlo Radice 807159
// Metodi del calcolo scientifico
// A.A 2018/2019

#include <iostream>
#include <algorithm>
#include <complex>
#include <fftw3.h>
#include <fstream>
#include "FastDctFft.hpp"
#include "functions.h"

/* REMOVE FREQUENCES */
std::vector< std::vector<double> > functions::removeFreqs(std::vector< std::vector<double> > c, int F, int d) {
    for (int h = 0; h < F; h++) {
        for (int g = 0; g < F; g++) {
            if ((h + g) >= d)
                c[h][g] = 0.0;
        }
    }

    return c;
}

/* ROUND */
std::vector< std::vector<double> > functions::round(std::vector< std::vector<double> > ff, int F) {
    for(unsigned int i = 0; i < F; i++) {
        for(unsigned int j = 0; j < F; j++) {
            if (ff[i][j] <= 0.0) {
                ff[i][j] = 0.0;
            }
            else if (ff[i][j] >= 255.0) {
                ff[i][j] = 255.0;
            }
            else {
                ff[i][j] = double(int(ff[i][j] + 0.5));
            }
        }
    }

    return ff;
}

/* DCT2 LIBRARY */
std::vector< std::vector<double> > functions::dct2_NxN(std::vector< std::vector<double> > ff, int F) {
    unsigned int i, j;

    /* USING NAYUKI ALGORITHM */

    std::vector< double > support (F);

    // DCT through columms
    for(i = 0; i < F; i++) {
        for(j = 0; j < F; j++) {
            support[j] = ff[j][i];
        }
        FastDctFft::transform(support);
        for(j = 0; j < F; j++) {
            ff[j][i] = support[j];
        }
    }

    // DCT through rows
    for(i = 0; i < F; i++) {
        for(j = 0; j < F; j++) {
            support[j] = ff[i][j];
        }
        FastDctFft::transform(support);
        for(j = 0; j < F; j++) {
            ff[i][j] = support[j];
        }
    }

    // scaling values
    for(int i = 0; i < F; i++) {
        for(int j = 0; j < F; j++) {
            if (i == 0 && j == 0) {
                ff[i][j] = ff[i][j] / (double(F));
            }
            else if (i == 0 || j == 0) {
                ff[i][j] = ff[i][j] / (double(F) * 2.0 * (1.0 / sqrt(double(8))));
            }
            else if (i != 0 && j != 0) {
                ff[i][j] = ff[i][j] / (double(F) / 2);
            }
        }
    }

    return ff;

}

/* MY IDCT2 */
std::vector< std::vector<double> > functions::idct2_NxN(std::vector< std::vector<double> > c, unsigned int N) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    double alpha00, alphaK0, alphaKL;

    std::vector< std::vector<double> > f (N, std::vector<double>(N, 0.0));

    alpha00 = 1.0 / sqrt (N * N);
    alphaK0 = sqrt (2.0 / (N * N));
    alphaKL = 2.0 / sqrt (N * N);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                for (l = 0; l < N; l++) {
                    if (k == 0 && l == 0){
                        f[i][j] = f[i][j] + c[k][l] * alpha00
                                                * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                                * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * N)));
                    }
                    else if (k == 0 || l == 0) {
                        f[i][j] = f[i][j] + c[k][l] * alphaK0
                                                * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                                * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * N)));
                    }
                    else if (k >= 1 && l >= 1) {
                        f[i][j] = f[i][j] + c[k][l] * alphaKL
                                                * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                                * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * N)));
                    }
                }
            }
        }
    }

    return f;
}

