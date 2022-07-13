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
            AxisDescriptor xAxis = {"x"};
            AxisDescriptor yAxis = {"y"};

            bool        key         = true;
            bool        border      = true;
            bool        parametric  = false;
            bool        polar       = false;
            std::string aspect  = "ratio -1";

        protected:
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

            // writers
            virtual void writePdfHead(std::ostream& hFile) const;
    };

}
#endif // PLOT_H
