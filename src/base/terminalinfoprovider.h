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
            bool                                outputToFile;

            std::optional<dimensions_t>         dimensions;
            std::optional<dimensions_pixels_t>  position;

            std::optional<std::string>          backgroundColor;
            std::optional<LineEnds>             lineEnds;
            std::optional<bool>                 transparent;

            std::optional<bool>                 animate;
            std::optional<int>                  delay;
            std::optional<int>                  loopCount;

            std::optional<std::string>          windowTitle;
            std::optional<int>                  windowNumber;

            std::optional<std::string>          options;


            static std::string getDimensionTypeName(const std::optional<dimensions_t>& dimensions);

            void throwIfDimensionsNotOfType(const dimensions_t& dimensions, size_t i);
            void throwIfUnsupportedFeature(const std::string& feature, const std::vector<FileType>& supportedTerminals);

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
            bool                getOutputToFile() const;
            void                setOutputToFile(bool newOutputToFile);

            std::optional<dimensions_t> getDimensions() const;
            void                        setDimensions(const dimensions_t& newDimensions);
            void                        setDimensions(const dimensions_pixels_t& newDimensions);
            void                        setDimensions(const dimensions_length_t& newDimensions);
            void                        setDimensions(const dimensions_length_t& newDimensions, const LengthUnit lengthUnit);
            void                        setDimensions(const dimensions_length_with_unit_t& newDimensions);
            void                        setDimensions(const int width, const int height);
            void                        setDimensions(const double width, const double height);
            void                        setDimensions(const double width, const double height, const LengthUnit lengthUnit);
            void                        clearDimensions();

            std::optional<dimensions_pixels_t>  getPosition() const;
            void                                setPosition(const dimensions_pixels_t& newPosition);
            void                                clearPosition();

            std::optional<std::string>          getBackgroundColor() const;
            void                                setBackgroundColor(const std::string& newBackgroundColor);
            void                                clearBackgroundColor();

            std::optional<LineEnds>             getLineEnds() const;
            void                                setLineEnds(const LineEnds newLineEnds);
            void                                clearLineEnds();

            std::optional<bool>                 getTransparent() const;
            void                                setTransparent(bool newTransparent);
            void                                clearTransparent();

            std::optional<bool>                 getAnimate() const;
            void                                setAnimate(bool newAnimate);
            void                                clearAnimate();

            std::optional<int>                  getDelay() const;
            void                                setDelay(int newDelay);
            void                                clearDelay();

            std::optional<int>                  getLoopCount() const;
            void                                setLoopCount(int newLoopCount);
            void                                clearLoopCount();

            std::optional<std::string>          getWindowTitle() const;
            void                                setWindowTitle(const std::string& newWindowTitle);
            void                                clearWindowTitle();

            std::optional<int>                  getWindowNumber() const;
            void                                setWindowNumber(int newWindowNumber);
            void                                clearWindowNumber();

            std::optional<std::string>          getOptions() const;
            void                                setOptions(const std::string& newOptions);
            void                                clearOptions();
    };
}

#endif // TERMINALINFOPROVIDER_H
