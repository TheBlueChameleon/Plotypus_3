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
             *
             * @todo update the supported types table in docs
             *
             * @todo add quick setup for A4, portrait/landscape, ...
             */

            /**
             *  @brief changes the default values for terminal engine and output filename extension associated with the new FileType
             *
             * | FileType     | Terminal Engine | Extension |
             * |--------------|-----------------|-----------|
             * | `Pdf`        | pdfcairo        | pdf       |
             * | `Png`        | pngcairo        | png       |
             * | `PostScript` | epscairo        | eps       |
             * | `Gif`        | gif animate     | gif       |
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

            void throwIfDimensionsNotOfType(const dimensions_t& dimensions, size_t i) const;
            void throwIfUnsupportedFeature(const std::string& feature, const std::vector<FileType>& supportedTerminals) const;

            void writeDimensions    (std::ostream& hFile) const;
            void writePosition      (std::ostream& hFile) const;
            void writeBackground    (std::ostream& hFile) const;
            void writeLineEnds      (std::ostream& hFile) const;
            void writeTransparent   (std::ostream& hFile) const;
            void writeAnimateX      (std::ostream& hFile) const;
            void writeWindowTitle   (std::ostream& hFile) const;
            void writeWindowNumber  (std::ostream& hFile) const;
            void writeOptions       (std::ostream& hFile) const;

        public:
            TerminalInfoProvider();
            TerminalInfoProvider(FileType fileType);
            TerminalInfoProvider(const std::string& terminal);

            TerminalInfoProvider& reset();

            FileType                    getFileType() const;
            TerminalInfoProvider&       setFileType(FileType newFileType);
            const std::string&          getTerminal() const;
            TerminalInfoProvider&       setTerminal(const std::string& newTerminal);
            const std::string&          getExtOut() const;
            TerminalInfoProvider&       setExtOut(const std::string& newExtOut);
            bool                        getOutputToFile() const;
            TerminalInfoProvider&       setOutputToFile(bool newOutputToFile);

            std::optional<dimensions_t> getDimensions() const;
            TerminalInfoProvider&       setDimensions(const dimensions_t& newDimensions);
            TerminalInfoProvider&       setDimensions(const dimensions_pixels_t& newDimensions);
            TerminalInfoProvider&       setDimensions(const dimensions_length_t& newDimensions);
            TerminalInfoProvider&       setDimensions(const dimensions_length_t& newDimensions, const LengthUnit lengthUnit);
            TerminalInfoProvider&       setDimensions(const dimensions_length_with_unit_t& newDimensions);
            TerminalInfoProvider&       setDimensions(const int width, const int height);
            TerminalInfoProvider&       setDimensions(const double width, const double height);
            TerminalInfoProvider&       setDimensions(const double width, const double height, const LengthUnit lengthUnit);
            TerminalInfoProvider&       clearDimensions();

            std::optional<dimensions_pixels_t>  getPosition() const;
            TerminalInfoProvider&               setPosition(const dimensions_pixels_t& newPosition);
            TerminalInfoProvider&               clearPosition();

            std::optional<std::string>          getBackgroundColor() const;
            TerminalInfoProvider&               setBackgroundColor(const std::string& newBackgroundColor);
            TerminalInfoProvider&               clearBackgroundColor();

            std::optional<LineEnds>             getLineEnds() const;
            TerminalInfoProvider&               setLineEnds(const LineEnds newLineEnds);
            TerminalInfoProvider&               clearLineEnds();

            std::optional<bool>                 getTransparent() const;
            TerminalInfoProvider&               setTransparent(bool newTransparent);
            TerminalInfoProvider&               clearTransparent();

            std::optional<bool>                 getAnimate() const;
            TerminalInfoProvider&               setAnimate(bool newAnimate);
            TerminalInfoProvider&               clearAnimate();

            std::optional<int>                  getDelay() const;
            TerminalInfoProvider&               setDelay(int newDelay);
            TerminalInfoProvider&               clearDelay();

            std::optional<int>                  getLoopCount() const;
            TerminalInfoProvider&               setLoopCount(int newLoopCount);
            TerminalInfoProvider&               clearLoopCount();

            std::optional<std::string>          getWindowTitle() const;
            TerminalInfoProvider&               setWindowTitle(const std::string& newWindowTitle);
            TerminalInfoProvider&               clearWindowTitle();

            std::optional<int>                  getWindowNumber() const;
            TerminalInfoProvider&               setWindowNumber(int newWindowNumber);
            TerminalInfoProvider&               clearWindowNumber();

            std::optional<std::string>          getOptions() const;
            TerminalInfoProvider&               setOptions(const std::string& newOptions);
            TerminalInfoProvider&               clearOptions();

            // writer

            void writeTerminalInfo(std::ostream& hFile) const;
    };
}

#endif // TERMINALINFOPROVIDER_H
