#ifndef PLOT_H
#define PLOT_H

#include <cmath>
#include <vector>

#include "../definitions/types.h"
#include "../definitions/styles.h"
#include "../base/sheet.h"

namespace Plotypus
{
    class Plot : public Sheet
    {
        private:
            std::string xLabel  = "x";
            std::string yLabel  = "y";

            bool    xTicks          = true;
            double  xRangeMin       = 0;
            double  xRangeMax       = std::nan("inf");
            int     xRangeStride    = 1;

            bool    yTicks          = true;
            double  yRangeMin       = 0;
            double  yRangeMax       = std::nan("inf");
            int     yRangeStride    = 1;

            bool        key     = true;
            bool        border  = true;
            std::string aspect  = "ratio -1";

        public:
            Plot(const std::string& title);

            const std::string&  getXLabel() const;
            void                setXLabel(const std::string& newXLabel);
            const std::string&  getYLabel() const;
            void                setYLabel(const std::string& newYLabel);

            bool                getXTicks() const;
            void                setXTicks(bool newXAxis);
            double              getXRangeMin() const;
            void                setXRangeMin(double newXRangeMin);
            double              getXRangeMax() const;
            void                setXRangeMax(double newXRangeMax);
            int                 getXRangeStride() const;
            void                setXRangeStride(int newXRangeStride);

            bool                getYTicks() const;
            void                setYTicks(bool newYAxis);
            double              getYRangeMin() const;
            void                setYRangeMin(double newYRangeMin);
            double              getYRangeMax() const;
            void                setYRangeMax(double newYRangeMax);
            int                 getYRangeStride() const;
            void                setYRangeStride(int newYRangeStride);

            bool                getKey() const;
            void                setKey(bool newKey);
            bool                getBorder() const;
            void                setBorder(bool newBorder);

            const std::string&  getAspect      () const;
            void                setAspect      (const std::string& newAspect);
            void                setAspectNone  ();
            void                setAspectSquare();
            void                setAspectEqual ();
            void                setAspectRatio (double ratio);

            // writers
            virtual void writePdfHead(std::ofstream& hFile);
    };

}
#endif // PLOT_H
