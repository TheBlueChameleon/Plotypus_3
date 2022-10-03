#include "abstractplot.h"

using namespace std::string_literals;
using namespace Plotypus;

namespace Plotypus
{

    AbstractPlot::AbstractPlot(const SheetType& type) :
        Sheet(type), DataviewCollection(allowedDataViewTypes)
    {}

    AbstractPlot::AbstractPlot(const SheetType& type, const std::string& title) :
        Sheet(type, title), DataviewCollection(allowedDataViewTypes)
    {}

    // ====================================================================== //

    void AbstractPlot::checkAndSetStyleFamily(PlotStyleFamily newDataViewFamily, const std::vector<PlotStyleFamily> allowedFamilies)
    {
        if      (plotStyleFamily == PlotStyleFamily::Custom)
        {
            return;
        }
        else if (plotStyleFamily == PlotStyleFamily::Undefined)
        {
            if (contains(newDataViewFamily, allowedFamilies))
            {
                plotStyleFamily = newDataViewFamily;
            }
            else
            {
                throw IncompatiblePlotStyle("Cannot add DataView to Plot: plot style not supported by sheet type");
            }
        }
        else if (plotStyleFamily != newDataViewFamily)
        {
            throw IncompatiblePlotStyle("Cannot add DataView to Plot: plot style not compatible with already present plots");
        }
    }

    AbstractPlot& AbstractPlot::reset()
    {
        Sheet::reset();
        clearDataviews();

        plotStyleFamily = PlotStyleFamily::Undefined;

        border = BORDERS_DEFAULT;
        borderLineStyle.reset();

        aspect = "noratio";
        fill   = "solid";

        datalineSeparatorTxt = "................................................................................\n";

        m_key.reset();
        m_paletteDescriptor.reset();

        parametric = false;

        return *this;
    }

    // ====================================================================== //

    PlotStyleFamily AbstractPlot::getPlotStyleFamily() const
    {
        return plotStyleFamily;
    }

    AbstractPlot& AbstractPlot::setPlotStyleFamily(PlotStyleFamily newStyleFamily)
    {
        if (plotStyleFamily != newStyleFamily)
        {
            // *INDENT-OFF*
            if (contains(plotStyleFamily, {PlotStyleFamily::Custom, PlotStyleFamily::Undefined}))   {plotStyleFamily = newStyleFamily;}
            else                                                                                {throw IncompatiblePlotStyle("Cannot override plot style family");}
            // *INDENT-ON*
        }

        return *this;
    }

    // ====================================================================== //

    size_t AbstractPlot::getBorder() const
    {
        return border;
    }

    AbstractPlot& AbstractPlot::setBorder(size_t newBorder)
    {
        border = newBorder;
        return *this;
    }

    size_t AbstractPlot::getBorderLineStyle() const
    {
        return borderLineStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    AbstractPlot& AbstractPlot::setBorderLineStyle(size_t newBorderLineStyle)
    {
        borderLineStyle = newBorderLineStyle;
        return *this;
    }

    AbstractPlot& AbstractPlot::clearBorderLineStyle()
    {
        borderLineStyle.reset();
        return *this;
    }

    KeyDescriptor& AbstractPlot::key()
    {
        if (!m_key.has_value())
        {
            m_key = KeyDescriptor();
        }

        return m_key.value();
    }

    PaletteDescriptor& AbstractPlot::paletteDescriptor()
    {
        if (!m_paletteDescriptor.has_value())
        {
            m_paletteDescriptor = PaletteDescriptor();
        }

        return m_paletteDescriptor.value();
    }

    bool AbstractPlot::getParametric() const
    {
        return parametric;
    }

    AbstractPlot& AbstractPlot::setParametric(bool newParametric)
    {
        parametric = newParametric;
        return *this;
    }

    const std::string AbstractPlot::getAspect() const
    {
        return aspect.value_or("");
    }

    AbstractPlot& AbstractPlot::setAspect(const std::string& newAspect)
    {
        aspect = newAspect;
        return *this;
    }

    AbstractPlot& AbstractPlot::setAspectNone()
    {
        aspect = "noratio";
        return *this;
    }

    AbstractPlot& AbstractPlot::setAspectSquare()
    {
        aspect = "square";
        return *this;
    }

    AbstractPlot& AbstractPlot::setAspectEqual()
    {
        aspect = "ratio -1";
        return *this;
    }

    AbstractPlot& AbstractPlot::setAspectRatio(double ratio)
    {
        aspect = "ratio "s + std::to_string(ratio);
        return *this;
    }

    AbstractPlot& AbstractPlot::clearAspect()
    {
        aspect.reset();
        return *this;
    }

    const std::string AbstractPlot::getFill() const
    {
        return fill.value_or("");
    }

    AbstractPlot& AbstractPlot::setFill(const std::string& newFill)
    {
        fill = newFill;
        return *this;
    }

    AbstractPlot& AbstractPlot::clearFill()
    {
        fill.reset();
        return *this;
    }

    const std::string& AbstractPlot::getDatalineSeparatorTxt() const
    {
        return datalineSeparatorTxt;
    }

    AbstractPlot& AbstractPlot::setDatalineSeparatorTxt(const std::string& newDatalineSeparatorTxt)
    {
        datalineSeparatorTxt = newDatalineSeparatorTxt;
        return *this;
    }

    // ====================================================================== //
    // writers

    void AbstractPlot::preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const
    {
        Sheet::preprocessSheet(autoDataFilename, extension);

        for (size_t i = 1u; const auto dataView : dataviews)
        {
            if (dataView->getAutoGenerateDataFilename())
            {
                const auto fullOutputFilename = autoDataFilename + "_" + std::to_string(i) + "." + extension;
                dataView->setDataFilename(fullOutputFilename);
            }
            ++i;
        }
    }

    void AbstractPlot::writeScriptHead(std::ostream& hFile) const
    {
        Sheet::writeScriptHead(hFile);

        // *INDENT-OFF*
        if (aspect.has_value()) {hFile << "set size " << aspect.value() << std::endl;}
        if (fill.  has_value()) {hFile << "set style fill " << fill.value() << std::endl;}


        if (border == BORDERS_NONE) {hFile << "unset border" << std::endl;}
        else                        {hFile <<   "set border " << border;
                                     hFile << optionalSizeTArgument("linestyle", borderLineStyle);
                                     hFile << std::endl;}

        if (m_key               .has_value()) {m_key                .value().writeKeyDescriptor     (hFile);}
        if (m_paletteDescriptor .has_value()) {m_paletteDescriptor  .value().writePaletteDescriptor (hFile);}
        // *INDENT-ON*

        hFile << (parametric    ? "" : "un") << "set parametric" << std::endl;
        hFile << std::endl;
    }

    void AbstractPlot::writeScriptFooter(std::ostream& hFile, const int pageNum) const
    {
        Sheet::writeScriptFooter(hFile, pageNum);

        // *INDENT-OFF*
        if (m_key               .has_value()) {m_key                .value().writeUnsetCommands(hFile);}
        if (m_paletteDescriptor .has_value()) {m_paletteDescriptor  .value().writeUnsetCommands(hFile);}
        // *INDENT-ON*
    }
}
