// Carlo Radice 807159
// Metodi del calcolo scientifico
// A.A 2018/2019

#include <math.h>
#include "mydct.h"

// DCT
std::vector<double> mydctlibrary::mydct(std::vector<int> f, unsigned int N) {

    unsigned int i = 0;
    unsigned int j = 0;
    double alpha0, alphaK;

    std::vector<double> c (N, 0.0);

    alpha0 = 1.0/sqrt (N);
    alphaK = sqrt (2.0 / N);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i] = c[i] + (f[j] * cos(i * M_PI * ((2.0 * j + 1.0) / (2.0 * N))));
        }
        if (i == 0)
            c[i] = alpha0 * c[i];
        else
            c[i] = alphaK * c[i];

    }

    return c;
}

// IDCT
std::vector<int> mydctlibrary::myidct(std::vector<double> c, unsigned int N) {

    unsigned int i = 0;
    unsigned int j = 0;
    double alpha0, alphaK;

    std::vector<int> f (N, 0);

    alpha0 = 1.0/sqrt (N);
    alphaK = sqrt (2.0 / N);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (j == 0) {
                f[i] = f[i] + int(c[j] * alpha0 * cos(j * M_PI * ((2.0 * i + 1.0) / (2.0 * N))));
            }
            else {
                f[i] = f[i] + int(c[j] * alphaK * cos(j * M_PI * ((2.0 * i + 1.0) / (2.0 * N))));
            }
        }
    }

    return f;
}

// DCT2
std::vector< std::vector<double> > mydctlibrary::mydct2(std::vector< std::vector<int> > f, unsigned int N, unsigned int M) {

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    double alpha00, alphaK0, alphaKL;

    std::vector< std::vector<double> > c(N, std::vector<double>(M, 0.0));

    alpha00 = 1.0 / sqrt (N * M);
    alphaK0 = sqrt (2.0 / (N * M));
    alphaKL = 2.0 / sqrt (N * M);

    for (k = 0; k < N; k++) {
        for (l = 0; l < M; l++) {
            for (i = 0; i < N; i++) {
                for (j = 0; j < M; j++) {
                    c[k][l] = c[k][l] + (f[i][j]
                                         * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                         * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * M))));
                }
            }
            if (k == 0 && l == 0){
                c[k][l] = c[k][l] * alpha00;
            }
            else if (k == 0 || l == 0) {
                c[k][l] = c[k][l] * alphaK0;
            }
            else if (k >= 1 && l >= 1) {
                c[k][l] = c[k][l] * alphaKL;
            }
        }
    }

    return c;
}

// IDCT2
std::vector< std::vector<int> > mydctlibrary::myidct2(std::vector< std::vector<double> > c, unsigned int N, unsigned int M) {

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    double alpha00, alphaK0, alphaKL;

    std::vector< std::vector<int> > f (N, std::vector<int>(M, 0));

    alpha00 = 1.0 / sqrt (N * M);
    alphaK0 = sqrt (2.0 / (N * M));
    alphaKL = 2.0 / sqrt (N * M);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < N; k++) {
                for (l = 0; l < M; l++) {
                    if (k == 0 && l == 0){
                        f[i][j] = f[i][j] + int(c[k][l] * alpha00
                                                * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                                * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * M))));
                    }
                    else if (k == 0 || l == 0) {
                        f[i][j] = f[i][j] + int(c[k][l] * alphaK0
                                                * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                                * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * M))));
                    }
                    else if (k >= 1 && l >= 1) {
                        f[i][j] = f[i][j] + int(c[k][l] * alphaKL
                                                * cos(k * M_PI * ((2.0 * i + 1.0) / (2.0 * N)))
                                                * cos(l * M_PI * ((2.0 * j + 1.0) / (2.0 * M))));
                    }
                }
            }
        }
    }

    return f;
}
