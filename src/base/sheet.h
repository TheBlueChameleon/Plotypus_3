#ifndef SHEET_H
#define SHEET_H

#include <string>

#include "../definitions/types.h"

namespace Plotypus
{
    class Sheet
    {
        protected:
            // .............................................................. //
            // behaviour objects

            PlotType type = PlotType::Sheet;

        public:
            Sheet();
            ~Sheet();
    };

}

#endif // SHEET_H
