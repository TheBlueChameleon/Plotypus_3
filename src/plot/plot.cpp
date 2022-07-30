#include "plot.h"

using namespace std::string_literals;
using namespace Plotypus;

namespace Plotypus
{
    Plot::Plot(const std::string& title) :
        Sheet(title)
    {}

    // ====================================================================== //

    void Plot::reset()
    {
        Sheet::reset();

        for (auto dataView : dataViews)
        {
            delete dataView;
        }
        dataViews.clear();

        key         = true;
        border      = true;
        parametric  = false;
        aspect      = "ratio -1";
    }

    // ====================================================================== //

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

    void Plot::setBorder(size_t newBorder)
    {
        border = newBorder;
    }

    size_t Plot::getBorderLineStyle() const
    {
        return borderLineStyle;
    }

    void Plot::setBorderLineStyle(size_t newBorderLineStyle)
    {
        borderLineStyle = newBorderLineStyle;
    }

    bool Plot::getKey() const
    {
        return key;
    }

    void Plot::setKey(bool newKey)
    {
        key = newKey;
    }

    bool Plot::getParametric() const
    {
        return parametric;
    }

    void Plot::setParametric(bool newParametric)
    {
        parametric = newParametric;
    }

    const std::string& Plot::getAspect() const
    {
        return aspect;
    }

    void Plot::setAspect(const std::string& newAspect)
    {
        aspect = newAspect;
    }

    void Plot::setAspectNone()
    {
        aspect = "noratio";
    }

    void Plot::setAspectSquare()
    {
        aspect = "square";
    }

    void Plot::setAspectEqual()
    {
        aspect = "ratio -1";
    }

    void Plot::setAspectRatio(double ratio)
    {
        aspect = "ratio "s + std::to_string(ratio);
    }

    const std::string& Plot::getFill() const
    {
        return fill;
    }

    void Plot::setFill(const std::string& newFill)
    {
        fill = newFill;
    }

    // ====================================================================== //
    // writers

    void Plot::writeScriptHead(std::ostream& hFile) const
    {
        Sheet::writeScriptHead(hFile);

        // *INDENT-OFF*
        if (!aspect.empty()) {hFile << "set size " << aspect << std::endl;}
        if (!fill.  empty()) {hFile << "set style fill " << fill << std::endl;}

        if (border == BORDERS_NONE) {hFile << "unset border" << std::endl;}
        else                        {hFile <<   "set border " << border;
                                     hFile << optionalStyleString("linestyle", borderLineStyle);
                                     hFile << std::endl;}
        // *INDENT-ON*

        hFile << "set key " << (key ? "on" : "off") << std::endl;
        hFile << (parametric    ? "" : "un") << "set parametric" << std::endl;
        hFile << std::endl;
    }
}
