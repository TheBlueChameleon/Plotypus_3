#include <complex>
#include <iostream>

#include "showcase.h"
#include "../plotypus.h"

using namespace std::complex_literals;
using namespace std::string_literals;

// ========================================================================== //
// data types and constants

constexpr auto pi = std::numbers::pi;

struct compound_t
{
    double x, y, errX, errY;
};

using complex_t = std::complex<double>;

struct compound_complex_t
{
    complex_t coordinate;
    complex_t value;
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
    constexpr auto N = 50;
    constexpr auto xIncrement = pi / N;
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

std::vector<compound_complex_t> generateVectorField()
{
    // creates a vortex field around origin, domain is [-1, +1) x [-1, +1)

    constexpr auto Nx = 25;
    constexpr auto Ny = 25;

    constexpr auto dx = 2. / Nx;
    constexpr auto dy = 2. / Nx;

    std::vector<compound_complex_t> result(Nx * Ny);

    double x = -1., y = -1.;
    for     (size_t iy = 0u; iy < Nx; ++iy)
    {
        x = -1.;
        for (size_t ix = 0u; ix < Nx; ++ix)
        {
            x += dx;
            const auto coordinate = complex_t(x, y);
            const auto value      = complex_t(0, 1) * coordinate * .1;

            auto& thisArrow = result[iy * Nx + ix];
            thisArrow.coordinate = coordinate;
            thisArrow.value      = value;
        }
        y += dy;
    }

    return result;
}

std::array<std::vector<double>, 3> generateScalarField()
{
    // non-uniform sampling of the domain {which is [-1, 1) x [-1, 1)}
    // z = sin( 1/r ) with r = sqrt(x² + y²)

    std::vector<double> points, dataX, dataY, dataZ;

    for (double q = -1.; q < 1.;)
    {
        q += 0.05 * std::sqrt( std::abs(q) );
        points.push_back(q);
    }

    for     (auto y : points)
    {
        for (auto x : points)
        {
            double r = std::sqrt(x*x + y*y);
            double z = std::sin(2. / r);

            dataX.push_back(x);
            dataY.push_back(y);
            dataZ.push_back(z);
        }
    }

    return {dataX, dataY, dataZ};
}

// ========================================================================== //
// internal showcase procs

void showcase_run_overlays(Plotypus::Report& report);
void showcase_run_plots2d (Plotypus::Report& report,
                           std::pair<std::vector<double>, std::vector<double>>& separate_data,
                           std::vector<compound_t>& compound_data);
void showcase_run_plots2d_maps(Plotypus::Report& report,
                               std::vector<compound_complex_t>& compound_complex,
                               std::array<std::vector<double>, 3>& separate_data);
void showcase_run_plots_multiplot(Plotypus::Report& report);
void showcase_run_plots3d (Plotypus::Report& report, std::array<std::vector<double>, 3>& separate_data);

// ========================================================================== //
// exposed interface

void showcase_run(Showcases selection)
{
    // ---------------------------------------------------------------------- //
    // prepare report, i.e. the primary object

    Plotypus::Report report = Plotypus::Report(Plotypus::FileType::Pdf);
    report.setOutputDirectory("../TestOutput");

    // ---------------------------------------------------------------------- //
    // prepare some data (so they persist in memory until we write the report)

    std::pair<std::vector<double>, std::vector<double>> separate_data;
    std::vector<compound_t>                             compound_data;
    std::vector<compound_complex_t>                     compound_complex;
    std::array<std::vector<double>, 3>                  separate_filed;

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
    if (selection & Showcases::Plots_2D_maps)
    {
        compound_complex = generateVectorField();
        separate_filed   = generateScalarField();
        showcase_run_plots2d_maps(report, compound_complex, separate_filed);
    }
    if (selection & Showcases::Plots_Multiplot)
    {
        showcase_run_plots_multiplot(report);
    }
    if (selection & Showcases::Plots_3D)
    {
        // this screws up the 2d showcase because the generated views are invalid. I have to rewrite the showcase framework, anyway.
        separate_filed   = generateScalarField();
        showcase_run_plots3d (report, separate_filed);
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

    sheet1.addLabel("normal text", .10, .20).setTextcolor("blue");
    sheet1.addLabel("abcdefghijklmnopqrstuvwxyz01234567890  ", .10, .26, true);
    sheet1.addLabel("ABCDEFGHIJKLMNOPQRSTUVWXYZ=!\"§$%&/()= ", .10, .32, true);

    sheet1.addLabel("greek font", .10, .45).setTextcolor("blue");
    sheet1.addLabel("{/symbol abcdefghijklmnopqrstuvwxyz01234567890} ", .10, .51, true);
    sheet1.addLabel("{/symbol ABCDEFGHIJKLMNOPQRSTUVWXYZ=!\"§$%&/()=}", .10, .57, true);

    sheet1.addLabel("dingbats font", .10, .70).setTextcolor("blue");
    sheet1.addLabel("{/zapfdingbats abcdefghijklmnopqrstuvwxyz01234567890}", .10, .76, true);
    sheet1.addLabel("{/zapfdingbats ABCDEFGHIJKLMNOPQRSTUVWXYZ=!\"§$%&/()=}", .10, .82, true);

    sheet1.addLabel("some special symbols", .70, .20).setTextcolor("blue");
    sheet1.addLabel(""s + SYMBOL_FORALL + SYMBOL_ALPHA + SYMBOL_DOT + "5" + SYMBOL_HBAR, .70, .26, true);

    sheet1.addLabel("implicitly escaping symbols", .70, .45).setTextcolor("blue");
    sheet1.addLabel(""s
                    + SYMBOL_TILDE + "a"
                    + SYMBOL_FORWARD_SLASH + "a"
                    + SYMBOL_BACKWARD_SLASH + "a"
                    + SYMBOL_AMPERSAND + "a"
                    + SYMBOL_AT + "ax"
                    + SYMBOL_CURLY_BRACE_OPEN + "a" + SYMBOL_CURLY_BRACE_CLOSE,
                    .70, .51, true);
}

// -------------------------------------------------------------------------- //

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
    using compound_view_t     = DataviewDefaultCompound<compound_t>;

    // *INDENT-OFF*
    compound_selector_t compoundSelectorX    = [] (const compound_t& data) {return data.x;};
    compound_selector_t compoundSelectorY    = [] (const compound_t& data) {return data.y;};
    compound_selector_t compoundSelectorErrX = [] (const compound_t& data) {return data.errX;};
    compound_selector_t compoundSelectorErrY = [] (const compound_t& data) {return data.errY;};
    // *INDENT-ON*


    // ---------------------------------------------------------------------- //
    // Sheet 1: cartesian line plots

    auto& sheet1 = report.addPlotDefault("line plot (cartesian)");

    sheet1
    .setCustomScriptBegin("# put here setup code that should be executed BEFORE the code generated by Plotypus")
    .setCustomScriptInter("# put here setup code that should be executed AFTER the code generated by Plotypus")
    .setCustomScriptEnd  ("# put here setup code that should be executed BEFORE the tidy up code generated by Plotypus but AFTER the plots");

    sheet1
    .addDataviewCompound<compound_t>(PlotStyle::YErrorLines, "Sine Approximation")
    .setData(compound_data)
    .setSelector(ColumnType::X,      compoundSelectorX)
    .setSelector(ColumnType::Y,      compoundSelectorY)
    .setSelector(ColumnType::DeltaY, compoundSelectorErrY);

    sheet1
    .addDataviewSeparate(sepData_X, sepData_Y, PlotStyle::LinesPoints)
    .setPointStyle(pointStyleOffset);
//    .clearTitle();
//    .setTitle("TODO - empty title");

    sheet1.addDataviewCompound<compound_t>("[0:pi] sin(x)", PlotStyle::Lines, "Sine Wave");
    sheet1.addDataviewCompound<compound_t>("[0:pi] cos(x)", PlotStyle::Steps, "Cosine Wave");

    sheet1.dataviewAs<compound_view_t>(2).setLineStyle(linesStyleOffset);

    sheet1.axis(AxisType::X).setLabelText("abscissa");
    sheet1.axis(AxisType::Y).setLabelText("ordinate");

    sheet1.key()
    .setPosition(HorizontalAlignment::Left, VerticalAlignment::Center)
    .setReverseSymbol(true)
    .setJustification(HorizontalAlignment::Left);

    // ---------------------------------------------------------------------- //
    // Sheet 2: polar line plots

    auto& sheet2 = report
                   .addPlotDefault("line plot (polar)")
                   .setPolar(true);
    sheet2
    .setAspectEqual()
    .setBorder(BorderLine::Polar);

    sheet2.axis(AxisType::Radial).setRangeMax(1.5);
    sheet2.axis(AxisType::Azimuthal).setRangeMax(180);

    sheet2
    .addDataviewCompound<compound_t>(PlotStyle::YErrorLines, "Sine Approximation")
    .setData(compound_data)
    .setSelector(ColumnType::X,      compoundSelectorX)
    .setSelector(ColumnType::Y,      compoundSelectorY)
    .setSelector(ColumnType::DeltaY, compoundSelectorErrY);

    sheet2.addDataviewCompound<compound_t>("[0:pi] sin(t)", PlotStyle::Lines, "Sine Wave");

    sheet2.dataviewAs<compound_view_t>(1).setPlotStyleID(PlotStyle::Dots);
    // or:
    // dynamic_cast<DataViewDefaultCompound<compound_t>&>(sheet2.dataView(1)).setStyleID(PlotStyle::Dots);

    sheet2.key()
    .setPosition(Margin::Right)
    .setBoxed(true)
    .setTitle("Foo bar");

    // ---------------------------------------------------------------------- //
    // Sheet 3: bar plots

    auto& sheet3 = report.addPlotDefault("bar plots");
    sheet3.setAspectSquare();

    sheet3.axis(AxisType::X)
    .setRangeMin(0)
    .setRangeMax(pi);
    sheet3.axis(AxisType::Y).setRangeMax(1.5);

    sheet3.addDataviewCompound<compound_t>(compound_data, PlotStyle::Boxes, "compound data series")
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Y, compoundSelectorY)
    .setSelector(ColumnType::Boxwidth, compoundSelectorErrX)
    .setLineStyle(linesStyleOffset + 1);

