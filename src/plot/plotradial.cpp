#include "plotradial.h"

namespace Plotypus
{
    void PlotRadial::abstractToken() {}

    PlotRadial::PlotRadial(const std::string& title) : Plot(SheetType::PlotRadialAxes, title) {}
}
