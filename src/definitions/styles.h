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

    class PointStyle
    {
        private:
            PointForm                   form = PointForm::Point;
            std::optional<std::string>  customSymbol;
            std::optional<std::string>  color;
            std::optional<double>       size;

            std::optional<std::string>  options;

        public:
            PointStyle() = default;

            PointStyle(
                const PointForm                     form,
                const std::string&                  customSymbol,
                const std::string&                  color,
                const double                        size,
                const std::optional<std::string>&   options = std::optional<std::string>()
            );

            PointStyle(
                const PointForm                     form,
                const std::optional<std::string>&   color = std::optional<std::string>(),
                const std::optional<double>&        size  = std::optional<double>()
            );

            PointStyle(
                const std::string&                  customSymbol,
                const std::optional<std::string>&   color = std::optional<std::string>(),
                const std::optional<double>&        size  = std::optional<double>()
            );

            PointForm                   getForm() const;
            PointStyle&                 setForm(PointForm newForm);

            std::optional<std::string>  getCustomSymbol() const;
            PointStyle&                 setCustomSymbol(const std::string& newCustomSymbol);
            PointStyle&                 clearCustomSymbol();

            std::optional<std::string>  getColor() const;
            PointStyle&                 setColor(const std::string& newColor);
            PointStyle&                 clearColor();

            std::optional<double>       getSize() const;
            PointStyle&                 setSize(const double newSize);
            PointStyle&                 clearSize();

            std::optional<std::string>  getOptions() const;
            PointStyle&                 setOptions(const std::string& newOptions);
            PointStyle&                 clearOptions();

            bool operator== (const PointStyle&) const = default;
    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Line Style (used with plots)
     *
     * cf. gnuplot 5.4 documentation, p. 203
     * Note: there, line*types* are used, which differ from line styles in permanence
     * of the definition
     *
     * @todo review reference handling of optionals
     */
    class LineStyle
    {
        private:
            std::optional<std::string> color;
            std::optional<double>      width;
            std::optional<std::string> dashtype;
            std::optional<PointStyle>  pointStyle;
            std::optional<std::string> options;

        public:
            LineStyle() = default;
            LineStyle(
                const std::optional<std::string>& color         = std::optional<std::string>(),
                const std::optional<double>&      width         = std::optional<double>(),
                const std::optional<std::string>& dashtype      = std::optional<std::string>(),
                const std::optional<PointStyle>&  pointStyle    = std::optional<PointStyle>(),
                const std::optional<std::string>& options       = std::optional<std::string>()
            );

            std::optional<std::string>  getColor() const;
            LineStyle&                  setColor(const std::string& newColor);
            LineStyle&                  clearColor();

            std::optional<double>       getWidth() const;
            LineStyle&                  setWidth(const double newWidth);
            LineStyle&                  clearWidth();

            std::optional<std::string>  getDashtype() const;
            LineStyle&                  setDashtype(const std::string& newDashtype);
            LineStyle&                  clearDashtype();

            std::optional<PointStyle>   getPointStyle() const;
            LineStyle&                  setPointStyle(const PointStyle newPointStyle);
            LineStyle&                  clearPointStyle();

            std::optional<std::string>  getOptions() const;
            LineStyle&                  setOptions(const std::string& newOptions);
            LineStyle&                  clearOptions();

            bool operator== (const LineStyle&) const = default;
    };

    // ========================================================================== //
    /**
     * @todo set style arrow support - p. 199 -- expands LineStyle?
     */
    class ArrowStyle {};

    // ====================================================================== //
    /**
     * @brief Sheet element: BoxStyle (used with Text overlays)
     *
     * Cf. page 201 gnuplot 5.4 documentation (section set style textbox)
     *
     * @todo refactor to monadic style
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
