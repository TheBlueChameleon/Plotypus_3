#include <iostream>

#include "showcase.h"
#include "../plotypus.h"

using namespace std::string_literals;

// ========================================================================== //
// data types and constants

const auto pi = std::numbers::pi;

struct compound_t
{
    double x, y, z, errX, errY;
};

// ========================================================================== //
// data generators

std::pair<std::vector<double>, std::vector<double>> generateSeparateData2D()
{
    // non-uniform sampling of the x domain, resulting in a sigmoid

    std::vector<double> dataX, dataY;

    size_t i = -1;
    for (double x = -1.; x < 1.;)
    {
        x += 0.1 * std::sqrt( std::abs(x) );
        ++i;

        dataX.push_back((x + 1.) * .5 * pi);
        dataY.push_back(.05 * i - 1);
    }

    return std::make_pair(dataX, dataY);
}

std::vector<compound_t> generateCompoundData2D()
{
    const auto N = 50;
    const auto xIncrement = pi / N;
    std::vector<compound_t> result(N);

    // Taylor approximation of sine
    for (double x = 0.; auto& datapoint : result)
    {
        datapoint.x    = x;
        datapoint.y    = x - (x*x*x / 6.) + (x*x*x*x*x / 120.);
        datapoint.errX = 0.01 + 0.04 * std::sin(x / 2.);
        datapoint.errY = std::abs(datapoint.y - std::sin(x)) * 1.1;

        x += xIncrement;
    }

    return result;
}

// ========================================================================== //
// internal showcase procs

void showcase_run_overlays(Plotypus::Report& report);
void showcase_run_plots2d (Plotypus::Report& report,
                           std::pair<std::vector<double>, std::vector<double>>& separate_data,
                           std::vector<compound_t>& compound_data);

// ========================================================================== //
// exposed interface

void showcase_run(Showcases selection)
{
    // ---------------------------------------------------------------------- //
    // prepare report, i.e. the primary object

    Plotypus::Report report = Plotypus::Report(Plotypus::FileType::Pdf);
    report.setOutputDirectory("TestOutput");

    // ---------------------------------------------------------------------- //
    // prepare some data (so they persist in memory until we write the report)

    std::pair<std::vector<double>, std::vector<double>> separate_data;
    std::vector<compound_t>                             compound_data;

    // ---------------------------------------------------------------------- //
    // run desired showcase options; this invokes generation of data as well.

    if (selection & Showcases::Overlays)
    {
        showcase_run_overlays(report);
    }
    if (selection & Showcases::Plots_2D)
    {
        separate_data = generateSeparateData2D();
        compound_data = generateCompoundData2D();
        showcase_run_plots2d (report, separate_data, compound_data);
    }

    // ---------------------------------------------------------------------- //
    // write the report

    report.writeTxt();
    report.writeDat();
    report.writeScript();
}

// ========================================================================== //
// showcases

void showcase_run_overlays(Plotypus::Report& report)
{
    using namespace Plotypus;

    auto& stylesCollection = report.stylesCollection();

    int boxStyleOffset = stylesCollection.getBoxStyleCount();

    stylesCollection.addBoxStyle("cyan", true, "blue");
    stylesCollection.addBoxStyle("", true, "blue");

    // ---------------------------------------------------------------------- //
    // Sheet 1: text boxes

    auto& sheet1 = report.addSheet("text overlay features");

    sheet1.addLabel("FOO BAR", .10, .10);
    sheet1.addLabel("auto-boxed", .30, .10, true);
    sheet1.addLabel("explicitly boxed", .50, .10, true, boxStyleOffset);


    sheet1.addLabel("normal text", .10, .20).textcolor = "blue";
    sheet1.addLabel("abcdefghijklmnopqrstuvwxyz01234567890  ", .10, .26, true);
    sheet1.addLabel("ABCDEFGHIJKLMNOPQRSTUVWXYZ=!\"§$%&/()= ", .10, .32, true);

    sheet1.addLabel("greek font", .10, .45).textcolor = "blue";
    sheet1.addLabel("{/symbol abcdefghijklmnopqrstuvwxyz01234567890} ", .10, .51, true);
    sheet1.addLabel("{/symbol ABCDEFGHIJKLMNOPQRSTUVWXYZ=!\"§$%&/()=}", .10, .57, true);

    sheet1.addLabel("dingbats font", .10, .70).textcolor = "blue";
    sheet1.addLabel("{/zapfdingbats abcdefghijklmnopqrstuvwxyz01234567890}", .10, .76, true);
    sheet1.addLabel("{/zapfdingbats ABCDEFGHIJKLMNOPQRSTUVWXYZ=!\"§$%&/()=}", .10, .82, true);

    sheet1.addLabel("some special symbols", .70, .20).textcolor = "blue";
    sheet1.addLabel(""s + SYMBOL_FORALL + SYMBOL_ALPHA + SYMBOL_DOT + "5" + SYMBOL_HBAR, .70, .26, true);

    sheet1.addLabel("implicitly escaping symbols", .70, .45).textcolor = "blue";
    sheet1.addLabel(""s
                    + SYMBOL_TILDE + "a"
                    + SYMBOL_FORWARD_SLASH + "a"
                    + SYMBOL_BACKWARD_SLASH + "a"
                    + SYMBOL_AMPERSAND + "a"
                    + SYMBOL_AT + "ax"
                    + SYMBOL_CURLY_BRACE_OPEN + "a" + SYMBOL_CURLY_BRACE_CLOSE,
                    .70, .51, true);
}

