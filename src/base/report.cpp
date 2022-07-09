#include "report.h"

namespace Plotypus
{
    Report::Report() {}

//    const std::string &Report::getInvalidFilenameChars() const
//    {
//        return invalidFilenameChars;
//    }

    const std::string& Report::getOutputDirectory() const
    {
        return outputDirectory;
    }

    void Report::setOutputDirectory(const std::string& newOutputDirectory)
    {
        outputDirectory = newOutputDirectory;
    }

    const std::string& Report::getFilenameBase() const
    {
        return filenameBase;
    }

    void Report::setFilenameBase(const std::string& newFilenameBase)
    {
        filenameBase = newFilenameBase;
    }

    const std::string& Report::getExtTXT() const
    {
        return extTXT;
    }

    void Report::setExtTXT(const std::string& newExtTXT)
    {
        extTXT = newExtTXT;
    }

    const std::string& Report::getExtGNU() const
    {
        return extGNU;
    }

    void Report::setExtGNU(const std::string& newExtGNU)
    {
        extGNU = newExtGNU;
    }

    const std::string& Report::getExtTEX() const
    {
        return extTEX;
    }

    void Report::setExtTEX(const std::string& newExtTEX)
    {
        extTEX = newExtTEX;
    }

    const std::string& Report::getExtPDF() const
    {
        return extPDF;
    }

    void Report::setExtPDF(const std::string& newExtPDF)
    {
        extPDF = newExtPDF;
    }

    const std::string& Report::getExtScript() const
    {
        return extSCRIPT;
    }

    void Report::setExtScript(const std::string& newExtSCRIPT)
    {
        extSCRIPT = newExtSCRIPT;
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
