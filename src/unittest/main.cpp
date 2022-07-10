#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "unittest.h"
#include "../plotypus.h"

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

    UNITTEST_THROWS(r.getSheet(0),
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

    UNITTEST_DOESNT_THROW(r.getSheet(0),
                          std::exception,
                          "access existing sheet (positive index)");
    UNITTEST_DOESNT_THROW(r.getSheet(-1),
                          std::exception,
                          "access existing sheet (negative index)");
    UNITTEST_THROWS(r.getSheet(2),
                    Plotypus::InvalidIndexError,
                    "prevent out of scope index access (positive index)"
                   );
    UNITTEST_THROWS(r.getSheet(-3),
                    Plotypus::InvalidIndexError,
                    "prevent out of scope index access (negative index)"
                   );

    // ...................................................................... //

    UNITTEST_FINALIZE;
}

// -------------------------------------------------------------------------- //

void playground ()
{
    Plotypus::Report r;

    r.setOutputDirectory("TestOutput");

    auto& sc = r.getStylesCollection();
    sc.addBoxStyle("cyan", true, "blue");

    auto& s1 = r.addSheet("foo");
    auto& s2 = r.addSheet("bar");
    auto& s3 = r.addSheet();

    s1.addLabel(" FOO ", .10, .10);
    s1.addLabel("(foo)", .10, .50);

    s2.addLabel(" BAR ", .10, .10, true);
    s2.addLabel("(bar)", .10, .50, true);

    s3.addLabel("empty", .10, .10, true, 1);
    s3.addLabel("empty", .10, .50, true, 1);

    r.writeTxt();
    r.writePdf();
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
