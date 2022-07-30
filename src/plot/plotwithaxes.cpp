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
            case 3  : return " " + std::to_string(min) + ", " + std::to_string(increment) + "+" + std::to_string(max) + " ";
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

    // ====================================================================== //

    PlotWithAxes::PlotWithAxes(const std::string& title) :
        Plot(title)
    {
        type = PlotType::Plot2D;
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

        m_xAxis = AxisDescriptor("x");
        m_yAxis = AxisDescriptor("y");

        polar   = false;
    }

    AxisDescriptor& PlotWithAxes::xAxis()
    {
        return m_xAxis;
    }

    AxisDescriptor& PlotWithAxes::yAxis()
    {
        return m_yAxis;
    }

    bool PlotWithAxes::getPolar() const
    {
        return polar;
    }

    void PlotWithAxes::setPolar(bool newPolar)
    {
        polar = newPolar;
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

        hFile << (polar         ? "" : "un") << "set polar" << std::endl;
        hFile << std::endl;

        writeAxisDescriptor(hFile, "x", m_xAxis);
        writeAxisDescriptor(hFile, "y", m_yAxis);

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

    void PlotWithAxes::writeAxisDescriptor(std::ostream& hFile, const std::string& axis, const AxisDescriptor& label) const
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
}