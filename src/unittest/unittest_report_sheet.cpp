//#include <functional>
#include <iostream>
//#include <numbers>
//#include <string>
//#include <vector>

#include "unittest.h"
#include "../plotypus.h"

// ========================================================================== //
// procs

bool unittest_report_basicSheetManagement()
{
    std::cout << "TESTING REPORT CLASS BASIC SHEET MANAGEMENT" << std::endl;

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

bool unittest_report_emptyScriptOutput()
{
    std::cout << "TESTING REPORT CLASS EMPTY SCRIPT OUTPUT" << std::endl;

    UNITTEST_VARS;

    Plotypus::Report r;
    std::stringstream s;
    std::string expectedScript;

    // ...................................................................... //

    UNITTEST_ASSERT(s.str() == "", "initialize empty string buffer");
    UNITTEST_CRITICAL_BARRIER;

    // ...................................................................... //

    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term pdfcairo\n"
        "set output 'report.pdf'\n"
        "\n";

    UNITTEST_DOESNT_THROW(
        r.writeScript(s),
        std::exception,
        "allow write of empty PDF script"
    );
    UNITTEST_ASSERT(s.str() == expectedScript, "write empty script");

    // ...................................................................... //

    s.str("");
    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term pngcairo\n"
        "set output 'report.png'\n"
        "\n";

    r.setFileType(Plotypus::FileType::Png);
    r.writeScript(s);
    UNITTEST_ASSERT(s.str() == expectedScript, "write empty script with defaults from other filetype");

    // ...................................................................... //

    s.str("");
    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term svg\n"
        "set output '././foo/bar/unittest.svg'\n"
        "\n";

    r.setTerminal("svg");
    r.setExtOut("svg");
    r.setFilenameBase("unittest");
    r.setOutputDirectory("././foo/bar/");
    r.writeScript(s);
    UNITTEST_ASSERT(s.str() == expectedScript, "write empty script with manually chosen strings");

    // ...................................................................... //

    s.str("");
    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term pdfcairo\n"
        "set output 'report.pdf'\n"
        "\n";
    r.reset();
    r.writeScript(s);
    UNITTEST_ASSERT(s.str() == expectedScript, "write empty script after reset");

    // ...................................................................... //

    UNITTEST_FINALIZE;
}

// -------------------------------------------------------------------------- //

bool unittest_report_sheets_scriptOutput()
{
    std::cout << "TESTING REPORT CLASS BASIC SHEET SCRIPT OUTPUT" << std::endl;

    UNITTEST_VARS;

    Plotypus::Report report;
    std::stringstream script;
    std::string expectedScript;

    // ...................................................................... //

    script.str("");
    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term pdfcairo\n"
        "set output 'report.pdf'\n"
        "\n"
        "# ============================================================================ #\n"
        "# page 1\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# prepare empty page\n"
        "\n"
        "set key off\n"
        "unset border\n"
        "unset xtics\n"
        "unset xlabel\n"
        "unset ytics\n"
        "unset ylabel\n"
        "unset ztics\n"
        "unset zlabel\n"
        "set xrange[0:1]\n"
        "set yrange[1:0]\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# generated setup script\n"
        "\n"
        "set font \"arial,7\"\n"
        "set title \"\"\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# dummy plot for empty page\n"
        "\n"
        "plot [][] 1/0 t\"\"\n"
        "unset label\n"
        "\n";

    auto& sheet1 = report.addSheet();

    report.writeScript(script);
    UNITTEST_ASSERT(script.str() == expectedScript, "write script with one empty sheet");

    // ...................................................................... //

    script.str("");
    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term pdfcairo\n"
        "set output 'report.pdf'\n"
        "\n"
        "# ============================================================================ #\n"
        "# page 1\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# prepare empty page\n"
        "\n"
        "set key off\n"
        "unset border\n"
        "unset xtics\n"
        "unset xlabel\n"
        "unset ytics\n"
        "unset ylabel\n"
        "unset ztics\n"
        "unset zlabel\n"
        "set xrange[0:1]\n"
        "set yrange[1:0]\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# generated setup script\n"
        "\n"
        "set font \"arial,7\"\n"
        "set title \"\"\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# dummy plot for empty page\n"
        "\n"
        "plot [][] 1/0 t\"\"\n"
        "unset label\n"
        "\n"
        "# ============================================================================ #\n"
        "# page 2\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# generated setup script\n"
        "\n"
        "set font \"arial,7\"\n"
        "set title \"\"\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# dummy plot for empty page\n"
        "\n"
        "plot [][] 1/0 t\"\"\n"
        "unset label\n"
        "\n";

    auto& sheet2 = report.addSheet();

    report.writeScript(script);
    UNITTEST_ASSERT(script.str() == expectedScript, "write script with two empty sheets without generating too much overhead");

    // ...................................................................... //

    script.str("");
    expectedScript =
        "# ============================================================================ #\n"
        "# output setup\n"
        "\n"
        "set term pdfcairo\n"
        "set output 'report.pdf'\n"
        "\n"
        "# ============================================================================ #\n"
        "# page 1\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# prepare empty page\n"
        "\n"
        "set key off\n"
        "unset border\n"
        "unset xtics\n"
        "unset xlabel\n"
        "unset ytics\n"
        "unset ylabel\n"
        "unset ztics\n"
        "unset zlabel\n"
        "set xrange[0:1]\n"
        "set yrange[1:0]\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# generated setup script\n"
        "\n"
        "set font \"courier,7\"\n"
        "set title \"foo bar\"\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# dummy plot for empty page\n"
        "\n"
        "plot [][] 1/0 t\"\"\n"
        "unset label\n"
        "\n"
        "# ============================================================================ #\n"
        "# page 2\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# generated setup script\n"
        "\n"
        "set font \"arial,7\"\n"
        "set title \"\"\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# custom setup script I\n"
        "\n"
        "# custom script begin\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# custom setup script II\n"
        "\n"
        "# custom script end\n"
        "\n"
        "# ---------------------------------------------------------------------------- #\n"
        "# dummy plot for empty page\n"
        "\n"
        "plot [][] 1/0 t\"\"\n"
        "unset label\n"
        "\n";

    sheet1.setTitle("foo bar");
    sheet1.setDefaultFont("courier,7");
    sheet2.setCustomScriptBegin("# custom script begin");
    sheet2.setCustomScriptEnd  ("# custom script end");

    report.writeScript(script);
    UNITTEST_ASSERT(script.str() == expectedScript, "write script with two empty sheets without generating unset overhead");

    // ...................................................................... //

    UNITTEST_FINALIZE;
}

bool unittest_sheets_labels()
{
    std::cout << "TESTING REPORT CLASS LABEL SCRIPT OUTPUT" << std::endl;

    UNITTEST_VARS;

    Plotypus::Report report;
    std::stringstream script;
    std::string expectedScript;

    // ...................................................................... //

//    auto& stylesCollection = report.getStylesCollection();
//    stylesCollection.addBoxStyle("yellow", true, "blue");

//    Plotypus::BoxStyle extendedBoxStyle = {false, "", true, "red", 2.5};
//    stylesCollection.addBoxStyle(extendedBoxStyle);

    auto& sheet = report.addSheet();

    Plotypus::Label expectedLabel;
    expectedLabel.text = "foo bar";
    expectedLabel.coordinates = {0.5, 0.5};
    expectedLabel.ID = 0;
    expectedLabel.boxed = true;
    expectedLabel.boxStyleID = 0;

    auto& label1 = sheet.addLabel("foo bar", 0.5, 0.5, true);

    UNITTEST_ASSERT(label1 == expectedLabel, "generate a box style");

    // ...................................................................... //

    UNITTEST_FINALIZE;
}
