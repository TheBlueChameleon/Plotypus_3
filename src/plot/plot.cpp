#include "plot.h"

using namespace std::string_literals;
using namespace Plotypus;

namespace Plotypus
{

    Plot::Plot(const SheetType& type) :
        Sheet(type)
    {}

    Plot::Plot(const SheetType& type, const std::string& title) :
        Sheet(type, title)
    {}

    // ====================================================================== //

    void Plot::checkAndSetStyleFamily(PlotStyleFamily newDataViewFamily, const std::vector<PlotStyleFamily> allowedFamilies)
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

    Plot& Plot::reset()
    {
        Sheet::reset();

        plotStyleFamily = PlotStyleFamily::Undefined;
        for (auto dataView : dataViews)
        {
            delete dataView;
        }
        dataViews.clear();

        border = BORDERS_DEFAULT;
        borderLineStyle.reset();

        aspect          = "noratio";
        fill            = "solid";

        datalineSeparatorTxt = "................................................................................\n";

        m_key.reset();
        parametric      = false;

        return *this;
    }

    // ====================================================================== //

    PlotStyleFamily Plot::getPlotStyleFamily() const
    {
        return plotStyleFamily;
    }

    Plot& Plot::setPlotStyleFamily(PlotStyleFamily newStyleFamily)
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

    const std::vector<DataView*>& Plot::getDataViews() const
    {
        return dataViews;
    }

    DataView& Plot::dataView(const size_t i)
    {
        throwIfInvalidIndex("dataView index", i, dataViews);
        return *dataViews[i];
    }

    // ====================================================================== //

    size_t Plot::getBorder() const
    {
        return border;
    }

    Plot& Plot::setBorder(size_t newBorder)
    {
        border = newBorder;
        return *this;
    }

    size_t Plot::getBorderLineStyle() const
    {
        return borderLineStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    Plot& Plot::setBorderLineStyle(size_t newBorderLineStyle)
    {
        borderLineStyle = newBorderLineStyle;
        return *this;
    }

    Plot& Plot::clearBorderLineStyle()
    {
        borderLineStyle.reset();
        return *this;
    }

    KeyDescriptor& Plot::key()
    {
        return m_key;
    }

    bool Plot::getParametric() const
    {
        return parametric;
    }

    Plot& Plot::setParametric(bool newParametric)
    {
        parametric = newParametric;
        return *this;
    }

    const std::string& Plot::getAspect() const
    {
        return aspect;
    }

    Plot& Plot::setAspect(const std::string& newAspect)
    {
        aspect = newAspect;
        return *this;
    }

    Plot& Plot::setAspectNone()
    {
        aspect = "noratio";
        return *this;
    }

    Plot& Plot::setAspectSquare()
    {
        aspect = "square";
        return *this;
    }

    Plot& Plot::setAspectEqual()
    {
        aspect = "ratio -1";
        return *this;
    }

    Plot& Plot::setAspectRatio(double ratio)
    {
        aspect = "ratio "s + std::to_string(ratio);
        return *this;
    }

    const std::string& Plot::getFill() const
    {
        return fill;
    }

    Plot& Plot::setFill(const std::string& newFill)
    {
        fill = newFill;
        return *this;
    }

    const std::string& Plot::getDatalineSeparatorTxt() const
    {
        return datalineSeparatorTxt;
    }

    Plot& Plot::setDatalineSeparatorTxt(const std::string& newDatalineSeparatorTxt)
    {
        datalineSeparatorTxt = newDatalineSeparatorTxt;
        return *this;
    }

    // ====================================================================== //
    // writers

    void Plot::preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const
    {
        Sheet::preprocessSheet(autoDataFilename, extension);

        for (size_t i = 1u; const auto dataView : dataViews)
        {
            if (dataView->getAutoGenerateDataFilename())
            {
                const auto fullOutputFilename = autoDataFilename + "_" + std::to_string(i) + "." + extension;
                dataView->setDataFilename(fullOutputFilename);
            }
            ++i;
        }
    }

    void Plot::writeScriptHead(std::ostream& hFile) const
    {
        Sheet::writeScriptHead(hFile);

        // *INDENT-OFF*
        if (!aspect.empty()) {hFile << "set size " << aspect << std::endl;}
        if (!fill.  empty()) {hFile << "set style fill " << fill << std::endl;}


        if (border == BORDERS_NONE) {hFile << "unset border" << std::endl;}
        else                        {hFile <<   "set border " << border;
                                     hFile << optionalSizeTArgument("linestyle", borderLineStyle);
                                     hFile << std::endl;}
        // *INDENT-ON*

        m_key.writeKeyDescriptor(hFile);

        hFile << (parametric    ? "" : "un") << "set parametric" << std::endl;
        hFile << std::endl;
    }
}
