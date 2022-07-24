#include <iostream>

#include "unittest.h"
#include "unittest_procs.h"
#include "../plotypus.h"

using namespace std::string_literals;

// ========================================================================== //
// playground

const auto& pi = std::numbers::pi;

struct compound_t
{
    double x, y, errX, errY;
};

std::vector<compound_t> generateCompoundData()
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

std::pair<std::vector<double>, std::vector<double>> generateSeparateData()
{
    std::vector<double> dataX = {0, 1./3.*pi, 1./2.*pi, 2./3.*pi, pi};
    std::vector<double> dataY = {0,        1,      0.5,        1,  0};

    return std::make_pair(dataX, dataY);
}

void playground ()
{
    Plotypus::Report report(Plotypus::FileType::Pdf);

    report.setOutputDirectory("TestOutput");

    auto& stylesCollection = report.getStylesCollection();
    stylesCollection.addBoxStyle("cyan", true, "blue");
    stylesCollection.addLineStyle("blue", 2.5, "..-", Plotypus::PointForm::Circle);

    auto& sheet1 = report.addSheet("foo");
    auto& sheet2 = report.addSheet("bar");
    auto& sheet3 = report.addSheet();
    auto& sheet4 = report.addPlot2D("plot");
    auto& sheet5 = report.addSheet();

    sheet1.addLabel(" FOO ", .10, .10);
    sheet1.addLabel("(foo)", .10, .50);

    sheet2.addLabel(" BAR ", .10, .10, true);
    sheet2.addLabel("(bar)", .10, .50, true);

    sheet3.addLabel("empty", .10, .10, true, 1);
    sheet3.addLabel("empty", .10, .50, true, 1);

    // *INDENT-OFF*
    std::vector<compound_t> data = generateCompoundData();
    Plotypus::DataSelector_t<compound_t> compoundSelectorX    = [] (const compound_t& data) {return data.x;};
    Plotypus::DataSelector_t<compound_t> compoundSelectorY    = [] (const compound_t& data) {return data.y;};
    Plotypus::DataSelector_t<compound_t> compoundSelectorErrX = [] (const compound_t& data) {return data.errX;};
    Plotypus::DataSelector_t<compound_t> compoundSelectorErrY = [] (const compound_t& data) {return data.errY;};
    // *INDENT-ON*

    auto& dataView1 = sheet4.addDataViewCompound<compound_t>(data, compoundSelectorY, Plotypus::PlotStyle2D::YErrorLines);
    dataView1.setSelector(Plotypus::ColumnTypes::X, compoundSelectorX);
    dataView1.setSelector(Plotypus::ColumnTypes::DeltaY, compoundSelectorErrY);
    dataView1.setLabel("Sine Approximation");
    //dataViewData1.setBinaryDataOutput(false);

    sheet4.addDataViewCompound<compound_t>("[0:pi] sin(x)", Plotypus::PlotStyle2D::Lines,       "Sine Wave"s);
    sheet4.addDataViewCompound<compound_t>("[0:pi] cos(x)", Plotypus::PlotStyle2D::LinesPoints, "Cosine Wave");
    auto& funcView2 = sheet4.dataViewAs<Plotypus::DataView2DCompound<compound_t>>(2);

    // *INDENT-OFF*
    try                             {auto& errv = sheet4.dataViewAs<Plotypus::DataView2DCompound<double>>(2);}
    catch (const std::bad_cast& e)  {std::cout << "prevented misinterpretation of dataview object" << std::endl;}
    // *INDENT-ON*

    funcView2.setLineStyle(0);
    dynamic_cast<Plotypus::DataView2DCompound<compound_t>&>(sheet4.dataView(1)).setStyleID(Plotypus::PlotStyle2D::Dots);


    auto [dataX, dataY] = generateSeparateData();

    report.writeTxt();
    report.writeDat();
    report.writeScript();
}

// ========================================================================== //
// main

int main()
{
    std::cout << "UNIT TEST MAIN" << std::endl;

    UNITTEST_MAIN_VARS;

    // ...................................................................... //

    std::cout << "REGISTERING UNIT TESTS ... " << std::flush;

    ADD_UNITTEST(unittest_report_basicSheetManagement);
    ADD_UNITTEST(unittest_report_emptyScriptOutput);
    ADD_UNITTEST(unittest_report_sheets_scriptOutput);
    ADD_UNITTEST(unittest_sheets_labels);

    std::cout << "DONE" << std::endl << std::endl;

    // ...................................................................... //

    std::cout << "ABOUT TO RUN UNIT TESTS" << std::endl;

    RUN_UNITTESTS;

    std::cout << "ALL REGISTERED UNIT TESTS DONE" << std::endl << std::endl;

    // ...................................................................... //

    std::cout << "UNIT TESTS SUMMARY" << std::endl;

    SUMMARIZE_UNITTESTS;

    // ...................................................................... //

    std::cout << std::endl;
    std::cout << "FREE RANGE CODE BEGINS HERE" << std::endl;
    playground();

    return 0;
}
