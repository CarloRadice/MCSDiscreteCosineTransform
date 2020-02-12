#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

namespace functions {

    std::vector< std::vector<double> > removeFreqs(std::vector< std::vector<double> > c, int F, int d);

    std::vector< std::vector<double> > round(std::vector< std::vector<double> > ff, int F);

    std::vector< std::vector<double> > dct2_NxN(std::vector< std::vector<double> > ff, int F);

    std::vector< std::vector<double> > idct2_NxN(std::vector< std::vector<double> > c, unsigned int N);
}

#endif // FUNCTIONS_H