    sheet3
    .addDataviewSeparate(sepData_X, sepData_Y, PlotStyle::Impulses, "separated data series")
    .setLineStyle(linesStyleOffset + 5);

    // ---------------------------------------------------------------------- //
    // Sheet 4: filled curve

    auto& sheet4 = report.addPlotDefault("filled curves");

    sheet4.addDataviewCompound<compound_t>(compound_data, PlotStyle::FilledCurves, "Error")
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Y, compoundSelectorY)
    .setSelector(ColumnType::DeltaY, compoundSelectorErrY)
    .setOptions("lc rgb \"#AACCFF\"");

    sheet4
    .addDataviewCompound<compound_t>()
    .setData(compound_data)
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Y, compoundSelectorY)
    .setTitle("Sine approximation");

    // ---------------------------------------------------------------------- //
    // ill-typed references cause a catch-able exception

    // *INDENT-OFF*
    try                             {auto& ill_typed_reference = sheet1.dataviewAs<DataviewDefaultCompound<double>>(2);}
    catch (const std::bad_cast& e)  {std::cout << "prevented misinterpretation of dataview object" << std::endl;}
    // *INDENT-ON*
}

// -------------------------------------------------------------------------- //

void showcase_run_plots2d_maps(Plotypus::Report& report,
                               std::vector<compound_complex_t>& compound_complex,
                               std::array<std::vector<double>, 3>& separate_data)
{
    using namespace Plotypus;

    // ---------------------------------------------------------------------- //
    // set up some styles

    auto& stylesCollection = report.stylesCollection();

    // ---------------------------------------------------------------------- //
    // separate data as before

    auto& [sepData_X, sepData_Y, sepData_Z] = separate_data;

    // ---------------------------------------------------------------------- //
    // for compound data: prepare selectors

    using compound_selector_t = DataSelector_t<compound_complex_t>;
    using compound_view_t     = DataviewDefaultCompound<compound_complex_t>;

    // *INDENT-OFF*
    compound_selector_t compoundSelectorX      = [] (const compound_complex_t& data) {return data.coordinate.real();};
    compound_selector_t compoundSelectorY      = [] (const compound_complex_t& data) {return data.coordinate.imag();};
    compound_selector_t compoundSelectorDeltaX = [] (const compound_complex_t& data) {return data.value     .real();};
    compound_selector_t compoundSelectorDeltaY = [] (const compound_complex_t& data) {return data.value     .imag();};
    // *INDENT-ON*

    // ---------------------------------------------------------------------- //
    // Sheet 1: vector field

    auto& sheet1 = report.addPlotDefault("vector field");

    sheet1.axis(AxisType::X)
    .setRangeMin (-1.5)
    .setRangeMax (+1.5)
    .setLabelText(SYMBOL_REAL_PART);
    sheet1.axis(AxisType::Y)
    .setRangeMin (-1.5)
    .setRangeMax (+1.5)
    .setLabelText(SYMBOL_IMAGINARY_PART);
    sheet1.setAspectSquare();

    sheet1.addDataviewCompound<compound_complex_t>(PlotStyle::Vectors, "vortex")
    .setData(compound_complex)
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Y, compoundSelectorY)
    .setSelector(ColumnType::DeltaX, compoundSelectorDeltaX)
    .setSelector(ColumnType::DeltaY, compoundSelectorDeltaY);

    // ---------------------------------------------------------------------- //
    // Sheet 2: scalar field

    auto& sheet2 = report.addPlotDefault("scalar field");

    sheet2.axis(AxisType::X)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet2.axis(AxisType::Y)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet2.setAspectEqual();

    sheet2.addDataviewSeparate(PlotStyle::Image, "sin(2/r)")
    .setData(ColumnType::X, sepData_X)
    .setData(ColumnType::Y, sepData_Y)
    .setData(ColumnType::Color, sepData_Z)
    .setBinaryDataOutput(false);

    sheet2.addLabel("Rendering of", -1.7, 0.6);
    sheet2.addLabel("sin(2/r)",     -1.7, 0.5);

    sheet2.paletteDescriptor().setMapping(NamedPalette::Gnu_Rainbow);

    sheet2.key().setPosition(Margin::Bottom, HorizontalAlignment::Right);
    try
    {
        sheet2.key().setPosition(Margin::Bottom, VerticalAlignment::Bottom);
    }
    catch (const PlotypusError& e)
    {
        std::cout << "No double specification of key position" << std::endl;
    }
}

