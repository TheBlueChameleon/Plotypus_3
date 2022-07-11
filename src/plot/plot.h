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

            bool        key     = true;
            bool        border  = true;
            std::string aspect  = "ratio -1";

        protected:
            static std::string generateRangeString(double min, double max);
            void writeAxisDescriptor(std::ofstream& hFile, const std::string& axis, const AxisDescriptor& label) const;

        public:
            Plot(const std::string& title);

            virtual void reset();

            AxisDescriptor& getXAxis();
            AxisDescriptor& getYAxis();

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
