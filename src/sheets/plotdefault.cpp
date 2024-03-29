#include "plotdefault.h"

#include "../base/util.h"
#include "../dataview/dataviewdefaultseparate.h"

namespace Plotypus
{
    PlotDefault::PlotDefault() :
        AbstractPlot(SheetType::PlotDefault)
    {
        axes[AxisType::X] = AxisDescriptor(AxisType::X);
        axes[AxisType::Y] = AxisDescriptor(AxisType::Y);
    }

    PlotDefault::PlotDefault(const std::string& title) :
        AbstractPlot(SheetType::PlotDefault, title)
    {
        axes[AxisType::X] = AxisDescriptor(AxisType::X);
        axes[AxisType::Y] = AxisDescriptor(AxisType::Y);
    }

    void PlotDefault::abstractToken() {}

    // ====================================================================== //

    PlotDefault& PlotDefault::reset()
    {
        AbstractPlot::reset();

        axes.clear();
        polar = false;

        return *this;
    }

    // ====================================================================== //

    const std::unordered_map<AxisType, AxisDescriptor>& PlotDefault::getAxes() const
    {
        return axes;
    }

    PlotDefault& PlotDefault::setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes)
    {
        axes = newAxes;
        return *this;
    }

    AxisDescriptor& PlotDefault::axis(const AxisType axisID)
    {
        // *INDENT-OFF*
        if (axisID == AxisType::Undefined) {throw UnsupportedOperationError("Cannot operate on undefined axis");}
        if (!axes.contains(axisID)) {axes[axisID] = AxisDescriptor(axisID);}
        // *INDENT-ON*

        return axes[axisID];
    }

    PlotDefault& PlotDefault::clearAxes()
    {
        axes.clear();
        return *this;
    }

    PlotDefault& PlotDefault::clearAxis(const AxisType axisID)
    {
        axes.erase(axisID);
        return *this;
    }

    // ====================================================================== //

    bool PlotDefault::getMode3D() const
    {
        return mode3D;
    }

    PlotDefault& PlotDefault::setMode3D(bool newMode3D)
    {
        if (mode3D != newMode3D)
        {
            if (contains(plotStyleFamily, {PlotStyleFamily::Custom, PlotStyleFamily::Undefined}))
            {
                mode3D = newMode3D;
            }
            else
            {
                if      ( newMode3D && (plotStyleFamily == PlotStyleFamily::Orthogonal3D))
                {
                    mode3D = true;
                }
                else if (!newMode3D && (plotStyleFamily == PlotStyleFamily::Orthogonal2D))
                {
                    mode3D = false;
                }
                else
                {
                    throw IncompatiblePlotStyle("Cannot override 3D mode: not a custom plot style");
                }
            }
        }

        return *this;
    }

    bool PlotDefault::getPolar() const
    {
        return polar;
    }

    PlotDefault& PlotDefault::setPolar(bool newPolar)
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

    DataviewDefaultSeparate& PlotDefault::addDataViewSeparate(DataviewDefaultSeparate* dataView)
    {
        checkAndSetStyleFamily(dataView->getPlotStyleFamily(), allowedStyleFamiles);

        // *INDENT-OFF*
        if      (plotStyleFamily == PlotStyleFamily::Orthogonal2D) {setMode3D(false);}
        else if (plotStyleFamily == PlotStyleFamily::Orthogonal3D) {setMode3D(true) ;}
        // *INDENT-ON*

        return *static_cast<DataviewDefaultSeparate*>(DataviewCollection::addDataview(dataView));
    }

    DataviewDefaultSeparate& PlotDefault::addDataviewDefaultSeparate(const PlotStyle style, const std::string& label)
    {
        return addDataViewSeparate( new DataviewDefaultSeparate(style, label) );
    }

    DataviewDefaultSeparate& PlotDefault::addDataviewDefaultSeparate(const std::span<double>& dataY, const PlotStyle style, const std::string& label)
    {
        DataviewDefaultSeparate* dataView = new DataviewDefaultSeparate(style, label);

        dataView->setData(ColumnType::Y, dataY);

        return addDataViewSeparate(dataView);
    }

    DataviewDefaultSeparate& PlotDefault::addDataviewDefaultSeparate(const std::span<double>& dataX, const std::span<double>& dataY, const PlotStyle style, const std::string& label)
    {
        DataviewDefaultSeparate* dataView = new DataviewDefaultSeparate(style, label);

        dataView->setData(ColumnType::X, dataX);
        dataView->setData(ColumnType::Y, dataY);

        return addDataViewSeparate(dataView);
    }

    DataviewDefaultSeparate& PlotDefault::addDataviewDefaultSeparate(const std::string& func, const PlotStyle style, const std::string& label)
    {
        DataviewDefaultSeparate* dataView = new DataviewDefaultSeparate(style, label);

        dataView->setFunc(func);

        return addDataViewSeparate(dataView);
    }

    // ====================================================================== //
    // writers

    void PlotDefault::writeTxtData(std::ostream& hFile) const
    {
        AbstractPlot::writeTxtData(hFile);
        for (const auto dataView : dataviews)
        {
            hFile << datalineSeparatorTxt;
            dataView->writeTxtData(hFile);
        }
    }

    void PlotDefault::writeDatData() const
    {
        AbstractPlot::writeDatData();
        for (const auto dataView : dataviews)
        {
            dataView->writeDatData();
        }
    }

    void PlotDefault::writeScriptHead(std::ostream& hFile) const
    {
        AbstractPlot::writeScriptHead(hFile);

        hFile << (polar ? "" : "un") << "set polar" << std::endl;
        hFile << std::endl;

        for (const auto& [axisID, axisDescriptor] : axes)
        {
            axisDescriptor.writeAxisDescriptor(hFile);
        }

        hFile << std::endl;
    }

    void PlotDefault::writeScriptData(std::ostream& hFile, const StylesCollection& stylesCollection) const
    {
        AbstractPlot::writeScriptData(hFile, stylesCollection);

        hFile << (mode3D ? "splot " : "plot ");

        const auto viewCount = dataviews.size();
        for (size_t i = 0u; const auto dataView : dataviews)
        {
            dataView->writeScriptData(hFile, stylesCollection);
            ++i;
            if (i < viewCount)
            {
                hFile << ", \\\n\t";
            }
        }
        hFile << std::endl << std::endl;
    }

    void PlotDefault::writeScriptFooter(std::ostream& hFile, int pageNum) const
    {
        AbstractPlot::writeScriptFooter(hFile, pageNum);

        for (const auto& [axisID, axis] : axes)
        {
            axis.writeUnsetCommands(hFile);
        }

        hFile << std::endl;
    }
}
