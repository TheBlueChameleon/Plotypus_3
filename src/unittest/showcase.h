#ifndef SHOWCASE_H
#define SHOWCASE_H

#include <complex>

// ========================================================================== //
// showcase selection

enum Showcases
{
    Overlays        = 1 << 0,
    Plots_2D        = 1 << 1,
    Plots_2D_maps   = 1 << 2,
    Plots_3D        = 1 << 3,
    Plots_Multiplot = 1 << 4,

    All             = -1,
};

// ========================================================================== //
// behaviour constants

extern bool SHOWCASE_TXT_REPORT;

// ========================================================================== //
// data types and constants

constexpr auto pi = std::numbers::pi;

struct compound_t
{
    double x, y, errX, errY;
};

using complex_t = std::complex<double>;

struct compound_complex_t
{
    complex_t coordinate;
    complex_t value;
};

// ========================================================================== //
// data generators

std::pair<std::vector<double>, std::vector<double>> generateSeparateData2D();
std::vector<compound_t>                             generateCompoundData2D();
std::vector<compound_complex_t>                     generateVectorField();
std::array<std::vector<double>, 3>                  generateScalarField();

// ========================================================================== //
// showcase interface

void showcase_minimal();
void showcase_run(size_t selection);

#endif // SHOWCASE_H
