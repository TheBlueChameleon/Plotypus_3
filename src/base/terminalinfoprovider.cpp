#include "../definitions/errors.h"

#include "terminalinfoprovider.h"

using namespace std::string_literals;

namespace Plotypus
{
    std::string TerminalInfoProvider::getDimensionTypeName(const std::optional<dimensions_t>& dimensions)
    {
        if (dimensions.has_value())
        {
            const auto& dimensionsVariant = dimensions.value();
            switch (dimensionsVariant.index())
            {
                case DimensionsTypeIndex::Pixels:
                    return "pixels";

                case DimensionsTypeIndex::Length:
                    const dimensions_length_with_unit_t&    dimensionsWithUnit = std::get<DimensionsTypeIndex::Length>(dimensionsVariant);
                    const std::string&                      dimensionsUnit = dimensionsWithUnit.second;
                    return "length with unit "s + dimensionsUnit;
            }
        }

        return "terminal default specification";
    }

    void TerminalInfoProvider::throwIfDimensionsNotOfType(const dimensions_t& dimensions, size_t i)
    {
        if (dimensions.index() != i)
        {
            throw InvalidArgumentError("    Invalid dimensions specification.\n"
                                       "      given   : "s + getDimensionTypeName(dimensions) + "\n"
                                       "      terminal: "s + getTerminalName(fileType));
        }
    }

    void TerminalInfoProvider::throwIfUnsupportedFeature(const std::string& feature, const std::vector<FileType>& supportedTerminals)
    {
        if (fileType == FileType::Custom)
        {
            return;
        }

        if (!contains(fileType, supportedTerminals))
        {
            throw InvalidArgumentError("    Feature not supported for this type of terminal.\n"
                                       "      feature : "s + feature + "\n"
                                       "      terminal: "s + getTerminalName(fileType));
        }
    }

    // ====================================================================== //

    TerminalInfoProvider::TerminalInfoProvider()
    {
        setFileType(FileType::Pdf);
    }

    TerminalInfoProvider::TerminalInfoProvider(FileType fileType)
    {
        setFileType(fileType);
    }

    TerminalInfoProvider::TerminalInfoProvider(const std::string& terminal)
    {
        setTerminal(terminal);
    }

    // ====================================================================== //

    void TerminalInfoProvider::reset()
    {
        fileType        = FileType::Custom;
        terminal        = "";
        extOut          = "";
        dimensions      .reset();
        position        .reset();
        backgroundColor .reset();
        lineEnds        .reset();
        transparent     .reset();
        delay           .reset();
        loopCount       .reset();
        options         .reset();
        outputToFile    = true;
        animate         = true;
    }

    // ---------------------------------------------------------------------- //

    FileType TerminalInfoProvider::getFileType() const
    {
        return fileType;
    }

    void TerminalInfoProvider::setFileType(FileType newFileType)
    {
        reset();

        switch(newFileType)
        {
            case FileType::Custom:
                break;

            case FileType::Ascii:
                terminal = "dumb";
                extOut   = "txt";
                break;

            case FileType::Gif:
                terminal = "gif";
                extOut   = "gif";
                break;

            case FileType::Jpeg:
                terminal = "jpeg";
                extOut   = "jpg";
                break;

            case FileType::LaTeX:
                terminal = "lua tikz";
                extOut   = "tex";
                break;

            case FileType::Pdf:
                terminal = "pdfcairo";
                extOut   = "pdf";
                break;

            case FileType::Png:
                terminal = "pngcairo";
                extOut   = "png";
                break;

            case FileType::PostScript:
                terminal = "epscairo";
                extOut   = "eps";
                break;

            case FileType::Screen:
                terminal = "qt";
                extOut   = "";
                outputToFile = false;
                break;
        }

        fileType = newFileType;
    }

    const std::string& TerminalInfoProvider::getTerminal() const
    {
        return terminal;
    }

    void TerminalInfoProvider::setTerminal(const std::string& newTerminal)
    {
        setFileType(FileType::Custom);
        terminal = newTerminal;
    }

    const std::string& TerminalInfoProvider::getExtOut() const
    {
        return extOut;
    }

    void TerminalInfoProvider::setExtOut(const std::string& newExtOut)
    {
        extOut = newExtOut;
    }

    bool TerminalInfoProvider::getOutputToFile() const
    {
        return outputToFile;
    }

    void TerminalInfoProvider::setOutputToFile(bool newOutputToFile)
    {
        outputToFile = newOutputToFile;
    }

    // ---------------------------------------------------------------------- //

    std::optional<TerminalInfoProvider::dimensions_t> TerminalInfoProvider::getDimensions() const
    {
        return dimensions;
    }

