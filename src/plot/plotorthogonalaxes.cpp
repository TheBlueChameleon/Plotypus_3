#include "plotorthogonalaxes.h"

namespace Plotypus
{
    PlotOrthogonalAxes::PlotOrthogonalAxes() :
        Plot(SheetType::PlotOrthogonalAxis)
    {
        axes[AxisType::X] = AxisDescriptor(AxisType::X);
        axes[AxisType::Y] = AxisDescriptor(AxisType::Y);
    }

    PlotOrthogonalAxes::PlotOrthogonalAxes(const std::string& title) :
        Plot(SheetType::PlotOrthogonalAxis, title)
    {
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

    PlotOrthogonalAxes& PlotOrthogonalAxes::reset()
    {
        Plot::reset();

        axes.clear();
        polar = false;

        return *this;
    }

    // ====================================================================== //

    const std::unordered_map<AxisType, AxisDescriptor>& PlotOrthogonalAxes::getAxes() const
    {
        return axes;
    }

    PlotOrthogonalAxes& PlotOrthogonalAxes::setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes)
    {
        axes = newAxes;
        return *this;
    }

    AxisDescriptor& PlotOrthogonalAxes::axis(const AxisType axisID)
    {
        // *INDENT-OFF*
        if (axisID == AxisType::Undefined) {throw UnsupportedOperationError("Cannot operate on undefined axis");}
        if (!axes.contains(axisID)) {axes[axisID] = AxisDescriptor(axisID);}
        // *INDENT-ON*

//        std::cout <<

        return axes[axisID];
    }

    PlotOrthogonalAxes& PlotOrthogonalAxes::clearAxes()
    {
        axes.clear();
        return *this;
    }

    PlotOrthogonalAxes& PlotOrthogonalAxes::clearAxis(const AxisType axisID)
    {
        axes.erase(axisID);
        return *this;
    }

    // ====================================================================== //

    bool PlotOrthogonalAxes::getMode3D() const
    {
        return mode3D;
    }

    PlotOrthogonalAxes& PlotOrthogonalAxes::setMode3D(bool newMode3D)
    {
        if (mode3D != newMode3D)
        {
            // *INDENT-OFF*
            if (contains(plotStyleFamily, {PlotStyleFamily::Custom, PlotStyleFamily::Undefined}))   {mode3D = newMode3D;}
            else                                                                                    {throw IncompatiblePlotStyle("Cannot override 3D mode: not a custom plot style");}
            // *INDENT-ON*
        }

        return *this;
    }

    bool PlotOrthogonalAxes::getPolar() const
    {
        return polar;
    }

    PlotOrthogonalAxes& PlotOrthogonalAxes::setPolar(bool newPolar)
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
            thetaAxes.setTicsIncrement(30);

            border = BorderLine::Polar;
        }
        else
        {
            // *INDENT-OFF*
            if (axes.contains(AxisType::Radial))    {axes.erase(AxisType::Radial);}
            if (axes.contains(AxisType::Azimuthal)) {axes.erase(AxisType::Azimuthal);}
            // *INDENT-ON*

            axes[AxisType::X] = AxisDescriptor(AxisType::X);
            axes[AxisType::Y] = AxisDescriptor(AxisType::Y);

            border = (mode3D ? BORDERS_2D_DEFAULT : BORDERS_3D_DEFAULT);
        }

        return *this;
    }

    // ====================================================================== //
    // dataview adders

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(DataViewDefaultSeparate* dataView)
    {
        checkAndSetStyleFamily(dataView->getPlotStyleFamily(), allowedStyleFamiles);

        // *INDENT-OFF*
        if      (plotStyleFamily == PlotStyleFamily::Orthogonal2D) {setMode3D(false);}
        else if (plotStyleFamily == PlotStyleFamily::Orthogonal3D) {setMode3D(true) ;}
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

        dataView->setData(ColumnType::Y, dataY);

        return addDataViewSeparate(dataView);
    }

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(const std::span<double>& dataX, const std::span<double>& dataY, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultSeparate* dataView = new DataViewDefaultSeparate(style, label);

        dataView->setData(ColumnType::X, dataX);
        dataView->setData(ColumnType::Y, dataY);

        return addDataViewSeparate(dataView);
    }

    DataViewDefaultSeparate& PlotOrthogonalAxes::addDataViewSeparate(const std::string& func, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultSeparate* dataView = new DataViewDefaultSeparate(style, label);

        dataView->setFunc(func);

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
            axisDescriptor.writeAxisDescriptor(hFile);
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
            axis.writeUnsetCommands(hFile);
        }

        hFile << std::endl;
    }
}
