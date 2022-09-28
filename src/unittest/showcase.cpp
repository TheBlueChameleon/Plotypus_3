#include <complex>
#include <iostream>

#include "showcase.h"
#include "../plotypus.h"

using namespace std::complex_literals;
using namespace std::string_literals;

// ========================================================================== //
// behaviour constants

bool SHOWCASE_TXT_REPORT = true;

// ========================================================================== //

void showcase_minimal()
{
    /* This example shows the very minimal code needed to create plots from
     * data in memory.
     *
     * Creating more fancy output is showcased in the other routines of this
     * module.
     */

    // ---------------------------------------------------------------------- //
    // prepare data

    std::vector<double> data;

    double x = 0.;
    while (x < 2*pi)
    {
        data.push_back( std::sin(x) );
        x += .05;
    }

    // ---------------------------------------------------------------------- //
    // prepare report, i.e. the primary object

    Plotypus::Report report = Plotypus::Report(Plotypus::FileType::Pdf);
    report
    .setOutputDirectory("../TestOutput")
    .setFilenameBase("minimal");

    // ---------------------------------------------------------------------- //
    // define the report elements

    report
    .addPlotDefault("Minimal Plotypus Example")
    .addDataviewSeparate(data, Plotypus::PlotStyle::Lines, "sine wave");

    // ---------------------------------------------------------------------- //
    // use the report writer(s)

    report.writeReport();       // generates the dat files, the gnuplot script and executes it
    if (SHOWCASE_TXT_REPORT)
    {
        report.writeTxt();      // generates a CSV like, human readable file
    }
}


// ========================================================================== //
// internal showcase procs

/* For the detail showcase examples, the same Plotypus::Report object will
 * be used. A driver function showcase_run generates the object as well as
 * all data that might be used for plots, akin to a main function in your
 * simulation. It then calls various routines that configure the report to
 * include different plots. To that end, the called routines are passed
 * REFERENCES to the data. The actual data all "live" in showcase_run and
 * their lifetime is the same as the Plotypuss::Report object.
 *
 * Below you will find the functions being called by showcase_run with brief
 * descriptions of what features to find there.
 */

// shows how to put text and graphical non-plot elements on sheets.
void showcase_run_overlays(Plotypus::Report& report);

// shows some simple X/Y graphs with formatting
void showcase_run_separateSimple(Plotypus::Report& report,
                                 std::vector<double>& dataX,
                                 std::vector<double>& dataY);

void showcase_run_plots2d_prime(Plotypus::Report& report,
                                std::pair<std::vector<double>, std::vector<double>>& separate_data,
                                std::vector<compound_t>& compound_data);
void showcase_run_plots2d_maps(Plotypus::Report& report,
                               std::vector<compound_complex_t>& compound_complex,
                               std::array<std::vector<double>, 3>& separate_data);
void showcase_run_plots_multiplot(Plotypus::Report& report);
void showcase_run_plots3d (Plotypus::Report& report, std::array<std::vector<double>, 3>& separate_data);

// ========================================================================== //
// exposed interface

