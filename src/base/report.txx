#ifndef REPORT_TXX
#define REPORT_TXX

#include "../plot/plot2d.h"

using namespace Plotypus;
namespace Plotypus
{
    template <class T>
    Sheet& Report::addPlot2D(const std::string& title)
    {
        {
            // instantiate Plot2D<T> just so that the code exists -- gcc should optimize this away
            Plot2D<T> x("");
        }
        sheets.push_back(new Plot2D<T>(title));
        return *sheets.back();
    }
}

#endif // REPORT_TXX
