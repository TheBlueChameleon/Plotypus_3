#include <iostream>

#include "../definitions/errors.h"

#include "localMacros.h"
#include "report.h"

using namespace Plotypus;

namespace Plotypus
{
    void Report::throwIfInvalidFilename(const std::string& component, const std::string& stringToTest) const
    {
        if (stringToTest.find_first_of(invalidFilenameChars) != std::string::npos)
        {
            throw InvalidFilenameError(THROWTEXT("    Attempted to set invalid "s + component + ".\n" +
                                                 "    value               : '" + stringToTest + "'\n" +
                                                 "    forbidden characters: " + invalidFilenameChars
                                                ));
        }
    }

    Report::Report()
    {}

    Report::~Report()
    {
        for (auto ptr : sheets)
        {
            delete ptr;
        }
    }

    size_t Report::getReportSize() const
    {
        return sheets.size();
    }

    Sheet& Report::addSheet()
    {
        sheets.push_back(new Sheet);
//        std::cout << "pushed sheet at " << sheets.back() << std::endl;

        return *sheets.back();
    }

    Sheet& Report::getSheet(int i) const
    {
        const int maxSize = sheets.size();
        // *INDENT-OFF*
        if      (i >= maxSize) {THROW_INVALID_INDEX(i, "sheet index");}
        else if (i <        0) {
            i += maxSize;
            if  (i <        0) {THROW_INVALID_INDEX(i, "sheet index");}
        }
        // *INDENT-ON*

        return *(sheets[i]);
    }

    const char* Report::getInvalidFilenameChars() const
    {
        return invalidFilenameChars;
    }

    const std::string& Report::getOutputDirectory() const
    {
        return outputDirectory;
    }

    void Report::setOutputDirectory(const std::string& newOutputDirectory)
    {
        throwIfInvalidFilename("output directory", newOutputDirectory);
        outputDirectory = newOutputDirectory;
    }

    const std::string& Report::getFilenameBase() const
    {
        return filenameBase;
    }

    void Report::setFilenameBase(const std::string& newFilenameBase)
    {
        throwIfInvalidFilename("filename base", newFilenameBase);
        filenameBase = newFilenameBase;
    }

    const std::string& Report::getExtTXT() const
    {
        return extTXT;
    }

    void Report::setExtTXT(const std::string& newExtTXT)
    {
        throwIfInvalidFilename("extension for text files", newExtTXT);
        extTXT = newExtTXT;
    }

    const std::string& Report::getExtDAT() const
    {
        return extDAT;
    }

    void Report::setExtDAT(const std::string& newExtDAT)
    {
        throwIfInvalidFilename("extension for gnuplot data files", newExtDAT);
        extDAT = newExtDAT;
    }

    const std::string& Report::getExtTEX() const
    {
        return extTEX;
    }

    void Report::setExtTEX(const std::string& newExtTEX)
    {
        throwIfInvalidFilename("extension for latex files", newExtTEX);
        extTEX = newExtTEX;
    }

    const std::string& Report::getExtPDF() const
    {
        return extPDF;
    }

    void Report::setExtPDF(const std::string& newExtPDF)
    {
        throwIfInvalidFilename("extension for PDF files", newExtPDF);
        extPDF = newExtPDF;
    }

    const std::string& Report::getExtGNU() const
    {
        return extGNU;
    }

    void Report::setExtGNU(const std::string& newExtGNU)
    {
        throwIfInvalidFilename("extension for gnuplot script files", newExtGNU);
        extGNU = newExtGNU;
    }

    bool Report::getAutoRunScript() const
    {
        return autoRunScript;
    }

    void Report::setAutoRunScript(bool newAutoRunScript)
    {
        autoRunScript = newAutoRunScript;
    }

    bool Report::getStandaloneTEX() const
    {
        return standaloneTEX;
    }

    void Report::setStandaloneTEX(bool newStandaloneTEX)
    {
        standaloneTEX = newStandaloneTEX;
    }

    int Report::getNumberPrecision() const
    {
        return numberPrecision;
    }

    void Report::setNumberPrecision(int newNumberPrecision)
    {
        numberPrecision = newNumberPrecision;
    }
}
