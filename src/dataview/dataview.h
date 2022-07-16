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
            std::string options = "";

            bool binaryDataOutput = true;

        public:
            DataView(const std::string& label, const PlotStyle2D& style, const std::string& dataColumnFormat = "#");
            DataView(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            virtual void reset();

            const std::string&  getLabel() const;
            void                setLabel(const std::string& newLabel);

            const std::string&  getStyle() const;
            void                setStyle(const std::string& newStyle);
            void                setStyle(const PlotStyle2D& newStyle);

            const std::string&  getDataColumnFormat() const;
            void                setDataColumnFormat(const std::string& newDataColumnFormat);
            void                setDataColumnFormatPositive();                            // shortcut: set format such that only positive values are plotted.

            bool                getBinaryDataOutput() const;
            void                setBinaryDataOutput(bool newBinaryDataOutput);

            const std::string&  getOptions() const;
            void                setOptions(const std::string& newOptions);

            // writers
            virtual void writeScriptData(std::ostream& hFile) const = 0;
    };
}

#endif // DATAVIEW_H
