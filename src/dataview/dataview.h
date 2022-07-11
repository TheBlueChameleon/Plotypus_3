#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <string>

namespace Plotypus
{
    class DataView
    {
        protected:
            std::string label;
            std::string style;
            std::string dataColumnFormat = "#";

        public:
            DataView(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            virtual void reset();

            const std::string&  getLabel() const;
            void                setLabel(const std::string& newLabel);

            const std::string&  getStyle() const;
            void                setStyle(const std::string& newStyle);

            const std::string&  getDataColumnFormat() const;
            void                setDataColumnFormat(const std::string& newDataColumnFormat);
            void                setDataColumnFormatPositive();                            // shortcut: set format such that only positive values are plotted.
    };
}

#endif // DATAVIEW_H
