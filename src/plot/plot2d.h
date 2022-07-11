#ifndef PLOT2D_H
#define PLOT2D_H

#include <fstream>
#include <string>

#include "plot.h"

namespace Plotypus
{
    template<class T>
    class Plot2D : public Plot
    {
        public:
            Plot2D(const std::string& title);

            virtual void reset();

            virtual void writePdfFooter(std::ofstream& hFile, int pageNum);
    };
}

#include "plot2d.txx"
#endif // PLOT2D_H
