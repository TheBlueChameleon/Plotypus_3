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
        Sheet,
        PlotDefault,
        PlotRadialAxes,
        Multiplot
    };

    // ====================================================================== //
    // Overlay

    /**
     * @brief used internally to select proper destructor
     */
    enum class OverlayType
    {
        Label,
        Object,
        Arrow
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
