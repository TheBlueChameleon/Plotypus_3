#ifndef TYPES_H
#define TYPES_H

#include <functional>

namespace Plotypus
{
//! @addtogroup Platypus_Definitions
//! @{

    // ====================================================================== //
    /**
     * @brief internally used specifyer of data format
     */
    enum class PlotType
    {
        //! @brief an empty sheet, optionally with title. Ready to be populated with overlays
        Sheet,

        //! @brief  functionality of sheet, together with frame formatting and capacity to accept 2D data sequences
        Plot2D,
        //! @brief  same, but accepts 3D data sequences
        Plot3D,

        //! @brief  a sheet with multiple plots on it
        Multiplot
    };

    // ====================================================================== //
    /**
     * @brief data selector: takes an object of type T and extracts the
     *  plottable quantity of type double
     */

    template <typename T>
    using DataSelector = std::function<double (const T)>;

    template <typename T>
    static inline double defaultDataSelector(const T x)
    {
        return x;
    }

//! @}
}

#endif // TYPES_H
