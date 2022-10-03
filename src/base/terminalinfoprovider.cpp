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

    void TerminalInfoProvider::throwIfDimensionsNotOfType(const dimensions_t& dimensions, size_t i) const
    {
        if (dimensions.index() != i)
        {
            throw InvalidArgumentError("    Invalid dimensions specification.\n"
                                       "      given   : "s + getDimensionTypeName(dimensions) + "\n"
                                       "      terminal: "s + getTerminalName(fileType));
        }
    }

    void TerminalInfoProvider::throwIfUnsupportedFeature(const std::string& feature, const std::vector<FileType>& supportedTerminals) const
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

    void TerminalInfoProvider::writeDimensions(std::ostream& hFile) const
    {
        if (dimensions.has_value())
        {
            hFile << "size ";

            std::visit(
                [&hFile](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, dimensions_pixels_t>)
                {
                    hFile << arg.first << ", " << arg.second;
                }
                else if constexpr (std::is_same_v<T, dimensions_length_with_unit_t>)
                {
                    const dimensions_length_t&  numbers = arg.first;
                    const std::string&          unit    = arg.second;

                    hFile << numbers.first << unit << ", " << numbers.second << unit;
                }

            }, dimensions.value());

            hFile << " ";
        }
    }

    void TerminalInfoProvider::writePosition(std::ostream& hFile) const
    {
        if (position.has_value())
        {
            const auto& value = position.value();
            hFile << "position " << value.first << ", " << value.second << " ";
        }
    }

    void TerminalInfoProvider::writeBackground(std::ostream& hFile) const
    {
        if (backgroundColor.has_value())
        {
            const auto& value = backgroundColor.value();
            hFile << "background " << std::quoted(value) << " ";
        }
    }

    void TerminalInfoProvider::writeLineEnds(std::ostream& hFile) const
    {
        switch (lineEnds)
        {
            case LineEnds::Default:
                break;
            case LineEnds::Butt:
                hFile << "butt";
                break;
            case LineEnds::Rounded:
                hFile << (fileType == FileType::LaTeX ? "" : "rounded");
                break;
        }
        hFile << " ";
    }

    void TerminalInfoProvider::writeTransparent(std::ostream& hFile) const
    {
        if (transparent.has_value())
        {
            const auto& value = transparent.value();
            if (!value)
            {
                hFile << "no";
            }
            hFile << "transparent ";
        }
    }

    void TerminalInfoProvider::writeAnimateX(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if (animate.has_value())
        {
            const auto& value = animate.value();
            if (value)                  {hFile << "animate ";}
            else                        {return;}

            if (delay    .has_value())  {hFile << "delay " << delay    .value() << " ";}
            if (loopCount.has_value())  {hFile << "loop "  << loopCount.value() << " ";}
        }
        // *INDENT-ON*
    }

    void TerminalInfoProvider::writeWindowTitle(std::ostream& hFile) const
    {
        if (windowTitle.has_value())
        {
            const auto& value = windowTitle.value();
            hFile << "title " << std::quoted(value) << " ";
        }
    }

    void TerminalInfoProvider::writeWindowNumber(std::ostream& hFile) const
    {
        if (windowNumber.has_value())
        {
            const auto& value = windowNumber.value();
            hFile << value << " ";
        }
    }

    void TerminalInfoProvider::writeOptions(std::ostream& hFile) const
    {
        if (options.has_value())
        {
            const auto& value = options.value();
            hFile << value << " ";
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

    TerminalInfoProvider& TerminalInfoProvider::reset()
    {
        fileType        = FileType::Pdf;
        terminal        = "pdfcairo";
        extOut          = "pdf";
        outputToFile    = true;
        dimensions      .reset();
        position        .reset();
        backgroundColor .reset();
        lineEnds        = LineEnds::Default;
        transparent     .reset();
        animate         .reset();
        delay           .reset();
        loopCount       .reset();
        windowTitle     .reset();
        windowNumber    .reset();
        options         .reset();

        return *this;
    }

    // ---------------------------------------------------------------------- //

    FileType TerminalInfoProvider::getFileType() const
    {
        return fileType;
    }

    TerminalInfoProvider& TerminalInfoProvider::setFileType(FileType newFileType)
    {
        reset();

        switch(newFileType)
        {
            case FileType::Custom:
                terminal = "";
                extOut   = "";
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
        return *this;
    }

    const std::string& TerminalInfoProvider::getTerminal() const
    {
        return terminal;
    }

    TerminalInfoProvider& TerminalInfoProvider::setTerminal(const std::string& newTerminal)
    {
        setFileType(FileType::Custom);
        terminal = newTerminal;
        return *this;
    }

    const std::string& TerminalInfoProvider::getExtOut() const
    {
        return extOut;
    }

    TerminalInfoProvider& TerminalInfoProvider::setExtOut(const std::string& newExtOut)
    {
        throwIfInvalidFilename("extension for script output", newExtOut);
        extOut = newExtOut;
        return *this;
    }

    bool TerminalInfoProvider::getOutputToFile() const
    {
        return outputToFile;
    }

    TerminalInfoProvider& TerminalInfoProvider::setOutputToFile(bool newOutputToFile)
    {
        outputToFile = newOutputToFile;
        return *this;
    }

    // ---------------------------------------------------------------------- //

    TerminalInfoProvider::dimensions_t TerminalInfoProvider::getDimensions() const
    {
        return dimensions.value_or(dimensions_t());
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const dimensions_t& newDimensions)
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
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const dimensions_pixels_t& newDimensions)
    {
        return setDimensions(dimensions_t(newDimensions));
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const dimensions_length_t& newDimensions)
    {
        const std::string lengthUnitString = getLengthUnitName(LengthUnit::Inch);
        dimensions_length_with_unit_t fullySpecifiedDimensions = std::make_pair(newDimensions, lengthUnitString);
        return setDimensions(dimensions_t(fullySpecifiedDimensions));
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const dimensions_length_t& newDimensions, const LengthUnit lengthUnit)
    {
        const std::string lengthUnitString = getLengthUnitName(lengthUnit);
        dimensions_length_with_unit_t fullySpecifiedDimensions = std::make_pair(newDimensions, lengthUnitString);
        return setDimensions(dimensions_t(fullySpecifiedDimensions));
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const dimensions_length_with_unit_t& newDimensions)
    {
        return setDimensions(dimensions_t(newDimensions));
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const int width, const int height)
    {
        return setDimensions(std::make_pair(width, height));
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const double width, const double height)
    {
        return setDimensions(std::make_pair(width, height));
    }

    TerminalInfoProvider& TerminalInfoProvider::setDimensions(const double width, const double height, const LengthUnit lengthUnit)
    {
        return setDimensions(std::make_pair(width, height), lengthUnit);
    }

    TerminalInfoProvider& TerminalInfoProvider::clearDimensions()
    {
        dimensions.reset();
        return *this;
    }

    // ---------------------------------------------------------------------- //

    TerminalInfoProvider::dimensions_pixels_t TerminalInfoProvider::getPosition() const
    {
        return position.value_or(dimensions_pixels_t());
    }

    TerminalInfoProvider& TerminalInfoProvider::setPosition(const dimensions_pixels_t& newPosition)
    {
        throwIfUnsupportedFeature("position", {FileType::Screen});
        position = newPosition;
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearPosition()
    {
        position.reset();
        return *this;
    }

    std::string TerminalInfoProvider::getBackgroundColor() const
    {
        return backgroundColor.value_or("");
    }

    TerminalInfoProvider& TerminalInfoProvider::setBackgroundColor(const std::string& newBackgroundColor)
    {
        throwIfUnsupportedFeature("background color", {FileType::Gif, FileType::Jpeg, FileType::LaTeX, FileType::Pdf, FileType::Png, FileType::PostScript});
        backgroundColor = newBackgroundColor;
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearBackgroundColor()
    {
        backgroundColor.reset();
        return *this;
    }

    LineEnds TerminalInfoProvider::getLineEnds() const
    {
        return lineEnds;
    }

    TerminalInfoProvider& TerminalInfoProvider::setLineEnds(const LineEnds newLineEnds)
    {
        throwIfUnsupportedFeature("line ends", {FileType::Gif, FileType::Jpeg, FileType::LaTeX, FileType::Pdf, FileType::Png, FileType::PostScript});
        lineEnds = newLineEnds;
        return *this;
    }

    bool TerminalInfoProvider::getTransparent() const
    {
        return transparent.value_or(false);
    }

    TerminalInfoProvider& TerminalInfoProvider::setTransparent(bool newTransparent)
    {
        throwIfUnsupportedFeature("transparent background", {FileType::Gif, FileType::Png});
        transparent = newTransparent;
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearTransparent()
    {
        transparent.reset();
        return *this;
    }

    bool TerminalInfoProvider::getAnimate() const
    {
        return animate.value_or(false);
    }

    TerminalInfoProvider& TerminalInfoProvider::setAnimate(bool newAnimate)
    {
        throwIfUnsupportedFeature("animation", {FileType::Gif});
        animate = newAnimate;
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearAnimate()
    {
        animate  .reset();
        delay    .reset();
        loopCount.reset();
        return *this;
    }

    size_t TerminalInfoProvider::getDelay() const
    {
        return delay.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    TerminalInfoProvider& TerminalInfoProvider::setDelay(const size_t newDelay)
    {
        throwIfUnsupportedFeature("animation delay", {FileType::Gif});
        animate = true;
        setOptionalSizeTOrClearIfDefault(delay, newDelay);
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearDelay()
    {
        delay.reset();
        return *this;
    }

    size_t TerminalInfoProvider::getLoopCount() const
    {
        return loopCount.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    TerminalInfoProvider& TerminalInfoProvider::setLoopCount(const size_t newLoopCount)
    {
        throwIfUnsupportedFeature("animation loop count", {FileType::Gif});
        animate = true;
        setOptionalSizeTOrClearIfDefault(loopCount, newLoopCount);
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearLoopCount()
    {
        loopCount.reset();
        return *this;
    }

    std::string TerminalInfoProvider::getWindowTitle() const
    {
        return windowTitle.value_or("");
    }

    TerminalInfoProvider& TerminalInfoProvider::setWindowTitle(const std::string& newWindowTitle)
    {
        throwIfUnsupportedFeature("window title", {FileType::Screen});
        windowTitle = newWindowTitle;
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearWindowTitle()
    {
        windowTitle.reset();
        return *this;
    }

    size_t TerminalInfoProvider::getWindowNumber() const
    {
        return windowNumber.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    TerminalInfoProvider& TerminalInfoProvider::setWindowNumber(const size_t newWindowNumber)
    {
        throwIfUnsupportedFeature("window number", {FileType::Screen});
        setOptionalSizeTOrClearIfDefault(windowNumber, newWindowNumber);
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearWindowNumber()
    {
        windowNumber.reset();
        return *this;
    }

    std::string TerminalInfoProvider::getOptions() const
    {
        return options.value_or("");
    }

    TerminalInfoProvider& TerminalInfoProvider::setOptions(const std::string& newOptions)
    {
        options = newOptions;
        return *this;
    }

    TerminalInfoProvider& TerminalInfoProvider::clearOptions()
    {
        options.reset();
        return *this;
    }

    // ====================================================================== //

    void TerminalInfoProvider::writeTerminalInfo(std::ostream& hFile) const
    {
        hFile << "set term " << terminal << " ";
        writeDimensions  (hFile);
        writePosition    (hFile);
        writeBackground  (hFile);
        writeLineEnds    (hFile);
        writeTransparent (hFile);
        writeAnimateX    (hFile);
        writeWindowTitle (hFile);
        writeWindowNumber(hFile);
        writeOptions     (hFile);

        hFile << std::endl << std::endl;
    }
}
