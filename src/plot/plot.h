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
            AxisDescriptor xAxis = {"x"};
            AxisDescriptor yAxis = {"y"};

            bool        key         = true;
            bool        border      = true;
            bool        parametric  = false;
            bool        polar       = false;
            std::string aspect      = "noratio";
            std::string fill        = "solid";

            static std::string generateRangeString(double min, double max);
            void writeAxisDescriptor(std::ostream& hFile, const std::string& axis, const AxisDescriptor& label) const;

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

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const = 0;

            virtual void writeScriptHead(std::ostream& hFile) const;
    };

}
#endif // PLOT_H
