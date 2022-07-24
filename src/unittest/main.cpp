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
    std::vector<compound_t> result(N);

    // Taylor approximation of sine
    for (double x = 0.; auto& datapoint : result)
    {
        datapoint.x    = x;
        datapoint.y    = x - (x*x*x / 6.) + (x*x*x*x*x / 120.);
        datapoint.errY = (1./120.) * (.1) * std::pow(x, 6.);

        x += pi / N;
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
    auto [dataX, dataY] = generateSeparateData();
    std::vector<compound_t> data = generateCompoundData();

    // *INDENT-OFF*
    Plotypus::DataSelector_t<compound_t> compoundSelectorX    = [] (const compound_t& data) {return data.x;};
    Plotypus::DataSelector_t<compound_t> compoundSelectorY    = [] (const compound_t& data) {return data.y;};
    Plotypus::DataSelector_t<compound_t> compoundSelectorErrX = [] (const compound_t& data) {return data.errX;};
    Plotypus::DataSelector_t<compound_t> compoundSelectorErrY = [] (const compound_t& data) {return data.errY;};
    // *INDENT-ON*

    Plotypus::Report r;

    r.setOutputDirectory("TestOutput");

    auto& sc = r.getStylesCollection();
    sc.addBoxStyle("cyan", true, "blue");
    sc.addLineStyle("blue", 2.5, "..-", Plotypus::PointForm::Circle);

    auto& s1 = r.addSheet("foo");
    auto& s2 = r.addSheet("bar");
    auto& s3 = r.addSheet();
    auto& s4 = r.addPlot2D("plot");
    auto& s5 = r.addSheet();

    s1.addLabel(" FOO ", .10, .10);
    s1.addLabel("(foo)", .10, .50);

    s2.addLabel(" BAR ", .10, .10, true);
    s2.addLabel("(bar)", .10, .50, true);

    s3.addLabel("empty", .10, .10, true, 1);
    s3.addLabel("empty", .10, .50, true, 1);

    s4.addDataViewCompound<compound_t>(data, compoundSelectorY, Plotypus::PlotStyle2D::YErrorLines);
    s4.addDataViewCompound<compound_t>("[0:pi] sin(x)", Plotypus::PlotStyle2D::Lines, "Sine Wave"s);
    s4.addDataViewCompound<compound_t>("[0:pi] cos(x)", Plotypus::PlotStyle2D::Lines, "Cosine Wave");

    dynamic_cast<Plotypus::DataView2DCompound<compound_t>&>(s4.dataView(1)).setStyleID(Plotypus::PlotStyle2D::Dots);

    auto& dataViewData1 = s4.dataViewAs<Plotypus::DataView2DCompound<compound_t>>(0);
    auto& dataViewFunc2 = s4.dataViewAs<Plotypus::DataView2DCompound<compound_t>>(2);
    // *INDENT-OFF*
    try                             {auto& errv = s4.dataViewAs<Plotypus::DataView2DCompound<double>>(2);}
    catch (const std::bad_cast& e)  {std::cout << "prevented misinterpretation of dataview object" << std::endl;}
    // *INDENT-ON*

    dataViewData1.setSelector(Plotypus::ColumnTypes::X, compoundSelectorX);
    dataViewData1.setSelector(Plotypus::ColumnTypes::DeltaY, compoundSelectorErrY);
    dataViewData1.setLabel("Sine Approximation");
    //dataViewData1.setBinaryDataOutput(false);
    dataViewFunc2.setLineStyle(0);


    r.writeTxt();
    r.writeDat();
    r.writeScript();
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
