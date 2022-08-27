#ifndef PLOT_H
#define PLOT_H

#include <vector>

#include "../base/sheet.h"

namespace Plotypus
{
    /**
     * @brief foo bar
     *
     * @todo legend position
     */
    class Plot : public Sheet
    {
        protected:
            PlotStyleFamily         plotStyleFamily = PlotStyleFamily::Undefined;
            std::vector<DataView*>  dataViews;

            size_t      border          = BORDERS_2D_DEFAULT;
            size_t      borderLineStyle = STYLE_ID_DEFAULT;

            std::string aspect      = "noratio";
            std::string fill        = "solid";

            bool        key         = true;         //! @todo introduce key descriptor (cf. p.160)
            bool        parametric  = false;

            void checkAndSetStyleFamily(PlotStyleFamily newDataViewFamily, const std::vector<PlotStyleFamily> allowedFamilies);

        public:
            Plot(const std::string& title);

            virtual Plot& reset();

            PlotStyleFamily     getPlotStyleFamily() const;
            Plot&               setPlotStyleFamily(PlotStyleFamily newStyleFamily);     //! @todo: couple with mode3D in ortho-axes..? virtual?

            const std::vector<DataView*>& getDataViews() const;
            DataView&           dataView(const size_t i);
            template<DataViewLike T>
            T&                  dataViewAs(const size_t i);

            size_t              getBorder() const;
            Plot&               setBorder(size_t newBorder);
            size_t              getBorderLineStyle() const;
            Plot&               setBorderLineStyle(size_t newBorderLineStyle);

            const std::string&  getAspect      () const;
            Plot&               setAspect      (const std::string& newAspect);
            Plot&               setAspectNone  ();
            Plot&               setAspectSquare();
            Plot&               setAspectEqual ();
            Plot&               setAspectRatio (double ratio);
            const std::string&  getFill() const;
            Plot&               setFill(const std::string& newFill);

            bool                getKey() const;
            Plot&               setKey(bool newKey);
            bool                getParametric() const;
            Plot&               setParametric(bool newParametric);

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeScriptHead(std::ostream& hFile) const;
    };
}

#include "plot.txx"
#endif // PLOT_H
