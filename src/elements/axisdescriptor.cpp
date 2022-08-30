#include "axisdescriptor.h"

namespace Plotypus
{
    std::string AxisDescriptor::generateRangeString(const std::optional<double>& min, const std::optional<double>& max) const
    {
        const std::string asterisk = "*";

        return "[" +
               optionalNumberAsString(min, asterisk) +
               ":" +
               optionalNumberAsString(max, asterisk) +
               "] ";
    }

    std::string AxisDescriptor::generateTicsSequence(const std::optional<double>& min, const std::optional<double>& increment, const std::optional<double>& max, const std::optional<double>& rangeMin, const std::optional<double>& rangeMax) const
    {
        // *INDENT-OFF*

        if (!ticsAuto) {return "";}

        double localMin       = rangeMin .value_or(OPTIONAL_DOUBLE_DEFAULT);
        double localMax       = rangeMax .value_or(OPTIONAL_DOUBLE_DEFAULT);
        double localIncrement = increment.value_or(OPTIONAL_DOUBLE_DEFAULT);

        /* determine which form of the following options will be chosen:
         *   set tics start, increment, stop
         *   set tics start, increment
         *   set tics increment
         * return nullstring if none of them is met
         */

        size_t argForm = 3;
        if (std::isnan(localMin))       {--argForm;}                // OPTIONAL_DOUBLE_DEFAULT is std::numeric_limits<double>::quiet_NaN();
        if (std::isnan(localMax))       {--argForm;}
        if (std::isnan(localIncrement)) {--argForm;}

        if (argForm == 1 &&  std::isnan(localIncrement)) {return "";}
        if (argForm == 2 && !std::isnan(localMax))       {return "";}

        switch (argForm)
        {
            case 1  : return " " +                                   std::to_string(localIncrement)                                   + " ";
            case 2  : return " " + std::to_string(localMin) + ", " + std::to_string(localIncrement)                                   + " ";
            case 3  : return " " + std::to_string(localMin) + ", " + std::to_string(localIncrement) + ", " + std::to_string(localMax) + " ";
            default : return "";
        }

        // *INDENT-ON*
    }

