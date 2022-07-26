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
        protected:
            AxisDescriptor xAxis = AxisDescriptor("x");
            AxisDescriptor yAxis = AxisDescriptor("y");

            bool        key         = true;
            bool        border      = true;
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

            AxisDescriptor& getXAxis();
            AxisDescriptor& getYAxis();

            bool                getKey() const;
            void                setKey(bool newKey);
            bool                getBorder() const;
            void                setBorder(bool newBorder);
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
