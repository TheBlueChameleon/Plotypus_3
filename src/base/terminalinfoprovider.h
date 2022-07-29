#ifndef TERMINALINFOPROVIDER_H
#define TERMINALINFOPROVIDER_H

#include <variant>
#include <optional>
#include <string>

namespace Plotypus
{
    class TerminalInfoProvider
    {
            /**
             * @todo provide support for
             *      Lua/Tikz alias LaTeX
             *      Svg
             *      Canvas alias JavaScript
             */

        public:
            using dimensions_pixels_t           = std::pair<int, int>;
            using dimensions_length_t           = std::pair<double, double>;
            using dimensions_length_with_unit_t = std::pair<dimensions_length_t, std::string>;
            using dimensions_t                  = std::variant<dimensions_pixels_t, dimensions_length_with_unit_t>;

            enum DimensionsTypeIndex {Pixels, Length};

        private:
            FileType                            fileType;
            std::string                         terminal;
            std::string                         extOut;

            std::optional<dimensions_t>         dimensions;
            std::optional<dimensions_pixels_t>  position;

            std::optional<std::string>          backgroundColor;
            std::optional<LineEnds>             lineEnds;
            std::optional<bool>                 transparent;

            std::optional<int>                  delay;
            std::optional<int>                  loopCount;

            std::optional<std::string>          windowTitle;
            std::optional<int>                  windowNumber;

            std::optional<std::string>          options;

            bool                                outputToFile;
            bool                                animate;

            static std::string getDimensionTypeName(const std::optional<dimensions_t>& dimensions);
            void throwIfDimensionsNotOfType(const dimensions_t& dimensions, size_t i);

        public:
            TerminalInfoProvider();
            TerminalInfoProvider(FileType fileType);
            TerminalInfoProvider(const std::string& terminal);

            void reset();

            FileType            getFileType() const;
            void                setFileType(FileType newFileType);
            const std::string&  getTerminal() const;
            void                setTerminal(const std::string& newTerminal);
            const std::string&  getExtOut() const;
            void                setExtOut(const std::string& newExtOut);

            std::optional<dimensions_t> getDimensions() const;
            void                        setDimensions(const dimensions_t& newDimensions);
            void                        setDimensions(const dimensions_pixels_t& newDimensions);
            void                        setDimensions(const dimensions_length_t& newDimensions);
            void                        setDimensions(const dimensions_length_t& newDimensions, const LengthUnits lengthUnit);
            void                        setDimensions(const dimensions_length_with_unit_t& newDimensions);
            void                        setDimensions(const int width, const int height);
            void                        setDimensions(const double width, const double height);
            void                        setDimensions(const double width, const double height, const LengthUnits lengthUnit);
            void                        clearDimensions();
    };
}

#endif // TERMINALINFOPROVIDER_H
