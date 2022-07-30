#include "plotwithaxes.h"

namespace Plotypus
{

    std::string PlotWithAxes::generateRangeString(double min, double max)
    {
        return "[" +
               (std::isnan(min) ? "*" : std::to_string(min)) +
               ":" +
               (std::isnan(max) ? "*" : std::to_string(max)) +
               "] ";
    }

    std::string PlotWithAxes::generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax)
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
            case 3  : return " " + std::to_string(min) + ", " + std::to_string(increment) + ", " + std::to_string(max) + " ";
            default : return "";
        }

        // *INDENT-ON*
    }

    std::string PlotWithAxes::generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add)
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

    void PlotWithAxes::writeAxisLabel(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis)
    {
        if (!hasAxisLabel(axis.type))
        {
            return;
        }

        const std::string axisCommand = axisName  + "label ";

        if (axis.labelText.has_value())
        {
            hFile << "set " << axisCommand
                  << std::quoted(axis.labelText.value()) << " "
                  << optionalQuotedTextString("font", axis.labelFont)
                  << optionalQuotedTextString("textcolor", axis.labelColor)
                  << axis.labelOptions.value_or("")
                  << std::endl;
        }
    }

    void PlotWithAxes::writeAxisRange(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis)
    {
        const std::string axisCommand = axisName + "range ";
        const std::string rangeString = generateRangeString (axis.rangeMin, axis.rangeMax);

        hFile << "set " << axisCommand << " " << rangeString << axis.rangeOptions.value_or("") << std::endl;
    }

    void PlotWithAxes::writeAxisTics(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis)
    {
        const std::string axisCommand  = axisName + "tics ";

        const std::string ticsSequenceString = generateTicsSequence(axis.ticsStart, axis.ticsIncrement, axis.ticsEnd, axis.rangeMin, axis.rangeMax);
        const std::string ticsListString     = generateTicsList    (axis.ticsLabels, !ticsSequenceString.empty());

        if (axis.tics)
        {
            hFile << "set " << axisCommand
                  << ticsSequenceString
                  << ticsListString
                  << (axis.ticsLogscale ? "logscale " : "nologscale ")
                  << optionalQuotedTextString("font", axis.ticsFont)
                  << optionalQuotedTextString("textcolor", axis.ticsTextColor)
                  << axis.ticsOptions.value_or("")
                  << std::endl;
        }
        else
        {
            hFile << "unset " << axisCommand << std::endl;
        }

        if (axis.minorTics)
        {
            hFile << "set m" << axisCommand
                  << (axis.minorTicsIntervals == AXIS_AUTO_MINOR_TICS ? "" : " " + std::to_string(axis.minorTicsIntervals));
        }
        else
        {
            hFile << "unset m" << axisCommand << std::endl;
        }

        hFile << std::endl;
    }

    // ====================================================================== //

    PlotWithAxes::PlotWithAxes(const std::string& title) :
        Plot(title)
    {
        type = PlotType::Plot2D;

        axes[AxisType::X] = AxisDescriptor(AxisType::X);
        axes[AxisType::Y] = AxisDescriptor(AxisType::Y);
    }

    PlotWithAxes::~PlotWithAxes()
    {
        for (auto dataView : dataViews)
        {
            delete dataView;
        }
    }

    // ====================================================================== //

    void PlotWithAxes::reset()
    {
        Plot::reset();

        axes.clear();
        polar = false;
    }

    // ====================================================================== //

    const std::unordered_map<AxisType, AxisDescriptor>& PlotWithAxes::getAxes() const
    {
        return axes;
    }

    void PlotWithAxes::setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes)
    {
        axes = newAxes;
    }

    AxisDescriptor& PlotWithAxes::axis(const AxisType axisID)
    {
        if (!axes.contains(axisID))
        {
            axes[axisID] = AxisDescriptor(axisID);
        }

        return axes[axisID];
    }

    void PlotWithAxes::clearAxes()
    {
        axes.clear();
    }

    void PlotWithAxes::clearAxis(const AxisType axisID)
    {
        axes.erase(axisID);
    }

    AxisDescriptor& PlotWithAxes::xAxis()
    {
        return axis(AxisType::X);
    }

    AxisDescriptor& PlotWithAxes::yAxis()
    {
        return axis(AxisType::Y);
    }

    // ====================================================================== //

    bool PlotWithAxes::getPolar() const
    {
        return polar;
    }

    void PlotWithAxes::setPolar(bool newPolar)
    {
        polar = newPolar;

        if (polar)
        {
            // *INDENT-OFF*
            if (axes.contains(AxisType::X)) {axes.erase(AxisType::Y);}
            if (axes.contains(AxisType::Y)) {axes.erase(AxisType::X);}
            // *INDENT-ON*

            axes[AxisType::Radius]                      = AxisDescriptor(AxisType::Radius);
            auto& thetaAxes = axes[AxisType::Azimuthal] = AxisDescriptor(AxisType::Azimuthal);
            thetaAxes.ticsIncrement = 30;
            border = BorderLine::Polar;
        }
        else
        {

        }
    }

    // ====================================================================== //
    // writers

    void PlotWithAxes::preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const
    {
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

    void PlotWithAxes::writeTxtData(std::ostream& hFile) const
    {
        Plot::writeTxtData(hFile);
        for (const auto dataView : dataViews)
        {
            hFile << datalineSeparatorTxt;
            dataView->writeTxtData(hFile);
        }
    }

    void PlotWithAxes::writeDatData() const
    {
        Plot::writeDatData();
        for (const auto dataView : dataViews)
        {
            dataView->writeDatData();
        }
    }

    void PlotWithAxes::writeScriptHead(std::ostream& hFile) const
    {
        Plot::writeScriptHead(hFile);

        hFile << (polar ? "" : "un") << "set polar" << std::endl;
        hFile << std::endl;

        for (const auto& [axisID, axisDescriptor] : axes)
        {
            writeAxisDescriptor(hFile, axisDescriptor);
        }

        hFile << std::endl;
    }

    void PlotWithAxes::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
    {
        Plot::writeScriptData(hFile, stylesColloction);

        hFile << "plot ";
        const auto viewCount = dataViews.size();
        for (size_t i = 0u; const auto dataView : dataViews)
        {
            dataView->writeScriptData(hFile, stylesColloction);
            ++i;
            if (i < viewCount)
            {
                hFile << ", \\\n\t";
            }
        }
        hFile << std::endl;
    }

    void PlotWithAxes::writeScriptFooter(std::ostream& hFile, int pageNum) const
    {
        Plot::writeScriptFooter(hFile, pageNum);
        hFile << std::endl;
    }

    void PlotWithAxes::writeAxisDescriptor(std::ostream& hFile, const AxisDescriptor& axis) const
    {
        const std::string axisName = getAxisName(axis.type);
        writeAxisLabel(hFile, axisName, axis);
        writeAxisRange(hFile, axisName, axis);
        writeAxisTics (hFile, axisName, axis);
    }
}
