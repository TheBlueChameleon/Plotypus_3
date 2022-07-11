#include "plot2d.h"

using namespace Plotypus;

namespace Plotypus
{
    template<class T>
    Plot2D<T>::Plot2D(const std::string& title) :
        Plot(title)
    {
        type = PlotType::Plot2D;
    }

    template<class T>
    void Plot2D<T>::reset()
    {
        Plot::reset();
    }
    template<class T>
    void Plot2D<T>::writePdfFooter(std::ofstream& hFile, int pageNum)
    {
        hFile << "plot [][] 1/0 t\"\"" << std::endl;
    }
}
