#ifndef INTERNALCONSTANTS_H
#define INTERNALCONSTANTS_H

namespace Plotypus
{
    // ====================================================================== //
    // Sheet

    /**
     * @brief used internally to select proper destructor
     */
    enum class SheetType
    {
        //! @brief an empty sheet, optionally with title. Ready to be populated with overlays
        Sheet,

        //! @brief functionality of sheet, together with capacity to render 2D/3D plots with orthogonal axes
        PlotOrthogonalAxis,

        //! @brief same, but renders pie charts and spiderplots
        PlotRadialAxes,

        //! @brief a sheet with multiple subsheets on it
        Multiplot
    };

    // ====================================================================== //
    // Plot

    /**
     * @brief used internally to select proper destructor
     */
    enum class DataViewType
    {
        DataViewDefaultCompound,
        DataViewDefaultSeparate
    };

    // ---------------------------------------------------------------------- //
    /**
     * @brief used internally to distinguish between mechanisms for plot command generation
     */
    enum class PlotStyleFamily
    {
        Undefined,
        Orthogonal2D,
        Orthogonal3D,
        Radial,
        Custom
    };
}
#endif // INTERNALCONSTANTS_H