    void TerminalInfoProvider::setDimensions(const dimensions_t& newDimensions)
    {
        // *INDENT-OFF*
        switch(fileType)
        {
            case FileType::Custom:      break;
            case FileType::Ascii:       throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Pixels); break;
            case FileType::Gif:         throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Pixels); break;
            case FileType::Jpeg:        throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Pixels); break;
            case FileType::LaTeX:       throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Length); break;
            case FileType::Pdf:         throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Length); break;
            case FileType::Png:         break;
            case FileType::PostScript:  throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Length); break;
            case FileType::Screen:      throwIfDimensionsNotOfType(newDimensions, DimensionsTypeIndex::Pixels); break;
        }
        // *INDENT-ON*

        dimensions = newDimensions;
    }

    void TerminalInfoProvider::setDimensions(const dimensions_pixels_t& newDimensions)
    {
        setDimensions(dimensions_t(newDimensions));
    }

    void TerminalInfoProvider::setDimensions(const dimensions_length_t& newDimensions)
    {
        const std::string lengthUnitString = getLengthUnitName(LengthUnit::Inch);
        dimensions_length_with_unit_t fullySpecifiedDimensions = std::make_pair(newDimensions, lengthUnitString);
        setDimensions(dimensions_t(fullySpecifiedDimensions));
    }

    void TerminalInfoProvider::setDimensions(const dimensions_length_t& newDimensions, const LengthUnit lengthUnit)
    {
        const std::string lengthUnitString = getLengthUnitName(lengthUnit);
        dimensions_length_with_unit_t fullySpecifiedDimensions = std::make_pair(newDimensions, lengthUnitString);
        setDimensions(dimensions_t(fullySpecifiedDimensions));
    }

    void TerminalInfoProvider::setDimensions(const dimensions_length_with_unit_t& newDimensions)
    {
        setDimensions(dimensions_t(newDimensions));
    }

    void TerminalInfoProvider::setDimensions(const int width, const int height)
    {
        setDimensions(std::make_pair(width, height));
    }

    void TerminalInfoProvider::setDimensions(const double width, const double height)
    {
        setDimensions(std::make_pair(width, height));
    }

    void TerminalInfoProvider::setDimensions(const double width, const double height, const LengthUnit lengthUnit)
    {
        setDimensions(std::make_pair(width, height), lengthUnit);
    }

    void TerminalInfoProvider::clearDimensions()
    {
        dimensions.reset();
    }

    // ---------------------------------------------------------------------- //

    std::optional<TerminalInfoProvider::dimensions_pixels_t> TerminalInfoProvider::getPosition() const
    {
        return position;
    }

    void TerminalInfoProvider::setPosition(const dimensions_pixels_t& newPosition)
    {
        throwIfUnsupportedFeature("position", {FileType::Screen});
        position = newPosition;
    }

    void TerminalInfoProvider::clearPosition()
    {
        position.reset();
    }

    std::optional<std::string> TerminalInfoProvider::getBackgroundColor() const
    {
        return backgroundColor;
    }

    void TerminalInfoProvider::setBackgroundColor(const std::string& newBackgroundColor)
    {
        throwIfUnsupportedFeature("background color", {FileType::Gif, FileType::Jpeg, FileType::LaTeX, FileType::Pdf, FileType::Png, FileType::PostScript});
        backgroundColor = newBackgroundColor;
    }

    void TerminalInfoProvider::clearBackgroundColor()
    {
        backgroundColor.reset();
    }

    std::optional<LineEnds> TerminalInfoProvider::getLineEnds() const
    {
        return lineEnds;
    }

    void TerminalInfoProvider::setLineEnds(const LineEnds newLineEnds)
    {
        throwIfUnsupportedFeature("line ends", {FileType::Gif, FileType::Jpeg, FileType::LaTeX, FileType::Pdf, FileType::Png, FileType::PostScript});
        lineEnds = newLineEnds;
    }

    void TerminalInfoProvider::clearLineEnds()
    {
        lineEnds.reset();
    }

    std::optional<bool> TerminalInfoProvider::getTransparent() const
    {
        return transparent;
    }

    void TerminalInfoProvider::setTransparent(bool newTransparent)
    {
        throwIfUnsupportedFeature("transparent background", {FileType::Gif, FileType::Png});
        transparent = newTransparent;
    }

    void TerminalInfoProvider::clearTransparent()
    {
        transparent.reset();
    }

    std::optional<bool> TerminalInfoProvider::getAnimate() const
    {
        return animate;
    }

    void TerminalInfoProvider::setAnimate(bool newAnimate)
    {
        throwIfUnsupportedFeature("animation", {FileType::Gif});
        animate = newAnimate;
    }

    void TerminalInfoProvider::clearAnimate()
    {
        animate.reset();
    }

    std::optional<int> TerminalInfoProvider::getDelay() const
    {
        return delay;
    }

    void TerminalInfoProvider::setDelay(int newDelay)
    {
        throwIfUnsupportedFeature("animation delay", {FileType::Gif});
        animate = true;
        delay = newDelay;
    }

    void TerminalInfoProvider::clearDelay()
    {
        delay.reset();
    }

    std::optional<int> TerminalInfoProvider::getLoopCount() const
    {
        return loopCount;
    }

    void TerminalInfoProvider::setLoopCount(int newLoopCount)
    {
        throwIfUnsupportedFeature("animation loop count", {FileType::Gif});
        animate = true;
        loopCount = newLoopCount;
    }

    void TerminalInfoProvider::clearLoopCount()
    {
        loopCount.reset();
    }

    std::optional<std::string> TerminalInfoProvider::getWindowTitle() const
    {
        return windowTitle;
    }

    void TerminalInfoProvider::setWindowTitle(const std::string& newWindowTitle)
    {
        throwIfUnsupportedFeature("window title", {FileType::Screen});
        windowTitle = newWindowTitle;
    }

    void TerminalInfoProvider::clearWindowTitle()
    {
        windowTitle.reset();
    }

    std::optional<int> TerminalInfoProvider::getWindowNumber() const
    {
        return windowNumber;
    }

    void TerminalInfoProvider::setWindowNumber(int newWindowNumber)
    {
        throwIfUnsupportedFeature("window number", {FileType::Screen});
        windowNumber = newWindowNumber;
    }

    void TerminalInfoProvider::clearWindowNumber()
    {
        windowNumber.reset();
    }

    std::optional<std::string> TerminalInfoProvider::getOptions() const
    {
        return options;
    }

    void TerminalInfoProvider::setOptions(const std::string& newOptions)
    {
        options = newOptions;
    }

    void TerminalInfoProvider::clearOptions()
    {
        options.reset();
    }
}