    std::string AxisDescriptor::generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add) const
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

    void AxisDescriptor::writeAxisLabel(std::ostream& hFile, const std::string& axisName) const
    {
        if (!hasAxisLabel(type))
        {
            return;
        }

        const std::string axisCommand = axisName  + "label ";

        if (labelText.has_value())
        {
            hFile << "set " << axisCommand
                  << std::quoted(labelText.value()) << " "
                  << optionalQuotedStringArgument("font", labelFont)
                  << optionalQuotedStringArgument("textcolor", labelColor)
                  << labelOptions.value_or("")
                  << std::endl;
        }
    }

    void AxisDescriptor::writeAxisRange(std::ostream& hFile, const std::string& axisName) const
    {
        const std::string axisCommand = axisName + "range ";
        const std::string rangeString = generateRangeString(rangeMin, rangeMax);

        hFile << "set " << axisCommand << rangeString << rangeOptions.value_or("") << std::endl;
    }

    void AxisDescriptor::writeAxisTics(std::ostream& hFile, const std::string& axisName) const
    {
        const std::string axisCommand  = axisName + "tics ";

        const std::string ticsSequenceString = generateTicsSequence(ticsStart, ticsIncrement, ticsEnd, rangeMin, rangeMax);
        const std::string ticsListString     = generateTicsList    (ticsLabels, !ticsSequenceString.empty());

        if (tics)
        {
            hFile << "set " << axisCommand
                  << ticsSequenceString
                  << ticsListString
                  << (ticsLogscale ? "logscale " : "nologscale ")
                  << optionalQuotedStringArgument("font", ticsFont)
                  << optionalQuotedStringArgument("textcolor", ticsTextColor)
                  << ticsOptions.value_or("")
                  << std::endl;
        }

        if (minorTics)
        {
            hFile << "set m" << axisCommand
                  << (minorTicsIntervals.has_value() ? std::to_string(minorTicsIntervals.value()) : "");
        }
    }

    void AxisDescriptor::writeAxisGrid(std::ostream& hFile, const std::string& axisName, bool off) const
    {
        if (!contains(axisName, {"x", "x2", "y", "y2", "z", "r", "cb"}))
        {
            return;
        }

        const std::string gridCommand  = axisName + "tics ";

        // *INDENT-OFF*
        if (gridMajor) {hFile << "set grid " << (off ? "no" : "") <<        gridCommand << gridMajorOptions.value_or("") << std::endl;}
        if (gridMinor) {hFile << "set grid " << (off ? "no" : "") << "m" << gridCommand << gridMinorOptions.value_or("") << std::endl;}
        // *INDENT-ON*
    }

    // ====================================================================== //

    AxisDescriptor::AxisDescriptor() :
        type(AxisType::Undefined)
    {}

    AxisDescriptor::AxisDescriptor(const AxisType type, const std::string& label, double rangeMin, double rangeMax) :
        type(type), labelText(label)
    {
        setRangeMax(rangeMin);
        setRangeMax(rangeMax);

        if (type == AxisType::Azimuthal)
        {
            // *INDENT-OFF*
            if (std::isnan(rangeMin)) {this->rangeMin =   0.;}
            if (std::isnan(rangeMax)) {this->rangeMax = 360.;}
            // *INDENT-ON*
        }
    }

    AxisDescriptor::AxisDescriptor(const AxisType type, double rangeMin, double rangeMax) :
        type(type)
    {
        setRangeMax(rangeMin);
        setRangeMax(rangeMax);

        switch (type)
        {
            case AxisType::Azimuthal:
                // *INDENT-OFF*
                if (std::isnan(rangeMin)) {this->rangeMin =   0.;}
                if (std::isnan(rangeMax)) {this->rangeMax = 360.;}
                // *INDENT-ON*
                break;
            case AxisType::Colourbar:
                labelText = "z";
                break;
            case AxisType::Radial:
                labelText = "r";
                break;
            case AxisType::X:
                labelText = "x";
                break;
            case AxisType::X2:
                labelText = "x";
                break;
            case AxisType::Y:
                labelText = "y";
                break;
            case AxisType::Y2:
                labelText = "y";
                break;
            case AxisType::Z:
                labelText = "z";
                break;
            case AxisType::Undefined:
                labelText = "undefined";
                break;
        }
    }

    // ====================================================================== //

    AxisDescriptor& AxisDescriptor::reset()
    {
        tics                = true;
        ticsAuto            = true;
        ticsLogscale        = false;
        minorTics           = false;
        gridMajor           = false;
        gridMinor           = false;
        labelText.reset();
        labelFont.reset();
        labelColor.reset();
        labelOptions.reset();
        rangeMin            = 0.;
        rangeMax.reset();
        rangeOptions.reset();
        ticsStart.reset();
        ticsEnd.reset();
        ticsIncrement.reset();
        ticsFormatstring.reset();
        ticsLabels.clear();
        ticsFont.reset();
        ticsTextColor.reset();
        ticsOptions.reset();
        minorTicsIntervals.reset();
        gridMajorOptions.reset();
        gridMinorOptions.reset();

        return *this;
    }

    std::string AxisDescriptor::getLabelText() const
    {
        return labelText.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setLabelText(const std::string& newLabelText)
    {
        labelText = newLabelText;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearLabelText()
    {
        labelText.reset();
        return *this;
    }

    std::string AxisDescriptor::getLabelFont() const
    {
        return labelFont.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setLabelFont(const std::string& newLabelFont)
    {
        labelFont = newLabelFont;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearLabelFont()
    {
        labelFont.reset();
        return *this;
    }

    std::string AxisDescriptor::getLabelColor() const
    {
        return labelColor.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setLabelColor(const std::string& newLabelColor)
    {
        labelColor = newLabelColor;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearLabelColor()
    {
        labelColor.reset();
        return *this;
    }

    std::string AxisDescriptor::getLabelOptions() const
    {
        return labelOptions.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setLabelOptions(const std::string& newLabelOptions)
    {
        labelOptions = newLabelOptions;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearLabelOptions()
    {
        labelOptions.reset();
        return *this;
    }

    double AxisDescriptor::getRangeMin() const
    {
        return rangeMin.value_or(OPTIONAL_DOUBLE_DEFAULT);
    }

    AxisDescriptor& AxisDescriptor::setRangeMin(double newRangeMin)
    {
        setOptionalDoubleOrClearIfNan(rangeMin, newRangeMin);
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearRangeMin()
    {
        rangeMin.reset();
        return *this;
    }

    double AxisDescriptor::getRangeMax() const
    {
        return rangeMax.value_or(OPTIONAL_DOUBLE_DEFAULT);
    }

    AxisDescriptor& AxisDescriptor::setRangeMax(double newRangeMax)
    {
        setOptionalDoubleOrClearIfNan(rangeMax, newRangeMax);
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearRangeMax()
    {
        rangeMax.reset();
        return *this;
    }

    std::string AxisDescriptor::getRangeOptions() const
    {
        return rangeOptions.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setRangeOptions(const std::string& newRangeOptions)
    {
        rangeOptions = newRangeOptions;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearRangeOptions()
    {
        rangeOptions.reset();
        return *this;
    }

    bool AxisDescriptor::getTics() const
    {
        return tics;
    }

    AxisDescriptor& AxisDescriptor::setTics(bool newTics)
    {
        tics = newTics;
        return *this;
    }

    bool AxisDescriptor::getTicsAuto() const
    {
        return ticsAuto;
    }

    AxisDescriptor& AxisDescriptor::setTicsAuto(bool newTicsAuto)
    {
        ticsAuto = newTicsAuto;
        return *this;
    }

    double AxisDescriptor::getTicsStart() const
    {
        return ticsStart.value_or(OPTIONAL_DOUBLE_DEFAULT);
    }

    AxisDescriptor& AxisDescriptor::setTicsStart(double newTicsStart)
    {
        setOptionalDoubleOrClearIfNan(ticsStart, newTicsStart);
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsStart()
    {
        ticsStart.reset();
        return *this;
    }

    double AxisDescriptor::getTicsEnd() const
    {
        return ticsEnd.value_or(OPTIONAL_DOUBLE_DEFAULT);
    }

    AxisDescriptor& AxisDescriptor::setTicsEnd(double newTicsEnd)
    {
        setOptionalDoubleOrClearIfNan(ticsEnd, newTicsEnd);
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsEnd()
    {
        ticsEnd.reset();
        return *this;
    }

    double AxisDescriptor::getTicsIncrement() const
    {
        return ticsIncrement.value_or(OPTIONAL_DOUBLE_DEFAULT);
    }

    AxisDescriptor& AxisDescriptor::setTicsIncrement(double newTicsIncrement)
    {
        setOptionalDoubleOrClearIfNan(ticsIncrement, newTicsIncrement);
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsIncrement()
    {
        ticsIncrement.reset();
        return *this;
    }

    std::string AxisDescriptor::getTicsFormatstring() const
    {
        return ticsFormatstring.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setTicsFormatstring(const std::string& newTicsFormatstring)
    {
        ticsFormatstring = newTicsFormatstring;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsFormatstring()
    {
        ticsFormatstring.reset();
        return *this;
    }

    const std::vector<AxisDescriptor::locatedTicsLabel_t>& AxisDescriptor::getTicsLabels() const
    {
        return ticsLabels;
    }

    AxisDescriptor& AxisDescriptor::setTicsLabels(const std::vector<locatedTicsLabel_t>& newTicsLabels)
    {
        ticsLabels = newTicsLabels;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsLabels()
    {
        ticsLabels.clear();
        return *this;
    }

    bool AxisDescriptor::getTicsLogscale() const
    {
        return ticsLogscale;
    }

    AxisDescriptor& AxisDescriptor::setTicsLogscale(bool newTicsLogscale)
    {
        ticsLogscale = newTicsLogscale;
        return *this;
    }

    std::string AxisDescriptor::getTicsFont() const
    {
        return ticsFont.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setTicsFont(const std::string& newTicsFont)
    {
        ticsFont = newTicsFont;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsFont()
    {
        ticsFont.reset();
        return *this;
    }

    std::string AxisDescriptor::getTicsOptions() const
    {
        return ticsOptions.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setTicsOptions(const std::string& newTicsOptions)
    {
        ticsOptions = newTicsOptions;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearTicsOptions()
    {
        ticsOptions.reset();
        return *this;
    }

    bool AxisDescriptor::getMinorTics() const
    {
        return minorTics;
    }

    AxisDescriptor& AxisDescriptor::setMinorTics(bool newMinorTics)
    {
        minorTics = newMinorTics;
        return *this;
    }

    size_t AxisDescriptor::getMinorTicsIntervals() const
    {
        return minorTicsIntervals.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    AxisDescriptor& AxisDescriptor::setMinorTicsIntervals(size_t newMinorTicsIntervals)
    {
        setOptionalSizeTOrClearIfDefault(minorTicsIntervals, newMinorTicsIntervals);
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearMinorTicsIntervals()
    {
        minorTicsIntervals.reset();
        return *this;
    }

    bool AxisDescriptor::getGridMajor() const
    {
        return gridMajor;
    }

    AxisDescriptor& AxisDescriptor::setGridMajor(bool newGridMajor)
    {
        gridMajor = newGridMajor;
        return *this;
    }

    std::string AxisDescriptor::getGridMajorOptions() const
    {
        return gridMajorOptions.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setGridMajorOptions(const std::string& newGridMajorOptions)
    {
        gridMajorOptions = newGridMajorOptions;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearGridMajorOptions()
    {
        gridMajorOptions.reset();
        return *this;
    }

    bool AxisDescriptor::getGridMinor() const
    {
        return gridMinor;
    }

    AxisDescriptor& AxisDescriptor::setGridMinor(bool newGridMinor)
    {
        gridMinor = newGridMinor;
        return *this;
    }

    std::string AxisDescriptor::getGridMinorOptions() const
    {
        return gridMinorOptions.value_or("");
    }

    AxisDescriptor& AxisDescriptor::setGridMinorOptions(const std::string& newGridMinorOptions)
    {
        gridMinorOptions = newGridMinorOptions;
        return *this;
    }

    AxisDescriptor& AxisDescriptor::clearGridMinorOptions()
    {
        gridMinorOptions.reset();
        return *this;
    }

    // ====================================================================== //
    // writers

    void AxisDescriptor::writeAxisDescriptor(std::ostream& hFile) const
    {
        const std::string axisName = getAxisName(type);

        writeAxisLabel(hFile, axisName);
        writeAxisRange(hFile, axisName);
        writeAxisTics (hFile, axisName);
        writeAxisGrid (hFile, axisName);

        hFile << std::endl;
    }

    void AxisDescriptor::writeUnsetCommands(std::ostream& hFile) const
    {
        const std::string axisName = getAxisName(type);

        // *INDENT-OFF*
        if (hasAxisLabel(type)) {hFile << "unset " << axisName << "label" << std::endl;}
        if (tics)               {hFile << "unset " << axisName << "tics"  << std::endl;}
        if (minorTics)          {hFile << "unset " << axisName << "mtics" << std::endl;}

        writeAxisGrid (hFile, axisName, true);
        // *INDENT-ON*
    }
}
