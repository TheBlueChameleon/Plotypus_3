#ifndef TYPES_H
#define TYPES_H

namespace Plotypus
{
    enum class PlotType
    {
        Sheet,                      // an empty sheet, optionally with title. Ready to be populated with overlays

        Plot2D,                     // functionality of sheet, together with frame formatting and capacity to accept 2D data sequences
        Plot3D,                     // same, but accepts 3D data sequences
        Plot3D_flattened,           // same, but accepts flattened 3D data sequences

        Multiplot,                  // a sheet with multiple plots on it
        Report                      // a collection of sheets, plots or multiplots.
    };
}

#endif // TYPES_H
