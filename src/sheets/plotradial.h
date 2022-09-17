#ifndef PLOT_RADIAL_H
#define PLOT_RADIAL_H

#include "abstractplot.h"

namespace Plotypus
{
    class PlotRadial : public AbstractPlot
    {
        protected:
            void abstractToken();

        public:
            PlotRadial(const std::string& title);
    };
}

#endif // PLOT_RADIAL_H
