#ifndef STYLESCOLLECTION_H
#define STYLESCOLLECTION_H

#include <vector>

#include "../definitions/styles.h"

namespace Plotypus
{
    class StylesCollection
    {
        private :
            std::vector<BoxStyle>   boxStyles;
            std::vector<LineStyle>  lineStyles;
            std::vector<PointStyle> pointStyles = {{PointForm::Point, 1.0, ""}};

        public:
            StylesCollection();

            /* generic rule for add***Style, ID parameter
             * if ID = -1, use default:
             *  use current length of boxstyle list as ID.
             * ==> first call sets default, subsequent calls set user styles.
             */

            const std::vector<BoxStyle>&    getBoxStyles() const;
            BoxStyle&                       getBoxStyle(int i);
            void                            setBoxStyles(const std::vector<BoxStyle>& newBoxstyles);
            void                            addBoxStyle (const BoxStyle& newBoxstyle);
            void                            addBoxStyle (const std::string& fillcolor, bool border = true, const std::string& bordercolor = "", int ID = -1);

            const std::vector<LineStyle>&   getLineStyles() const;
            LineStyle&                      getLineStyle(int i);
            void                            setLineStyles(const std::vector<LineStyle>& newLineStyles);
            void                            addLineStyle (const LineStyle& newLineStyle);
            void                            addLineStyle (const std::string& color, double width = 1.0, std::string dashtype = "", PointForm pointForm = PointForm::Point, int ID = -1);

            const std::vector<PointStyle>&  getPointStyles() const;
            PointStyle&                     getPointStyle(int i);
            void                            setPointStyles(const std::vector<PointStyle>& newPointStyles);
            int                             addPointStyle (const PointStyle& newPointStyle);
            int                             addPointStyle (PointForm form = PointForm::Point, double size = 1.0, std::string color = "");

            // writers
    };
}

#endif // STYLESCOLLECTION_H