// -------------------------------------------------------------------------- //

void showcase_run_plots_multiplot(Plotypus::Report& report)
{
    auto& sheet1 = report.addMultiPlot("multiplot").setGridDimensions({1, 3});
    auto& subplot_1_1 = sheet1.addPlotDefault("subplot 1");
    auto& subplot_1_2 = sheet1.addSheet("subplot 2");
    auto& subplot_1_3 = sheet1.addPlotDefault("subplot 3");

    auto& f_sin = subplot_1_1.addDataviewSeparate("[0:2*pi]sin(x)");
    auto& f_cos = subplot_1_3.addDataviewSeparate("[0:3*pi]cos(x)");
    f_sin.setTitle("foo bar");
    f_cos.setTitle("BOO FAR");

    subplot_1_1.addLabel("foo bar", 0.1, 0.1);
    subplot_1_2.addLabel("FOO BAR", 0.1, 0.1);

    auto& sheet2 = report.addSheet("Simple Sheet").addLabel("after a multiplot, the normal features are available as usual.", 0.05, 0.1);

    auto& sheet3 = report.addMultiPlot("second one");
    auto& subplot_3_1 = sheet3.addPlotDefault("subplot 1");
    auto& subplot_3_2 = sheet3.addPlotDefault("subplot 2");

    subplot_3_1.setSize  ({0.5, 1.0});
    subplot_3_2.setSize  ({0.5, 1.0});
    subplot_3_2.setOrigin({0.5, 0.0});

    subplot_3_1.addDataviewSeparate("[0:pi]tan(x)");
    subplot_3_2.addDataviewSeparate("[0:pi]exp(x)");

    sheet3.addLabel("label on multiplot level behaves like subplot 1 element", 0.1, 40);

    auto& sheet4 = report.addMultiPlot("blanks test").setGridDimensions({2, 2}).setBlanks({2, 3});
    auto& subplot_4_1 = sheet4.addPlotDefault("subplot 1");
    auto& subplot_4_2 = sheet4.addPlotDefault("subplot 2");

    subplot_4_1.addDataviewSeparate("[0:2*pi]sin(x)");
    subplot_4_2.addDataviewSeparate("[0:2*pi]cos(x)");
}

void showcase_run_plots3d (Plotypus::Report& report, std::array<std::vector<double>, 3>& separate_data)
{
    using namespace Plotypus;

    // ---------------------------------------------------------------------- //
    // set up some styles

    auto& stylesCollection = report.stylesCollection();

    // ---------------------------------------------------------------------- //
    // separate data as before

    auto& [sepData_X, sepData_Y, sepData_Z] = separate_data;


    // ---------------------------------------------------------------------- //
    // Sheet 1: scalar field

    auto& sheet1 = report.addPlotDefault("scalar field");

    sheet1.axis(AxisType::X)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet1.axis(AxisType::Y)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet1.setAspectEqual();

    sheet1.addDataviewSeparate(PlotStyle::Dots3D, "sin(2/r)")
    .setData(ColumnType::X, sepData_X)
    .setData(ColumnType::Y, sepData_Y)
    .setData(ColumnType::Z, sepData_Z)
    .setBinaryDataOutput(false);
}

// ========================================================================== //
