#include <iomanip>
#include <string>

#include "plot.h"

using namespace std::string_literals;
using namespace Plotypus;

namespace Plotypus
{
    Plot::Plot(const std::string& title) :
        Sheet(title)
    {}

    const std::string& Plot::getXLabel() const
    {
        return xLabel;
    }

    void Plot::setXLabel(const std::string& newXLabel)
    {
        xLabel = newXLabel;
    }

    const std::string& Plot::getYLabel() const
    {
        return yLabel;
    }

    void Plot::setYLabel(const std::string& newYLabel)
    {
        yLabel = newYLabel;
    }

    bool Plot::getXTicks() const
    {
        return xTicks;
    }

    void Plot::setXTicks(bool newXAxis)
    {
        xTicks = newXAxis;
    }

    double Plot::getXRangeMin() const
    {
        return xRangeMin;
    }

    void Plot::setXRangeMin(double newXRangeMin)
    {
        xRangeMin = newXRangeMin;
    }

    double Plot::getXRangeMax() const
    {
        return xRangeMax;
    }

    void Plot::setXRangeMax(double newXRangeMax)
    {
        xRangeMax = newXRangeMax;
    }

    int Plot::getXRangeStride() const
    {
        return xRangeStride;
    }

    void Plot::setXRangeStride(int newXRangeStride)
    {
        xRangeStride = newXRangeStride;
    }

    bool Plot::getYTicks() const
    {
        return yTicks;
    }

    void Plot::setYTicks(bool newYAxis)
    {
        yTicks = newYAxis;
    }

    double Plot::getYRangeMin() const
    {
        return yRangeMin;
    }

    void Plot::setYRangeMin(double newYRangeMin)
    {
        yRangeMin = newYRangeMin;
    }

    double Plot::getYRangeMax() const
    {
        return yRangeMax;
    }

    void Plot::setYRangeMax(double newYRangeMax)
    {
        yRangeMax = newYRangeMax;
    }

    int Plot::getYRangeStride() const
    {
        return yRangeStride;
    }

    void Plot::setYRangeStride(int newYRangeStride)
    {
        yRangeStride = newYRangeStride;
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

    void Plot::writePdfHead(std::ofstream& hFile)
    {
        Sheet::writePdfHead(hFile);

        if (!aspect.empty())
        {
            hFile << "set size " << aspect << std::endl;
        }

        hFile << "set key " << (key ? "on" : "off") << std::endl;
        hFile << (border ? "" : "un") << "set border" << std::endl;
        hFile << (xTicks ? "" : "un") << "set xtics"  << std::endl;
        hFile << "set xlabel " << std::quoted(xLabel) << std::endl;
        hFile << (yTicks ? "" : "un") << "set ytics"  << std::endl;
        hFile << "set ylabel " << std::quoted(yLabel) << std::endl;

        hFile << "set xrange[0:1]" << std::endl;
        hFile << "set yrange[1:0]" << std::endl;

        hFile << std::endl;
    }
}
