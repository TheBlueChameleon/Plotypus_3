#ifndef STYLESCOLLECTION_H
#define STYLESCOLLECTION_H

#include <optional>
#include <vector>

#include "../definitions/styles.h"

namespace Plotypus
{
    class StylesCollection
    {
            /**
             * @todo add default style adders
             */

        private :
            std::vector<BoxStyle>   boxStyles;
            std::vector<LineStyle>  lineStyles;
            std::vector<PointStyle> pointStyles;

        public:
            StylesCollection() = default;

            StylesCollection&               reset();

            size_t                          getBoxStyleCount() const;
            const std::vector<BoxStyle>&    getBoxStyles() const;
            BoxStyle&                       boxStyle    (const size_t i);
            const BoxStyle&                 getBoxStyle (const size_t i) const;
            StylesCollection&               setBoxStyles(const std::vector<BoxStyle>& newBoxstyles);
            BoxStyle&                       addBoxStyle (const BoxStyle& newBoxstyle);
            BoxStyle&                       addBoxStyle (const std::string& fillcolor, bool border = true, const std::string& bordercolor = "");

            size_t                          getLineStyleCount() const;
            const std::vector<LineStyle>&   getLineStyles() const;
            LineStyle&                      lineStyle (const size_t i);
            const LineStyle&                getLineStyle (const size_t i) const;
            StylesCollection&               setLineStyles(const std::vector<LineStyle>& newLineStyles);
            LineStyle&                      addLineStyle (const LineStyle& newLineStyle);
            LineStyle&                      addLineStyle (const std::string& color, double width = 1.0, std::string dashtype = "", PointForm pointForm = PointForm::Point);

            size_t                          getPointStyleCount() const;
            const std::vector<PointStyle>&  getPointStyles() const;
            PointStyle&                     pointStyle (const size_t i);
            const PointStyle&               getPointStyle (const size_t i) const;
            StylesCollection&               setPointStyles(const std::vector<PointStyle>& newPointStyles);
            PointStyle&                     addPointStyle (const PointStyle& newPointStyle);
            PointStyle&                     addPointStyle (
                PointForm                           form  = PointForm::Point,
                const std::optional<std::string>&   color = std::optional<std::string>(),
                const std::optional<double>&        size  = std::optional<double>()
            );
            PointStyle&                     addPointStyle (
                const std::string&                  customSymbol,
                const std::optional<std::string>&   color = std::optional<std::string>(),
                const std::optional<double>&        size  = std::optional<double>()
            );

            // writers
            void writeStyles        (std::ostream& hFile) const;
            void writeBoxStyles     (std::ostream& hFile) const;
            void writeLineStyles    (std::ostream& hFile) const;
            void writePointStyleCode(std::ostream& hFile, const size_t i) const;
    };
}

#endif // STYLESCOLLECTION_H
