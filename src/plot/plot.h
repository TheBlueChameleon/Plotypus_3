#ifndef PLOT_H
#define PLOT_H

#include <optional>
#include <vector>

#include "../base/sheet.h"
#include "../elements/keydescriptor.h"

namespace Plotypus
{
    /**
     * @brief foo bar
     *
     * @todo make abstract
     *
     * @note externalize std::vector<DataView*> dataViews via new base class DataViewsCollection..? probably not necessary, since there will be no other DataViewCollections.
     */
    class Plot : public Sheet
    {
        protected:
            PlotStyleFamily             plotStyleFamily = PlotStyleFamily::Undefined;
            std::vector<DataView*>      dataViews;

            size_t                      border = BORDERS_DEFAULT;
            std::optional<size_t>       borderLineStyle;

            std::optional<std::string>  aspect = "noratio";
            std::optional<std::string>  fill   = "solid";

            std::string datalineSeparatorTxt = "................................................................................\n";

            KeyDescriptor m_key;
            bool          parametric  = false;

            void checkAndSetStyleFamily(PlotStyleFamily newDataViewFamily, const std::vector<PlotStyleFamily> allowedFamilies);

        public:
            Plot(const SheetType& type);
            Plot(const SheetType& type, const std::string& title);

            virtual Plot& reset();

            PlotStyleFamily     getPlotStyleFamily() const;
            //! @todo couple with mode3D in ortho-axes..? virtual?
            Plot&               setPlotStyleFamily(PlotStyleFamily newStyleFamily);

            const std::vector<DataView*>& getDataViews() const;
            DataView&           dataView(const size_t i);
            template<DataViewLike T>
            T&                  dataViewAs(const size_t i);

            size_t              getBorder() const;
            Plot&               setBorder(size_t newBorder);

            size_t              getBorderLineStyle() const;
            Plot&               setBorderLineStyle(size_t newBorderLineStyle);
            Plot&               clearBorderLineStyle();

            const std::string   getAspect      () const;
            Plot&               setAspect      (const std::string& newAspect);
            Plot&               setAspectNone  ();
            Plot&               setAspectSquare();
            Plot&               setAspectEqual ();
            Plot&               setAspectRatio (double ratio);
            Plot&               clearAspect    ();
            const std::string   getFill() const;
            Plot&               setFill(const std::string& newFill);
            Plot&               clearFill();

            const std::string&  getDatalineSeparatorTxt() const;
            Plot&               setDatalineSeparatorTxt(const std::string& newDatalineSeparatorTxt);

            KeyDescriptor&      key();

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
