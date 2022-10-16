#ifndef SHOWCASE_H
#define SHOWCASE_H

#include <complex>

#include "../plotypus.h"

// ========================================================================== //
// showcase selection

enum Showcases
{
    Overlays            = 1 << 0,
    Plot_SeparateSimple = 1 << 1,
    Plot_CompoundSimple = 1 << 2,
    FrameControls       = 1 << 3,
    Plot_Multiplot      = 1 << 4,
    Plots_2D_Variety    = 1 << 5,
    Plots_2D_Maps       = 1 << 6,
    Plots_3D            = 1 << 7,

    All                 = -1,
};

// ========================================================================== //
// behaviour constants

extern bool SHOWCASE_TXT_REPORT;

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

std::array<std::vector<double>, 5> generateSeparateData2D();
std::vector<compound_t>            generateCompoundData2D();
std::vector<compound_complex_t>    generateVectorField();
std::array<std::vector<double>, 3> generateScalarField();

// ========================================================================== //
// showcase interface

void showcase_minimal();
void showcase_run(size_t selection);

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
                                 std::vector<double>& dataX, std::vector<double>& dataY);

// shows some simple X/Y based on a std::vector<some_struct>
void showcase_run_compoundSimple(Plotypus::Report& report, std::vector<compound_t>& compound_data);

// shows how to change the size of report pages and plot areas
void showcase_run_frameControls(Plotypus::Report& report);

// shows how to arrange several plots on a single page
void showcase_run_plots_multiplot(Plotypus::Report& report);

// shows other standard plot types and how to use them
void showcase_run_plots2d_variety (Plotypus::Report& report,
                                   std::array<std::vector<double>, 5>& dataSep,
                                   std::vector<compound_t>& dataCmp);

// shows how to portray scalar and vector fields on a 2D domain
void showcase_run_plots2d_maps(Plotypus::Report& report,
                               std::vector<compound_complex_t>& compound_complex,
                               std::array<std::vector<double>, 3>& separate_data);

// show some 3d capabilities
void showcase_run_plots3d (Plotypus::Report& report, std::array<std::vector<double>, 3>& separate_data);


#endif // SHOWCASE_H
