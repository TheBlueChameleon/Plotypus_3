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
        const std::string lengthUnitString = getLengthUnitName(LengthUnits::Inch);
        dimensions_length_with_unit_t fullySpecifiedDimensions = std::make_pair(newDimensions, lengthUnitString);
        setDimensions(dimensions_t(fullySpecifiedDimensions));
    }

    void TerminalInfoProvider::setDimensions(const dimensions_length_t& newDimensions, const LengthUnits lengthUnit)
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

    void TerminalInfoProvider::setDimensions(const double width, const double height, const LengthUnits lengthUnit)
    {
        setDimensions(std::make_pair(width, height), lengthUnit);
    }

    void TerminalInfoProvider::clearDimensions()
    {
        dimensions.reset();
    }
}
