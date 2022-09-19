#ifndef ABSTRACTPLOT_H
#define ABSTRACTPLOT_H

#include <optional>
#include <vector>

#include "sheet.h"

#include "../elements/keydescriptor.h"
#include "../collections/dataviewcollection.h"

namespace Plotypus
{
    /**
     * @brief foo bar
     *
     * @todo set palette, colorbox ~> new element, optional here
     */
    class AbstractPlot : public Sheet, public DataviewCollection
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
            AbstractPlot(const SheetType& type);
            AbstractPlot(const SheetType& type, const std::string& title);

            virtual AbstractPlot& reset();

            PlotStyleFamily     getPlotStyleFamily() const;
            //! @todo couple with mode3D in ortho-axes..? virtual?
            AbstractPlot&               setPlotStyleFamily(PlotStyleFamily newStyleFamily);

            size_t              getBorder() const;
            AbstractPlot&               setBorder(size_t newBorder);

            size_t              getBorderLineStyle() const;
            AbstractPlot&               setBorderLineStyle(size_t newBorderLineStyle);
            AbstractPlot&               clearBorderLineStyle();

            const std::string   getAspect      () const;
            AbstractPlot&               setAspect      (const std::string& newAspect);
            AbstractPlot&               setAspectNone  ();
            AbstractPlot&               setAspectSquare();
            AbstractPlot&               setAspectEqual ();
            AbstractPlot&               setAspectRatio (double ratio);
            AbstractPlot&               clearAspect    ();

            const std::string   getFill() const;
            AbstractPlot&               setFill(const std::string& newFill);
            AbstractPlot&               clearFill();

            const std::string&  getDatalineSeparatorTxt() const;
            AbstractPlot&               setDatalineSeparatorTxt(const std::string& newDatalineSeparatorTxt);

            KeyDescriptor&      key();

            bool                getParametric() const;
            AbstractPlot&               setParametric(bool newParametric);

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeScriptHead(std::ostream& hFile) const;
    };
}

#endif // ABSTRACTPLOT_H
