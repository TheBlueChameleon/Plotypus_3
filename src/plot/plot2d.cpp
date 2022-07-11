#include "plot2d.h"

using namespace Plotypus;

namespace Plotypus
{
    Plot2D::Plot2D(const std::string& title) :
        Plot(title)
    {
        type = PlotType::Plot2D;
    }

    void Plot2D::reset()
    {
        Plot::reset();
    }

    void Plot2D::writePdfFooter(std::ofstream& hFile, int pageNum)
    {
        hFile << "plot [][] 1/0 t\"\"" << std::endl;
    }
}
