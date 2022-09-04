#ifndef MULITPLOT_H
#define MULITPLOT_H

#include "sheet.h"

namespace Plotypus
{
    class MulitPlot : public Sheet, public SheetsCollection
    {
        protected:
            static constexpr std::initializer_list<SheetType> allowedSheetTypes = {SheetType::Sheet,
                                                                                   SheetType::PlotOrthogonalAxis,
                                                                                   SheetType::PlotRadialAxes
                                                                                  };
        public:
            MulitPlot(const std::string& title);
    };
}

#endif // MULITPLOT_H
