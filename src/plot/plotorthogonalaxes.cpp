#include "plotorthogonalaxes.h"

namespace Plotypus
{
    std::string PlotOrthogonalAxes::generateRangeString(double min, double max)
    {
        return "[" +
               (std::isnan(min) ? "*" : std::to_string(min)) +
               ":" +
               (std::isnan(max) ? "*" : std::to_string(max)) +
               "] ";
    }

    std::string PlotOrthogonalAxes::generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax)
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

    std::string PlotOrthogonalAxes::generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add)
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

    void PlotOrthogonalAxes::writeAxisLabel(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis)
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

    void PlotOrthogonalAxes::writeAxisRange(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis)
    {
        const std::string axisCommand = axisName + "range ";
        const std::string rangeString = generateRangeString (axis.rangeMin, axis.rangeMax);

        hFile << "set " << axisCommand << " " << rangeString << axis.rangeOptions.value_or("") << std::endl;
    }

    void PlotOrthogonalAxes::writeAxisTics(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis)
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

        if (axis.minorTics)
        {
            hFile << "set m" << axisCommand
                  << (axis.minorTicsIntervals == AXIS_AUTO_MINOR_TICS ? "" : " " + std::to_string(axis.minorTicsIntervals));
        }

        hFile << std::endl;
    }

    // ====================================================================== //

    PlotOrthogonalAxes::PlotOrthogonalAxes(const std::string& title) :
        Plot(title)
    {
        type = SheetType::PlotOrthogonalAxis;

        axes[AxisType::X] = AxisDescriptor(AxisType::X);
        axes[AxisType::Y] = AxisDescriptor(AxisType::Y);
    }

    PlotOrthogonalAxes::~PlotOrthogonalAxes()
    {
        for (auto dataView : dataViews)
        {
            delete dataView;
        }
    }

    // ====================================================================== //

    void PlotOrthogonalAxes::reset()
    {
        Plot::reset();

        axes.clear();
        polar = false;
    }

    // ====================================================================== //

    const std::unordered_map<AxisType, AxisDescriptor>& PlotOrthogonalAxes::getAxes() const
    {
        return axes;
    }

    void PlotOrthogonalAxes::setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes)
    {
        axes = newAxes;
    }

    AxisDescriptor& PlotOrthogonalAxes::axis(const AxisType axisID)
    {
        if (!axes.contains(axisID))
        {
            axes[axisID] = AxisDescriptor(axisID);
        }

        return axes[axisID];
    }

    void PlotOrthogonalAxes::clearAxes()
    {
        axes.clear();
    }

    void PlotOrthogonalAxes::clearAxis(const AxisType axisID)
    {
        axes.erase(axisID);
    }

    AxisDescriptor& PlotOrthogonalAxes::xAxis()
    {
        return axis(AxisType::X);
    }

    AxisDescriptor& PlotOrthogonalAxes::yAxis()
    {
        return axis(AxisType::Y);
    }

    // ====================================================================== //

    bool PlotOrthogonalAxes::getMode3D() const
    {
        return mode3D;
    }

    void PlotOrthogonalAxes::setMode3D(bool newMode3D)
    {
        // *INDENT-OFF*
        if (contains(styleFamily, {PlotStyleFamily::Custom, PlotStyleFamily::Undefined}))   {mode3D = newMode3D;}
        else                                                                                {throw IncompatiblePlotStyle("Cannot override 3D mode: not a custom plot style");}
        // *INDENT-ON*
    }

    bool PlotOrthogonalAxes::getPolar() const
    {
        return polar;
    }

    void PlotOrthogonalAxes::setPolar(bool newPolar)
    {
        polar = newPolar;

        if (polar)
        {
            // *INDENT-OFF*
            if (axes.contains(AxisType::X)) {axes.erase(AxisType::X);}
            if (axes.contains(AxisType::Y)) {axes.erase(AxisType::Y);}
            // *INDENT-ON*

            axes[AxisType::Radial]                      = AxisDescriptor(AxisType::Radial);
            auto& thetaAxes = axes[AxisType::Azimuthal] = AxisDescriptor(AxisType::Azimuthal);
            thetaAxes.ticsIncrement = 30;
            border = BorderLine::Polar;
        }
        else
        {

        }
    }

    // ====================================================================== //
    // dataview adders

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(DataViewDefaultSeparate* dataView)
    {
        checkAndSetStyleFamily(dataView->getStyleFamily(), allowedStyleFamiles);

        // *INDENT-OFF*
        if      (styleFamily == PlotStyleFamily::Orthogonal2D) {mode3D = false;}
        else if (styleFamily == PlotStyleFamily::Orthogonal3D) {mode3D = true;}
        // *INDENT-ON*

        dataViews.push_back(dataView);
        return *dataView;
    }

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(const PlotStyle style, const std::string& label)
    {
        DataViewDefaultSeparate* dataView = new DataViewDefaultSeparate(style, label);
        return addDataViewSeparate(dataView);
    }

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(const std::span<double>& dataY, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultSeparate* dataView = new DataViewDefaultSeparate(style, label);

        dataView->data(ColumnType::Y) = dataY;

        return addDataViewSeparate(dataView);
    }

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(const std::span<double>& dataX, const std::span<double>& dataY, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultSeparate* dataView = new DataViewDefaultSeparate(style, label);

        dataView->data(ColumnType::X) = dataX;
        dataView->data(ColumnType::Y) = dataY;

        return addDataViewSeparate(dataView);
    }

    // ====================================================================== //
    // writers

    void PlotOrthogonalAxes::writeTxtData(std::ostream& hFile) const
    {
        Plot::writeTxtData(hFile);
        for (const auto dataView : dataViews)
        {
            hFile << datalineSeparatorTxt;
            dataView->writeTxtData(hFile);
        }
    }

    void PlotOrthogonalAxes::writeDatData() const
    {
        Plot::writeDatData();
        for (const auto dataView : dataViews)
        {
            dataView->writeDatData();
        }
    }

    void PlotOrthogonalAxes::writeScriptHead(std::ostream& hFile) const
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

    void PlotOrthogonalAxes::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
    {
        Plot::writeScriptData(hFile, stylesColloction);

        hFile << (mode3D ? "splot " : "plot ");

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
        hFile << std::endl << std::endl;
    }

    void PlotOrthogonalAxes::writeScriptFooter(std::ostream& hFile, int pageNum) const
    {
        Plot::writeScriptFooter(hFile, pageNum);

        for (const auto& [axisID, axis] : axes)
        {
            const auto axisName = getAxisName(axisID);
            // *INDENT-OFF*
            if (hasAxisLabel(axisID))   {hFile << "unset " << axisName << "label" << std::endl;}
            if (axis.tics)              {hFile << "unset " << axisName << "tics"  << std::endl;}
            if (axis.minorTics)         {hFile << "unset " << axisName << "mtics" << std::endl;}
            // *INDENT-ON*
        }

        hFile << std::endl;
    }

    void PlotOrthogonalAxes::writeAxisDescriptor(std::ostream& hFile, const AxisDescriptor& axis) const
    {
        const std::string axisName = getAxisName(axis.type);
        writeAxisLabel(hFile, axisName, axis);
        writeAxisRange(hFile, axisName, axis);
        writeAxisTics (hFile, axisName, axis);
    }
}
