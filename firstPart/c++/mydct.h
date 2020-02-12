// Carlo Radice 807159
// Metodi del calcolo scientifico
// A.A 2018/2019

#ifndef MYDCT_H
#define MYDCT_H

#include <vector>
namespace mydctlibrary  {

// DCT
std::vector<double> mydct(std::vector<int>, unsigned int);

// IDCT
std::vector<int> myidct(std::vector<double> c, unsigned int);

// DCT2
std::vector< std::vector<double> > mydct2(std::vector< std::vector<int> >, unsigned int, unsigned int);

// IDCT2
std::vector< std::vector<int> > myidct2(std::vector< std::vector<double> >, unsigned int, unsigned int);

}
#endif // MYDCT_H

