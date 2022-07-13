#include <iomanip>
#include <string>

#include "plot.h"

using namespace std::string_literals;
using namespace Plotypus;

namespace Plotypus
{
    std::string Plot::generateRangeString(double min, double max)
    {
        return "[" +
               (std::isnan(min) ? "*" : std::to_string(min)) +
               ":" +
               (std::isnan(max) ? "*" : std::to_string(max)) +
               "]";
    }

    void Plot::writeAxisDescriptor(std::ostream& hFile, const std::string& axis, const AxisDescriptor& label) const
    {
        const std::string alabel = axis + "label";
        const std::string atics  = axis + "tics";
        const std::string arange = axis + "range";

        const std::string rangeString = generateRangeString(label.rangeMin, label.rangeMax);

        // *INDENT-OFF*
        if (!label.label.empty())   {hFile <<   "set " << alabel << " " << std::quoted(label.label) << " " << label.labelOptions << std::endl;}
        else                        {hFile << "unset " << alabel << std::endl;}

        if (label.tics) {hFile <<   "set " << atics << " " << label.ticsOptions << std::endl;}
        else            {hFile << "unset " << atics << std::endl;}
        // *INDENT-ON*

        hFile << "set " << arange << " " << rangeString << " " << label.rangeOptions << std::endl;
        hFile << std::endl;
    }

    Plot::Plot(const std::string& title) :
        Sheet(title)
    {}

    void Plot::reset()
    {
        Sheet::reset();

        xAxis       = {"x"};
        yAxis       = {"y"};

        key         = true;
        border      = true;
        parametric  = false;
        polar       = false;
        aspect      = "ratio -1";
    }

    AxisDescriptor& Plot::getXAxis()
    {
        return xAxis;
    }

    AxisDescriptor& Plot::getYAxis()
    {
        return yAxis;
    }

    bool Plot::getKey() const
    {
        return key;
    }

    void Plot::setKey(bool newKey)
    {
        key = newKey;
    }

    bool Plot::getBorder() const
    {
        return border;
    }

    void Plot::setBorder(bool newBorder)
    {
        border = newBorder;
    }

    bool Plot::getParametric() const
    {
        return parametric;
    }

    void Plot::setParametric(bool newParametric)
    {
        parametric = newParametric;
    }

    bool Plot::getPolar() const
    {
        return polar;
    }

    void Plot::setPolar(bool newPolar)
    {
        polar = newPolar;
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

    void Plot::writeScriptHead(std::ostream& hFile) const
    {
        Sheet::writeScriptHead(hFile);

        if (!aspect.empty())
        {
            hFile << "set size " << aspect << std::endl;
        }
        hFile << "set key " << (key ? "on" : "off") << std::endl;
        hFile << (border        ? "" : "un") << "set border" << std::endl;
        hFile << (parametric    ? "" : "un") << "set parametric" << std::endl;
        hFile << (polar         ? "" : "un") << "set polar" << std::endl;
        hFile << std::endl;

        writeAxisDescriptor(hFile, "x", xAxis);
        writeAxisDescriptor(hFile, "y", yAxis);

        hFile << std::endl;
    }
}
