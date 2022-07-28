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
               "] ";
    }

    std::string Plot::generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax)
    {
        size_t argForm = 3;

        // *INDENT-OFF*

        /* check for: no generated tics via symbol:
         * AXIS_NO_AUTO_TICS = std::numeric_limits<double>::infinity(); */

        if (std::isinf(min))       {return "";}
        if (std::isinf(max))       {return "";}
        if (std::isinf(increment)) {return "";}

        /* check for: auto ranged tics via symbol:
         * AXIS_AUTO_RANGE = std::numeric_limits<double>::quiet_NaN(); */

        if (std::isnan(min))       {min = rangeMin;}
        if (std::isnan(max))       {max = rangeMax;}
        if (std::isnan(increment)) {increment = 1.;}

        /* determine which form of the following options will be chosen:
         *   set tics start, increment, stop
         *   set tics start, increment
         *   set tics increment
         * return null if none of them is met
         */

        if (std::isnan(min))       {--argForm;}
        if (std::isnan(max))       {--argForm;}
        if (std::isnan(increment)) {--argForm;}

        if (argForm == 1 &&  std::isnan(increment)) {return "";}
        if (argForm == 2 && !std::isnan(max))       {return "";}

        switch (argForm)
        {
            case 1  : return " " +                              std::to_string(increment)                             + " ";
            case 2  : return " " + std::to_string(min) + ", " + std::to_string(increment)                             + " ";
            case 3  : return " " + std::to_string(min) + ", " + std::to_string(increment) + "+" + std::to_string(max) + " ";
            default : return "";
        }

        // *INDENT-ON*
    }

    std::string Plot::generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add)
    {
        std::string result = (add ? "add " : "");

        // *INDENT-OFF*
        if (tics.empty()) {return "";}
        else              {result += "(";}
        // *INDENT-ON*

        const size_t N = tics.size();
        for (size_t i = 1u; const auto& [text, pos] : tics)
        {
            result += text + " " + std::to_string(pos);
            result += (i < N ? ", " : "");
        }
        result += ") ";

        return result;
    }

    Plot::Plot(const std::string& title) :
        Sheet(title)
    {}

    void Plot::reset()
    {
        Sheet::reset();

        m_xAxis       = AxisDescriptor("x");
        m_yAxis       = AxisDescriptor("y");

        key         = true;
        border      = true;
        parametric  = false;
        polar       = false;
        aspect      = "ratio -1";
    }

    AxisDescriptor& Plot::xAxis()
    {
        return m_xAxis;
    }

    AxisDescriptor& Plot::yAxis()
    {
        return m_yAxis;
    }

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

    void Plot::writeAxisDescriptor(std::ostream& hFile, const std::string& axis, const AxisDescriptor& label) const
    {
        const std::string alabel = axis + "label ";
        const std::string arange = axis + "range ";
        const std::string atics  = axis + "tics ";

        const std::string rangeString        = generateRangeString (label.rangeMin, label.rangeMax);
        const std::string ticsSequenceString = generateTicsSequence(label.ticsStart, label.ticsIncrement, label.ticsEnd, label.rangeMin, label.rangeMax);
        const std::string ticsListString     = generateTicsList    (label.ticsLabels, !ticsSequenceString.empty());

        // *INDENT-OFF*
        if (label.label)    {hFile <<   "set " << alabel
                                                << std::quoted(label.labelText) << " "
                                                << optionalQuotedTextString("font"     , label.labelFont)
                                                << optionalQuotedTextString("textcolor", label.labelColor)
                                                << label.labelOptions
                                                << std::endl;}
        else                {hFile << "unset " << alabel << std::endl;}

        hFile << "set " << arange << " " << rangeString << label.rangeOptions << std::endl;

        if (label.tics) {hFile << "set " << atics
                                << ticsSequenceString
                                << ticsListString
                                << (label.ticsLogscale ? "logscale " : "nologscale ")
                                << optionalQuotedTextString("font"     , label.ticsFont)
                                << optionalQuotedTextString("textcolor", label.ticsTextColor)
                                << label.ticsOptions
                                << std::endl;}
        else            {hFile << "unset " << atics << std::endl;}

        if (label.minorTics) {hFile << "set m" << atics
                                    << (label.minorTicsIntervals == AXIS_AUTO_MINOR_TICS ? "" : " " + std::to_string(label.minorTicsIntervals));}
        else                 {hFile << "unset m" << atics << std::endl;}

        hFile << std::endl;

        // *INDENT-ON*
    }

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
        hFile << (polar         ? "" : "un") << "set polar" << std::endl;
        hFile << std::endl;

        writeAxisDescriptor(hFile, "x", m_xAxis);
        writeAxisDescriptor(hFile, "y", m_yAxis);

        hFile << std::endl;
    }
}
