#ifndef PLOT_H
#define PLOT_H

#include <optional>
#include <vector>

#include "../base/sheet.h"
#include "../elements/keydescriptor.h"
#include "../collections/dataviewcollection.h"

namespace Plotypus
{
    /**
     * @brief foo bar
     */
    class Plot : public Sheet, public DataViewCollection
    {
        protected:
            static constexpr auto allowedDataViewTypes =
            {
                DataViewType::DataViewDefaultCompound,
                DataViewType::DataViewDefaultSeparate
            };

            PlotStyleFamily             plotStyleFamily = PlotStyleFamily::Undefined;

            size_t                      border = BORDERS_DEFAULT;
            std::optional<size_t>       borderLineStyle;

            std::optional<std::string>  aspect = "noratio";
            std::optional<std::string>  fill   = "solid";

            std::string datalineSeparatorTxt = "................................................................................\n";

            KeyDescriptor m_key;
            bool          parametric  = false;

            void checkAndSetStyleFamily(PlotStyleFamily newDataViewFamily, const std::vector<PlotStyleFamily> allowedFamilies);

            virtual void abstractToken() = 0;

        public:
            Plot(const SheetType& type);
            Plot(const SheetType& type, const std::string& title);

            virtual Plot& reset();

            PlotStyleFamily     getPlotStyleFamily() const;
            //! @todo couple with mode3D in ortho-axes..? virtual?
            Plot&               setPlotStyleFamily(PlotStyleFamily newStyleFamily);

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

#endif // PLOT_H
