#ifndef PLOT_H
#define PLOT_H

#include <vector>

#include "../base/sheet.h"

namespace Plotypus
{
    class Plot : public Sheet
    {
        protected:
            PlotStyleFamily         styleFamily = PlotStyleFamily::Undefined;
            std::vector<DataView*>  dataViews;

            size_t      border          = BORDERS_2D_DEFAULT;
            size_t      borderLineStyle = STYLE_ID_DEFAULT;

            std::string aspect      = "noratio";
            std::string fill        = "solid";

            bool        key         = true;
            bool        parametric  = false;

            void checkStyleFamily(PlotStyleFamily newDataViewFamily, const std::vector<PlotStyleFamily> allowedFamilies);

        public:
            Plot(const std::string& title);

            virtual void reset();

            const std::vector<DataView*>& getDataViews() const;
            DataView&           dataView(const size_t i);
            template<DataViewLike T>
            T&                  dataViewAs(const size_t i);

            size_t              getBorder() const;
            void                setBorder(size_t newBorder);
            size_t              getBorderLineStyle() const;
            void                setBorderLineStyle(size_t newBorderLineStyle);

            const std::string&  getAspect      () const;
            void                setAspect      (const std::string& newAspect);
            void                setAspectNone  ();
            void                setAspectSquare();
            void                setAspectEqual ();
            void                setAspectRatio (double ratio);
            const std::string&  getFill() const;
            void                setFill(const std::string& newFill);

            bool                getKey() const;
            void                setKey(bool newKey);
            bool                getParametric() const;
            void                setParametric(bool newParametric);

            // -------------------------------------------------------------- //
            // writers

            void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeScriptHead(std::ostream& hFile) const;
    };
}

#include "plot.txx"
#endif // PLOT_H
