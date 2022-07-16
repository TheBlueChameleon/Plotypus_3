#ifndef REPORT_TXX
#define REPORT_TXX

#include "../plot/plot2d.h"

namespace Plotypus
{
    template <class T>
    Plot2D<T>& Report::addPlot2D(const std::string& title)
    {
        Plot2D<T>* newPlot = new Plot2D<T>(title);
        sheets.push_back(newPlot);
        return *newPlot;
    }
}

#endif // REPORT_TXX
