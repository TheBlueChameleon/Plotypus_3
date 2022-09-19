#include "plotradial.h"

namespace Plotypus
{
    void PlotRadial::abstractToken() {}

    PlotRadial::PlotRadial(const std::string& title) : AbstractPlot(SheetType::PlotRadial, title) {}
}
