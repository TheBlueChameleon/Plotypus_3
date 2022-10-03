#ifndef TERMINALINFOPROVIDER_H
#define TERMINALINFOPROVIDER_H

#include <variant>
#include <optional>
#include <string>

namespace Plotypus
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
     *
     * @todo maybe use GridPos, SheetPos types for dimension_..._t
     */

    /**
     *  @todo re-introduce this brief: changes the default values for terminal engine and output filename extension associated with the new FileType
     *
     * | FileType     | Terminal Engine | Extension |
     * |--------------|-----------------|-----------|
     * | `Pdf`        | pdfcairo        | pdf       |
     * | `Png`        | pngcairo        | png       |
     * | `PostScript` | epscairo        | eps       |
     * | `Gif`        | gif animate     | gif       |
     *
     * @todo remove aliases dimensions_pixels_t, dimensions_length_t
     */

    class TerminalInfoProvider
    {
        public:
            using dimensions_pixels_t           = GridDimension_t;
            using dimensions_length_t           = SheetPosition_t;
            using dimensions_length_with_unit_t = std::pair<dimensions_length_t, std::string>;
            using dimensions_t                  = std::variant<dimensions_pixels_t, dimensions_length_with_unit_t>;

            enum DimensionsTypeIndex {Pixels, Length};

        private:
            FileType                            fileType            = FileType::Pdf;
            std::string                         terminal            = "pdfcairo";
            bool                                outputToFile        = true;

            std::string                         outputDirectory     = "";
            std::string                         filenameBase        = "report";

            std::string                         extTxt              = "txt";
            std::string                         extDat              = "dat";
            std::string                         extGnu              = "gnuplot";
            std::string                         extOut              = "pdf";

            std::optional<dimensions_t>         dimensions;
            std::optional<dimensions_pixels_t>  position;

            std::optional<std::string>          backgroundColor;
            LineEnds                            lineEnds            = LineEnds::Default;
            std::optional<bool>                 transparent;

            std::optional<bool>                 animate;
            std::optional<size_t>               delay;
            std::optional<size_t>               loopCount;

            std::optional<std::string>          windowTitle;
            std::optional<size_t>               windowNumber;

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

            TerminalInfoProvider&               reset();
            TerminalInfoProvider&               clearOptionals();

            FileType                            getFileType() const;
            //! @todo consider moving lookup to util
            TerminalInfoProvider&               setFileType(FileType newFileType);

            const std::string&                  getTerminal() const;
            TerminalInfoProvider&               setTerminal(const std::string& newTerminal);

            bool                                getOutputToFile() const;
            TerminalInfoProvider&               setOutputToFile(bool newOutputToFile);

            const std::string&                  getOutputDirectory() const;
            TerminalInfoProvider&               setOutputDirectory(const std::string& newOutputDirectory);

            const std::string&                  getFilenameBase() const;
            TerminalInfoProvider&               setFilenameBase(const std::string& newFilenameBase);

            const std::string&                  getExtTxt() const;
            TerminalInfoProvider&               setExtTxt(const std::string& newExtTxt);

            const std::string&                  getExtDat() const;
            TerminalInfoProvider&               setExtDat(const std::string& newExtDat);

            const std::string&                  getExtOut() const;
            TerminalInfoProvider&               setExtOut(const std::string& newExtOut);

            const std::string&                  getExtGnu() const;
            TerminalInfoProvider&               setExtGnu(const std::string& newExtGnu);

            dimensions_t                        getDimensions() const;
            TerminalInfoProvider&               setDimensions(const dimensions_t& newDimensions);
            TerminalInfoProvider&               setDimensions(const dimensions_pixels_t& newDimensions);
            TerminalInfoProvider&               setDimensions(const dimensions_length_t& newDimensions);
            TerminalInfoProvider&               setDimensions(const dimensions_length_t& newDimensions, const LengthUnit lengthUnit);
            TerminalInfoProvider&               setDimensions(const dimensions_length_with_unit_t& newDimensions);
            TerminalInfoProvider&               setDimensions(const size_t width, const size_t height);
            TerminalInfoProvider&               setDimensions(const double width, const double height);
            TerminalInfoProvider&               setDimensions(const double width, const double height, const LengthUnit lengthUnit);
            TerminalInfoProvider&               setDimensions(const PaperFormats paperformat);
            TerminalInfoProvider&               clearDimensions();

            dimensions_pixels_t                 getPosition() const;
            TerminalInfoProvider&               setPosition(const dimensions_pixels_t& newPosition);
            TerminalInfoProvider&               clearPosition();

            std::string                         getBackgroundColor() const;
            TerminalInfoProvider&               setBackgroundColor(const std::string& newBackgroundColor);
            TerminalInfoProvider&               clearBackgroundColor();

            LineEnds                            getLineEnds() const;
            TerminalInfoProvider&               setLineEnds(const LineEnds newLineEnds);

            bool                                getTransparent() const;
            TerminalInfoProvider&               setTransparent(bool newTransparent);
            TerminalInfoProvider&               clearTransparent();

            bool                                getAnimate() const;
            TerminalInfoProvider&               setAnimate(bool newAnimate);
            TerminalInfoProvider&               clearAnimate();

            size_t                              getDelay() const;
            TerminalInfoProvider&               setDelay(const size_t newDelay);
            TerminalInfoProvider&               clearDelay();

            size_t                              getLoopCount() const;
            TerminalInfoProvider&               setLoopCount(const size_t newLoopCount);
            TerminalInfoProvider&               clearLoopCount();

            std::string                         getWindowTitle() const;
            TerminalInfoProvider&               setWindowTitle(const std::string& newWindowTitle);
            TerminalInfoProvider&               clearWindowTitle();

            size_t                              getWindowNumber() const;
            TerminalInfoProvider&               setWindowNumber(const size_t newWindowNumber);
            TerminalInfoProvider&               clearWindowNumber();

            std::string                         getOptions() const;
            TerminalInfoProvider&               setOptions(const std::string& newOptions);
            TerminalInfoProvider&               clearOptions();

            // util

            std::string getOutputFilename(const GeneratedFileType filetype, const std::string& infix = "") const;

            // writer

            void writeTerminalInfo(std::ostream& hFile) const;
    };
}

#endif // TERMINALINFOPROVIDER_H
