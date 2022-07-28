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
            /**
             * @todo: upgrade border from boolean to int, as specified on p.136.
             * use set border 0 as "no border" option.
             * maybe also add lt, lw, lc, dt (ignored if border == 0)
             */

        protected:
            AxisDescriptor m_xAxis = AxisDescriptor("x");
            AxisDescriptor m_yAxis = AxisDescriptor("y");

            size_t      border          = BORDERS_2D_DEFAULT;
            size_t      borderLineStyle = STYLE_ID_DEFAULT;

            bool        key         = true;
            bool        parametric  = false;
            bool        polar       = false;
            std::string aspect      = "noratio";
            std::string fill        = "solid";

            static std::string generateRangeString (double min,                   double max);
            static std::string generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax);
            static std::string generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add);

        public:
            Plot(const std::string& title);

            virtual void reset();

            AxisDescriptor&     xAxis();
            AxisDescriptor&     yAxis();

            size_t              getBorder() const;
            void                setBorder(size_t newBorder);
            size_t              getBorderLineStyle() const;
            void                setBorderLineStyle(size_t newBorderLineStyle);

            bool                getKey() const;
            void                setKey(bool newKey);
            bool                getParametric() const;
            void                setParametric(bool newParametric);
            bool                getPolar() const;
            void                setPolar(bool newPolar);

            const std::string&  getAspect      () const;
            void                setAspect      (const std::string& newAspect);
            void                setAspectNone  ();
            void                setAspectSquare();
            void                setAspectEqual ();
            void                setAspectRatio (double ratio);
            const std::string&  getFill() const;
            void                setFill(const std::string& newFill);

            // -------------------------------------------------------------- //
            // writers

            void writeAxisDescriptor(std::ostream& hFile, const std::string& axis, const AxisDescriptor& label) const;

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const = 0;

            virtual void writeScriptHead(std::ostream& hFile) const;
    };

}
#endif // PLOT_H