void showcase_run(size_t selection)
{
    // ---------------------------------------------------------------------- //
    // prepare report, i.e. the primary object

    Plotypus::Report report = Plotypus::Report(Plotypus::FileType::Pdf);
    report
    .setOutputDirectory("../TestOutput")
    .setFilenameBase("extended");

    // ---------------------------------------------------------------------- //
    // prepare some data (so they persist in memory until we write the report)

    std::pair<std::vector<double>, std::vector<double>> separate_data = generateSeparateData2D();
    std::vector<compound_t>                             compound_data = generateCompoundData2D();
    std::vector<compound_complex_t>                     compound_complex = generateVectorField();
    std::array<std::vector<double>, 3>                  separate_filed   = generateScalarField();

    // ---------------------------------------------------------------------- //
    // run desired showcase options

    showcase_run_separateSimple(report, separate_data.first, separate_data.second);

    // *INDENT-OFF*
    if (selection & Showcases::Overlays)        {showcase_run_overlays(report);}
    if (selection & Showcases::Plots_2D)        {showcase_run_plots2d_prime(report, separate_data, compound_data);}
    if (selection & Showcases::Plots_2D_maps)   {showcase_run_plots2d_maps(report, compound_complex, separate_filed);}
    if (selection & Showcases::Plots_Multiplot) {showcase_run_plots_multiplot(report);}
    if (selection & Showcases::Plots_3D)        {showcase_run_plots3d(report, separate_filed);}
    // *INDENT-ON*

    // ---------------------------------------------------------------------- //
    // write the report

    report.writeReport();
    if (SHOWCASE_TXT_REPORT)
    {
        report.writeTxt();      // generates a CSV like, human readable file
    }
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

void showcase_run_separateSimple(Plotypus::Report& report,
                                 std::vector<double>& dataX,
                                 std::vector<double>& dataY)
{
    /* locally using namespace Plotypus will save you a lot of typing while
     * still protecting you from most name collisions
     */

    using namespace Plotypus;

    // ---------------------------------------------------------------------- //
    // set up some styles

    /* styles -- the way lines, points, ... look like are managed centrally by
     * the Report in its stylesCollection. We later refer to these styles by
     * their index within the collection.
     */

    auto& stylesCollection = report.stylesCollection();

    /* since other showcase calls might have added other styles, we record the
     * number of registered styles before defining own styles and use this as
     * an offset.
     * In your code, you probably won't need to do that.
     */
    int linesStyleOffset = stylesCollection.getLineStyleCount();
    int pointStyleOffset = stylesCollection.getPointStyleCount();


    stylesCollection.addLineStyle("#FFF8E7");                                   // "cosmic latte"
    stylesCollection.addLineStyle("red");                                       // simply a red line
    stylesCollection.addLineStyle("blue", 2.5, "..-");                          // a blue line with 2.5pt thickness, dash-dotted

    stylesCollection.addLineStyle("steelblue")                                  // line styles may be changed after creation
    .setWidth(0.2);                                                             // this gives an alternative, more readable way of setting attributes

    stylesCollection.addPointStyle(PointForm::Diamond, "steelblue", 0.5);       // much the same holds for point styles, too.

    stylesCollection
    .addPointStyle("*", "dark-chartreuse", 0.5)
    .setOptions("pointinterval 5");                                             // not all options of gnuplot are natively supported. A options record/method usually allows to inject custom code

    // ---------------------------------------------------------------------- //
    // sheet 1: plots with default styles

    auto& sheet1 = report.addPlotDefault("default styles");

    sheet1.addDataviewSeparate(dataX, dataY, PlotStyle::Impulses, "impulses");

    sheet1
    .addDataviewSeparate()                                                  // apart from the constructor arguments, ...
    .setData(ColumnType::X, dataX)                                          // ... attributes can be set by chainable setter functions ...
    .setData(ColumnType::Y, dataY)                                          // ... which also throw exceptions in case of improper use.
    .setTitle("lines (by default)");                                        // When chaining, order matters since the returned type of the setters may only decrease in specificity

    sheet1.addDataviewSeparate( "sin(x)", PlotStyle::Lines,        "sin(x)");
    sheet1.addDataviewSeparate( "cos(x)", PlotStyle::Lines,        "cos(x)");
    sheet1.addDataviewSeparate("-sin(x)", PlotStyle::LinesPoints, "-sin(x)");
    sheet1.addDataviewSeparate("-cos(x)", PlotStyle::LinesPoints, "-cos(x)");

    // ---------------------------------------------------------------------- //
    // sheet 2: plots with our styles

    auto& sheet2 = report.addPlotDefault("custom styles");

    sheet2
    .addDataviewSeparate(dataX, dataY, PlotStyle::Impulses, "simData")
    .setLineStyle(linesStyleOffset);

    //! @todo duplicator functions here!
    sheet2
    .addDataviewSeparate()
    .setData(ColumnType::X, dataX)
    .setData(ColumnType::Y, dataY)
    .setLineStyle(linesStyleOffset + 1)
    .setTitle("simData");

    sheet2.addDataviewSeparate( "sin(x)", PlotStyle::Lines,       "sin(x)").setLineStyle  (linesStyleOffset + 2);
    sheet2.addDataviewSeparate( "cos(x)", PlotStyle::Lines,       "cos(x)").setLineStyle  (linesStyleOffset + 3);
    sheet2.addDataviewSeparate("-sin(x)", PlotStyle::LinesPoints, "-sin(x)").setPointStyle(pointStyleOffset    );
    sheet2.addDataviewSeparate("-cos(x)", PlotStyle::LinesPoints, "-cos(x)").setPointStyle(pointStyleOffset + 1);

}

// -------------------------------------------------------------------------- //

void showcase_run_plots2d_prime(Plotypus::Report& report,
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

    stylesCollection.addPointStyle(PointForm::Diamond, "gold", 0.5);

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
    // Sheet 5: HBoxes with normal functions overlayed

    auto& sheet5 = report.addPlotDefault("HBoxes");

    std::cout << std::string(80, '-') << std::endl;
    sheet5.addDataviewCompound<compound_t>(compound_data, PlotStyle::HBoxes, "Data")
    .setSelector(ColumnType::X, compoundSelectorX)
    .setSelector(ColumnType::Y, compoundSelectorY);
    //.setSelector(ColumnType::Boxwidth, compoundSelectorErrX);

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
    // Sheet 1: dots

    auto& sheet1 = report.addPlotDefault("3D dots");

    sheet1.axis(AxisType::X)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet1.axis(AxisType::Y)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet1.setAspectEqual();

    sheet1.addDataviewSeparate(PlotStyle::Points3D, "sin(2/r)")
    .setData(ColumnType::X, sepData_X)
    .setData(ColumnType::Y, sepData_Y)
    .setData(ColumnType::Z, sepData_Z);

    // ---------------------------------------------------------------------- //
    // Sheet 2: image

    auto& sheet2 = report.addPlotDefault("image projection");

    sheet2.axis(AxisType::X)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet2.axis(AxisType::Y)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet2.setAspectEqual();

    sheet2.addDataviewSeparate(PlotStyle::Image3D, "sin(2/r)")
    .setData(ColumnType::X, sepData_X)
    .setData(ColumnType::Y, sepData_Y)
    .setData(ColumnType::Z, sepData_Z)
    .setData(ColumnType::Color, sepData_Z)
    .setColumnFormat(ColumnType::Z, "(0)")
    .setBinaryDataOutput(false);

    // ---------------------------------------------------------------------- //
    // Sheet 2: image

    auto& sheet3 = report.addPlotDefault("lines projection");

    sheet3.axis(AxisType::X)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet3.axis(AxisType::Y)
    .setRangeMin(-1.0)
    .setRangeMax(+1.0);
    sheet3.setAspectEqual();

    sheet3.addDataviewSeparate(PlotStyle::Lines3D, "sin(2/r)")
    .setData(ColumnType::X, sepData_X)
    .setData(ColumnType::Y, sepData_Y)
    .setData(ColumnType::Z, sepData_Z);
}

