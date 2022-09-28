#include "showcase.h"

// ========================================================================== //
// data generators

std::pair<std::vector<double>, std::vector<double>> generateSeparateData2D()
{
    // non-uniform sampling of the x domain, resulting in a sigmoid

    std::vector<double> dataX, dataY;

    size_t i = -1;
    for (double x = -1.; x < 1.;)
    {
        x += 0.1 * std::sqrt( std::abs(x) );
        ++i;

        dataX.push_back((x + 1.) * .5 * pi);
        dataY.push_back(.05 * i - 1);
    }

    return std::make_pair(dataX, dataY);
}

std::vector<compound_t> generateCompoundData2D()
{
    constexpr auto N = 50;
    constexpr auto xIncrement = pi / N;
    std::vector<compound_t> result(N);

    // Taylor approximation of sine
    for (double x = 0.; auto& datapoint : result)
    {
        datapoint.x    = x;
        datapoint.y    = x - (x*x*x / 6.) + (x*x*x*x*x / 120.);
        datapoint.errX = 0.01 + 0.04 * std::sin(x / 2.);
        datapoint.errY = std::abs(datapoint.y - std::sin(x)) * 1.1;

        x += xIncrement;
    }

    return result;
}

std::vector<compound_complex_t> generateVectorField()
{
    // creates a vortex field around origin, domain is [-1, +1) x [-1, +1)

    constexpr auto Nx = 25;
    constexpr auto Ny = 25;

    constexpr auto dx = 2. / Nx;
    constexpr auto dy = 2. / Nx;

    std::vector<compound_complex_t> result(Nx * Ny);

    double x = -1., y = -1.;
    for     (size_t iy = 0u; iy < Nx; ++iy)
    {
        x = -1.;
        for (size_t ix = 0u; ix < Nx; ++ix)
        {
            x += dx;
            const auto coordinate = complex_t(x, y);
            const auto value      = complex_t(0, 1) * coordinate * .1;

            auto& thisArrow = result[iy * Nx + ix];
            thisArrow.coordinate = coordinate;
            thisArrow.value      = value;
        }
        y += dy;
    }

    return result;
}

std::array<std::vector<double>, 3> generateScalarField()
{
    // non-uniform sampling of the domain {which is [-1, 1) x [-1, 1)}
    // z = sin( 1/r ) with r = sqrt(x² + y²)

    std::vector<double> points, dataX, dataY, dataZ;

    for (double q = -1.; q < 1.;)
    {
        q += 0.05 * std::sqrt( std::abs(q) );
        points.push_back(q);
    }

    for     (auto y : points)
    {
        for (auto x : points)
        {
            double r = std::sqrt(x*x + y*y);
            double z = std::sin(2. / r);

            dataX.push_back(x);
            dataY.push_back(y);
            dataZ.push_back(z);
        }
    }

    return {dataX, dataY, dataZ};
}
