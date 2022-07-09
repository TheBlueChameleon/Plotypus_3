#include <filesystem>
#include <iostream>

#include "../definitions/errors.h"

#include "localMacros.h"
#include "report.h"

namespace fs = std::filesystem;
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

    // ====================================================================== //

    Report::Report()
    {}

    Report::~Report()
    {
        for (auto ptr : sheets)
        {
            delete ptr;
        }
    }

    // ====================================================================== //

    size_t Report::getReportSize() const
    {
        return sheets.size();
    }

    Sheet& Report::addSheet(const std::string& title)
    {
        sheets.push_back(new Sheet(title));
        return *sheets.back();
    }

    Sheet& Report::getSheet(int i) const
    {
        CHECK_INDEX_EXT(i, sheets, "sheet index");
        return *(sheets[i]);
    }

    // ====================================================================== //

    const char* Report::getInvalidFilenameChars() const
    {
        return invalidFilenameChars;
    }

    const std::string& Report::getSeparatorTxt() const
    {
        return separatorTxt;
    }

    void Report::setSeparatorTxt(const std::string& newSeparatorTXT)
    {
        separatorTxt = newSeparatorTXT;
    }

    const std::string& Report::getSeparatorDat() const
    {
        return separatorDat;
    }

    void Report::setSeparatorDat(const std::string& newSeparatorDAT)
    {
        separatorDat = newSeparatorDAT;
    }

    const std::string& Report::getOutputDirectory() const
    {
        return outputDirectory;
    }

    const std::string& Report::getNewPageTxt() const
    {
        return newPageTxt;
    }

    void Report::setNewPageTxt(const std::string& newNewPageTXT)
    {
        newPageTxt = newNewPageTXT;
    }

    const std::string& Report::getNewFrameTxt() const
    {
        return newFrameTxt;
    }

    void Report::setNewFrameTxt(const std::string& newNewFrameTXT)
    {
        newFrameTxt = newNewFrameTXT;
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

    const std::string& Report::getExtTxt() const
    {
        return extTxt;
    }

    void Report::setExtTxt(const std::string& newExtTXT)
    {
        throwIfInvalidFilename("extension for text files", newExtTXT);
        extTxt = newExtTXT;
    }

    const std::string& Report::getExtDat() const
    {
        return extDat;
    }

    void Report::setExtDat(const std::string& newExtDAT)
    {
        throwIfInvalidFilename("extension for gnuplot data files", newExtDAT);
        extDat = newExtDAT;
    }

    const std::string& Report::getExtTex() const
    {
        return extTex;
    }

    void Report::setExtTex(const std::string& newExtTEX)
    {
        throwIfInvalidFilename("extension for latex files", newExtTEX);
        extTex = newExtTEX;
    }

    const std::string& Report::getExtPdf() const
    {
        return extPdf;
    }

    void Report::setExtPdf(const std::string& newExtPDF)
    {
        throwIfInvalidFilename("extension for PDF files", newExtPDF);
        extPdf = newExtPDF;
    }

    const std::string& Report::getExtGnu() const
    {
        return extGnu;
    }

    void Report::setExtGnu(const std::string& newExtGNU)
    {
        throwIfInvalidFilename("extension for gnuplot script files", newExtGNU);
        extGnu = newExtGNU;
    }

    std::string Report::getOutputFilename(const std::string& extension) const
    {
        fs::path p(outputDirectory);
        p.append(filenameBase);
        p.concat(".");
        p.concat(extension);

        return p;
    }

    bool Report::getAutoRunScript() const
    {
        return autoRunScript;
    }

    void Report::setAutoRunScript(bool newAutoRunScript)
    {
        autoRunScript = newAutoRunScript;
    }

    bool Report::getStandaloneTex() const
    {
        return standaloneTex;
    }

    void Report::setStandaloneTex(bool newStandaloneTEX)
    {
        standaloneTex = newStandaloneTEX;
    }

    int Report::getNumberPrecision() const
    {
        return numberPrecision;
    }

    void Report::setNumberPrecision(int newNumberPrecision)
    {
        numberPrecision = newNumberPrecision;
    }

    // ====================================================================== //

    void Report::writeTxt()
    {
        const std::string filename = getOutputFilename(extTxt);
        std::ofstream hFile(filename);

        if (!hFile.is_open())
        {
            throw FileIOError(THROWTEXT("Could not open '"s + filename + "'"));
        }

        for (size_t i = 1u; auto sheet : sheets)
        {
            sheet->writeTxtHead  (hFile);
            sheet->writeTxtData  (hFile);
            sheet->writeTxtLabels(hFile);
            sheet->writeTxtFooter(hFile, i);

            if (i != sheets.size())
            {
                hFile << newPageTxt;
            }
            ++i;
        }
    }

    void Report::writePdf()
    {
        const std::string filenameGnu = getOutputFilename(extGnu),
                          filenamePdf = getOutputFilename(extPdf);
        std::ofstream hFile(filenameGnu);

        if (!hFile.is_open())
        {
            throw FileIOError(THROWTEXT("Could not open '"s + filenameGnu + "'"));
        }

        hFile << "# " << std::string(76, '=') << " #" << std::endl;
        hFile << "# output setup" << std::endl << std::endl;
        hFile << "set term pdfcairo" << std::endl;
        hFile << "set output '" << filenamePdf << "'" << std::endl << std::endl;

        for (size_t i = 1u; auto sheet : sheets)
        {
            hFile << "# " << std::string(76, '=') << " #\n";
            hFile << "# page " << i << std::endl << std::endl;

            sheet->writePdfHead  (hFile);
            sheet->writePdfSetup (hFile);
            sheet->writePdfData  (hFile);
            sheet->writePdfLabels(hFile);
            sheet->writePdfFooter(hFile, i);
            ++i;
        }
    }
}
