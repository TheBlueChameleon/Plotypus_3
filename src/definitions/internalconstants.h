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
        PlotRadial,
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
    enum class DataviewType
    {
        DataViewDefaultCompound,
        DataViewDefaultSeparate,
        DataViewMatrixCompound,
        DataViewMatrixSeparate
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

    // ---------------------------------------------------------------------- //
    /**
     * @brief used internally to distinguish between mechanisms for plot command generation
     */
    enum PlotStyleTraits
    {
        Orthogonal2D    = 1 << 0,
        Orthogonal3D    = 1 << 1,
        Radial          = 1 << 2,
        Horizontal      = 1 << 3,
        Matrix          = 1 << 4,
    };
}
#endif // INTERNALCONSTANTS_H
