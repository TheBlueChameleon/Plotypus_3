#ifndef STYLES_H
#define STYLES_H

#include <optional>
#include <string>
#include <utility>

#include "constants.h"

namespace Plotypus
{
    //! @addtogroup Plotypus_Definitions
    //! @{

    struct PointStyle
    {
        PointForm                   form = PointForm::Point;
        std::string                 customSymbol;
        std::optional<double>       size;
        std::optional<std::string>  color;

        std::optional<std::string> options;

        bool operator== (const PointStyle&) const = default;

    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Line Style (used with plots)
     *
     * cf. gnuplot 5.4 documentation, p. 203
     * Note: there, line*types* are used, which differ from line styles in permanence
     * of the definition
     */
    struct LineStyle
    {
        std::optional<std::string> color;
        std::optional<double>      width;
        std::optional<std::string> dashtype;
        std::optional<PointStyle>  pointStyle;
        std::optional<std::string> options;

        bool operator== (const LineStyle&) const = default;
    };

    // ========================================================================== //
    /**
     * @todo set style arrow support - p. 199 -- expands LineStyle?
     */
    struct ArrowStyle {};

    // ====================================================================== //
    /**
     * @brief Sheet element: BoxStyle (used with Text overlays)
     *
     * Cf. page 201 gnuplot 5.4 documentation (section set style textbox)
     */
    struct BoxStyle
    {
        bool                        opaque      = true;
        bool                        border      = true;
        std::optional<double>       linewidth;
        std::optional<std::string>  fillcolor;
        std::optional<std::string>  bordercolor;
        std::optional<std::string>  options;

        bool operator== (const BoxStyle&) const = default;
    };

    //! }
}

#endif // STYLES_H
