#include <functional>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

#include "unittest.h"
#include "../plotypus.h"

using namespace std::string_literals;

// ========================================================================== //
// convenience macro

#define ADD_UNITTEST(func) {unittests.emplace_back(std::make_pair(#func, func));}

// ========================================================================== //
// procs

bool unittest_report()
{
    std::cout << "TESTING REPORT CLASS" << std::endl;

    UNITTEST_VARS;

    Plotypus::Report r;

    // ...................................................................... //

    UNITTEST_ASSERT(r.getReportSize() == 0,
                    "initialize empty list of sheets");

    UNITTEST_THROWS(r.sheet(0),
                    Plotypus::InvalidIndexError,
                    "prevent access to nonexistent sheets");

    r.addSheet();
    UNITTEST_ASSERT(r.getReportSize() == 1,
                    "add sheet");

    {
        auto& s = r.addSheet();
    }
    UNITTEST_ASSERT(r.getReportSize() == 2,
                    "add sheet in scope and persist thereafter");

    UNITTEST_DOESNT_THROW(r.sheet(0),
                          std::exception,
                          "access existing sheet (positive index)");
    UNITTEST_THROWS(r.sheet(2),
                    Plotypus::InvalidIndexError,
                    "prevent out of scope index access (positive index)"
                   );
    UNITTEST_THROWS(r.sheet(-1),
                    Plotypus::InvalidIndexError,
                    "prevent out of scope index access (negative index)"
                   );

    // ...................................................................... //

    UNITTEST_FINALIZE;
}

// -------------------------------------------------------------------------- //

void playground ()
{
    struct compound_t
    {
        double x, y, errX, errY;
    };

    const auto& pi = std::numbers::pi;
    std::vector<double> dataX = {0, 1./3.*pi, 2./3.*pi, pi};
    std::vector<double> dataY = {0,        1,        1,  0};

    std::vector<compound_t> data =
    {
        {       0, 0, 0, 0},
        {1./3.*pi, 1, 0, 0},
        {2./3.*pi, 1, 0, 0},
        {      pi, 0, 0, 0}
    };
    // *INDENT-OFF*
    Plotypus::DataSelector<compound_t> compoundSelectorX = [] (const compound_t& data) {return data.x;};
    Plotypus::DataSelector<compound_t> compoundSelectorY = [] (const compound_t& data) {return data.y;};
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

    s4.addDataViewCompound<compound_t>(data, compoundSelectorY);
    s4.addDataViewCompound<compound_t>("[0:pi] sin(x)"s, "Sine Wave"s);
    s4.addDataViewCompound<compound_t>("[0:pi] cos(x)", "Cosine Wave");

    dynamic_cast<Plotypus::DataView2DCompound<compound_t>&>(s4.dataView(1)).setStyleID(Plotypus::PlotStyle2D::Dots);

    auto& dv = s4.dataViewAs<Plotypus::DataView2DCompound<compound_t>>(2);
    try
    {
        auto& errv = s4.dataViewAs<Plotypus::DataView2DCompound<double>>(2);
    }
    catch (const std::bad_cast& e)
    {
        std::cout << "prevented misinterpretation of dataview object" << std::endl;
    }

    dv.setLineStyle(0);
    dv.setSelector(Plotypus::ColumnTypes::X, compoundSelectorX);


//    r.writeTxt();
//    r.writeDat();
//    r.writeScript();
}

// ========================================================================== //
// main

int main()
{
    std::cout << "UNIT TEST MAIN" << std::endl;

    std::vector<std::pair<std::string, std::function<bool()>>> unittests;
    std::vector<std::string> failedTests;

    // ...................................................................... //

    std::cout << "REGISTERING UNIT TESTS ... " << std::flush;

    ADD_UNITTEST(unittest_report);

    std::cout << "DONE" << std::endl << std::endl;

    // ...................................................................... //

    std::cout << "ABOUT TO RUN UNIT TESTS" << std::endl;
    for (auto & [name, func] : unittests)
    {
        std::cout << "### STARTING TEST '" << name << "' ..." << std::endl;
        if (! func())
        {
            failedTests.push_back(name);
            std::cout << "~~~ FAILED!" << std::endl;
        }
        else
        {
            std::cout << "~~~ PASSED!" << std::endl;
        }
    }
    std::cout << "ALL REGISTERED UNIT TESTS DONE" << std::endl << std::endl;

    // ...................................................................... //

    std::cout << "UNIT TESTS SUMMARY" << std::endl;
    std::cout << "Passed " << unittests.size() - failedTests.size() << "/" << unittests.size() << " tests"  << std::endl;
    if (!failedTests.empty())
    {
        std::cout << "Failed Tests:" << std::endl;
        for (auto& name : failedTests)
        {
            std::cout << "~~~ " << name << std::endl;
        }
    }

    // ...................................................................... //

    std::cout << std::endl;
    std::cout << "FREE RANGE CODE BEGINS HERE" << std::endl;
    playground();

    return 0;
}