void showcase_run_plots2d(Plotypus::Report& report,
                          std::pair<std::vector<double>, std::vector<double> >& separate_data,
                          std::vector<compound_t>& compound_data)
{
    using namespace Plotypus;

    // ---------------------------------------------------------------------- //
    // set up some styles

    auto& stylesCollection = report.stylesCollection();
    int linesStyleOffset = stylesCollection.getLineStyleCount();
    int pointStyleOffset = stylesCollection.getPointStyleCount();

    stylesCollection.addLineStyle("blue",   2.5, "..-", PointForm::Circle);
    stylesCollection.addLineStyle("yellow", 0.1, "",    PointForm::None  );

    stylesCollection.addPointStyle(PointForm::Diamond, 0.5, "gold");

    // ---------------------------------------------------------------------- //
    // normally, we would get separate data in individual std::vector<double>s

    auto& [sepData_X, sepData_Y] = separate_data;

    // ---------------------------------------------------------------------- //
    // for compound data: prepare selectors

    using compound_selector_t = DataSelector_t<compound_t>;
    using compound_view_t     = DataViewDefaultCompound<compound_t>;

    // *INDENT-OFF*
    compound_selector_t compoundSelectorX    = [] (const compound_t& data) {return data.x;};
    compound_selector_t compoundSelectorY    = [] (const compound_t& data) {return data.y;};
    compound_selector_t compoundSelectorErrX = [] (const compound_t& data) {return data.errX;};
    compound_selector_t compoundSelectorErrY = [] (const compound_t& data) {return data.errY;};
    // *INDENT-ON*


    // ---------------------------------------------------------------------- //
    // Sheet 1: cartesian line plots

    auto& sheet1 = report.addPlotOrthogonalAxes("line plot (cartesian)");

    sheet1
    .setCustomScriptBegin("# put here setup code that should be executed BEFORE the code generated by Plotypus")
    .setCustomScriptEnd  ("# put here setup code that should be executed AFTER the code generated by Plotypus");

    auto& viewLineCompound = sheet1
                             .addDataViewCompound<compound_t>(PlotStyle::YErrorLines, "Sine Approximation")
                             .setData(compound_data)
                             .setSelector(ColumnType::X,      compoundSelectorX)
                             .setSelector(ColumnType::Y,      compoundSelectorY)
                             .setSelector(ColumnType::DeltaY, compoundSelectorErrY);

    sheet1
    .addDataViewSeparate(sepData_X, sepData_Y, PlotStyle::LinesPoints)
    .setPointStyle(pointStyleOffset);

    sheet1.addDataViewCompound<compound_t>("[0:pi] sin(x)", PlotStyle::Lines, "Sine Wave");
    sheet1.addDataViewCompound<compound_t>("[0:pi] cos(x)", PlotStyle::Steps, "Cosine Wave");

    sheet1.dataViewAs<compound_view_t>(2).setLineStyle(linesStyleOffset);

    sheet1.xAxis().labelText = "abscissa";
    sheet1.yAxis().labelText = "ordinate";

    // ---------------------------------------------------------------------- //
    // Sheet 2: polar line plots

    auto& sheet2 = report
                   .addPlotOrthogonalAxes("line plot (polar)")
                   .setPolar(true);
    sheet2
    .setAspectEqual()
    .setBorder(BorderLine::Polar);

    sheet2.axis(AxisType::Radial).rangeMax = 1.5;
    sheet2.axis(AxisType::Azimuthal).rangeMax = 180;

    sheet2.addDataViewCompound(&viewLineCompound);
    sheet2.addDataViewCompound<compound_t>("[0:pi] sin(t)", PlotStyle::Lines, "Sine Wave");

    sheet2.dataViewAs<compound_view_t>(1).setPlotStyleID(PlotStyle::Dots);
    // or:
    // dynamic_cast<DataViewDefaultCompound<compound_t>&>(sheet2.dataView(1)).setStyleID(PlotStyle::Dots);

    // ---------------------------------------------------------------------- //
    // Sheet 3: bar plots

    auto& sheet3 = report.addPlotOrthogonalAxes("bar plots");
    sheet3.setAspectSquare();

    sheet3.axis(AxisType::X).rangeMin = 0.;
    sheet3.axis(AxisType::X).rangeMax = pi;
    sheet3.axis(AxisType::Y).rangeMax = 1.5;

    sheet3.addDataViewCompound<compound_t>(compound_data, compoundSelectorY, PlotStyle::Boxes, "compound data series")
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Boxwidth, compoundSelectorErrX)
    .setLineStyle(linesStyleOffset + 1);

    sheet3
    .addDataViewSeparate(sepData_X, sepData_Y, PlotStyle::Impulses, "separated data series")
    .setLineStyle(linesStyleOffset + 5);

    // ---------------------------------------------------------------------- //
    // Sheet 4: filled curve

    auto& sheet4 = report.addPlotOrthogonalAxes("filled curves");

    sheet4
    .addDataViewCompound<compound_t>()
    .setData(compound_data)
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Y, compoundSelectorY)
    .setTitle("Sine approximation");

    sheet4.addDataViewCompound<compound_t>(compound_data, compoundSelectorY, PlotStyle::FilledCurves, "Error")
    .setSelector(ColumnType::X,      compoundSelectorX)
    .setSelector(ColumnType::DeltaY, compoundSelectorErrY);

    // ---------------------------------------------------------------------- //
    // ill-typed references cause a catch-able exception

    // *INDENT-OFF*
    try                             {auto& ill_typed_reference = sheet1.dataViewAs<DataViewDefaultCompound<double>>(2);}
    catch (const std::bad_cast& e)  {std::cout << "prevented misinterpretation of dataview object" << std::endl;}
    // *INDENT-ON*
}

// ========================================================================== //
