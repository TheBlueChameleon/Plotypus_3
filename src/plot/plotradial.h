#ifndef PLOT_RADIAL_H
#define PLOT_RADIAL_H

#include "plot.h"

namespace Plotypus
{
    class PlotRadial : public Plot
    {
        protected:
            void abstractToken();

        public:
            PlotRadial(const std::string& title);
    };
}

#endif // PLOT_RADIAL_H
