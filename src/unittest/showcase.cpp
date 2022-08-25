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
        datapoint.errY = std::abs(datapoint.y - std::sin(x)) * 1.1;

        x += xIncrement;
    }

    return result;
}

std::pair<std::vector<double>, std::vector<double>> generateSeparateData2D()
{
    std::vector<double> dataX = {0, 1./3.*pi, 1./2.*pi, 2./3.*pi, pi};
    std::vector<double> dataY = {0,        1,      0.5,        1,  0};

    return std::make_pair(dataX, dataY);
}

// ========================================================================== //
// showcase utility

Plotypus::Report showcase_report = Plotypus::Report(Plotypus::FileType::Pdf);
bool             showcase_RunAutoActions = true;

void showcase_init()
{
    if (showcase_RunAutoActions)
    {
        showcase_report.setOutputDirectory("TestOutput");
    }
}

void showcase_exit()
{
    if (showcase_RunAutoActions)
    {
        showcase_report.writeTxt();
        showcase_report.writeDat();
        showcase_report.writeScript();
    }
}

// ========================================================================== //
// exposed procs

void showcase_all()
{
    showcase_init();
    showcase_RunAutoActions = false;

    showcase_overlays();

    showcase_RunAutoActions = true;
    showcase_exit();
}

void showcase_overlays()
{
    showcase_init();
    using namespace Plotypus;

    auto& stylesCollection = showcase_report.stylesCollection();

    int boxStyleOffset = stylesCollection.getBoxStyleCount();

    stylesCollection.addBoxStyle("cyan", true, "blue");
    stylesCollection.addBoxStyle("", true, "blue");

    auto& sheet1 = showcase_report.addSheet("text overlay features");

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

    showcase_exit();
}

void showcase_2D_plots()
{
    showcase_init();
    using namespace Plotypus;

    auto& stylesCollection = showcase_report.stylesCollection();
    int linesStyleOffset = stylesCollection.getLineStyleCount();
    int pointStyleOffset = stylesCollection.getPointStyleCount();

    stylesCollection.addLineStyle("blue", 2.5, "..-", PointForm::Circle);
    stylesCollection.addPointStyle(PointForm::Diamond, 2.0, "gold");

    using compound_selector_t = DataSelector_t<compound_t>;
    using compound_view_t = DataViewDefaultCompound<compound_t>;

    // *INDENT-OFF*
    std::vector<compound_t> compound_data = generateCompoundData2D();
    compound_selector_t compoundSelectorX    = [] (const compound_t& data) {return data.x;};
    compound_selector_t compoundSelectorY    = [] (const compound_t& data) {return data.y;};
    compound_selector_t compoundSelectorErrX = [] (const compound_t& data) {return data.errX;};
    compound_selector_t compoundSelectorErrY = [] (const compound_t& data) {return data.errY;};

    auto [sepData_X, sepData_Y] = generateSeparateData2D();
    // *INDENT-ON*

    auto& sheet1 = showcase_report.addPlotOrthogonalAxes("line plot (cartesian)");

    auto& dataViewCompound = sheet1.addDataViewCompound<compound_t>(compound_data, compoundSelectorY, PlotStyle::YErrorLines);
    dataViewCompound.setSelector(ColumnType::X, compoundSelectorX);
    dataViewCompound.setSelector(ColumnType::DeltaY, compoundSelectorErrY);
    dataViewCompound.setTitle("Sine Approximation");
    dataViewCompound.setBinaryDataOutput(false);

//    auto& dataViewSeparate = sheet1.addDataViewSeparate(sepData_X, sepData_Y);
//    dataViewSeparate.setPointStyle(pointStyleOffset);

    sheet1.addDataViewCompound<compound_t>("[0:pi] sin(x)", PlotStyle::Lines,       "Sine Wave");
    sheet1.addDataViewCompound<compound_t>("[0:pi] cos(x)", PlotStyle::LinesPoints, "Cosine Wave");

    auto& funcView = sheet1.dataViewAs<compound_view_t>(2);
    funcView.setLineStyle(linesStyleOffset);

    sheet1.xAxis().labelText = "abscissa";
    sheet1.yAxis().labelText = "ordinate";

    auto& sheet2 = showcase_report.addPlotOrthogonalAxes("line plot (polar)");
    sheet2.setPolar(true);
    sheet2.setAspectEqual();

    sheet2.addDataViewCompound(&dataViewCompound);
    sheet2.addDataViewCompound<compound_t>("[0:pi] sin(t)", PlotStyle::Lines,       "Sine Wave");

    sheet2.dataViewAs<compound_view_t>(1).setStyleID(PlotStyle::Dots);
    // or:
    // dynamic_cast<DataViewDefaultCompound<compound_t>&>(sheet2.dataView(1)).setStyleID(PlotStyle::Dots);
    sheet2.setBorder(BorderLine::Polar);
    sheet2.axis(AxisType::Radial).rangeMax = 1.5;


    // *INDENT-OFF*
    try                             {auto& ill_typed_reference = sheet1.dataViewAs<DataViewDefaultCompound<double>>(2);}
    catch (const std::bad_cast& e)  {std::cout << "prevented misinterpretation of dataview object" << std::endl;}
    // *INDENT-ON*


    showcase_exit();
}

// ========================================================================== //
