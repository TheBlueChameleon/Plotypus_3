#ifndef STYLESCOLLECTION_H
#define STYLESCOLLECTION_H

#include <fstream>
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
            StylesCollection();

            /* generic rule for add***Style, ID parameter
             * if ID = -1, use default:
             *  use current length of boxstyle list as ID.
             * ==> first call sets default, subsequent calls set user styles.
             */

            void reset();

            size_t                          getBoxStyleCount() const;
            const std::vector<BoxStyle>&    getBoxStyles() const;
            BoxStyle&                       getBoxStyle (const size_t i);
            void                            setBoxStyles(const std::vector<BoxStyle>& newBoxstyles);
            size_t                          addBoxStyle (const BoxStyle& newBoxstyle);
            size_t                          addBoxStyle (const std::string& fillcolor, bool border = true, const std::string& bordercolor = "");

            size_t                          getLineStyleCount() const;
            const std::vector<LineStyle>&   getLineStyles() const;
            LineStyle&                      getLineStyle (const size_t i);
            void                            setLineStyles(const std::vector<LineStyle>& newLineStyles);
            size_t                          addLineStyle (const LineStyle& newLineStyle);
            size_t                          addLineStyle (const std::string& color, double width = 1.0, std::string dashtype = "", PointForm pointForm = PointForm::Point);

            size_t                          getPointStyleCount() const;
            const std::vector<PointStyle>&  getPointStyles() const;
            PointStyle&                     getPointStyle (const size_t i);
            void                            setPointStyles(const std::vector<PointStyle>& newPointStyles);
            size_t                          addPointStyle (const PointStyle& newPointStyle);
            size_t                          addPointStyle (PointForm form = PointForm::Point, double size = 1.0, std::string color = "");

            // writers
            void writeBoxStyles     (std::ostream& hFile) const;
            void writeLineStyles    (std::ostream& hFile) const;
            void writePointStyleCode(std::ostream& hFile, const size_t i) const;
    };
}

#endif // STYLESCOLLECTION_H
