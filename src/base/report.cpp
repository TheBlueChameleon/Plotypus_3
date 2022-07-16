#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "../definitions/errors.h"



#include "localMacros.h"
#include "report.h"

namespace fs = std::filesystem;
using namespace Plotypus;

namespace Plotypus
{
    void Report::writeCleanSheetCommands(std::ostream& hFile) const
    {
        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# prepare empty page" << std::endl << std::endl;

        hFile << "set key off"  << std::endl;
        hFile << "unset border" << std::endl;
        hFile << "unset xtics"  << std::endl;
        hFile << "unset xlabel" << std::endl;
        hFile << "unset ytics"  << std::endl;
        hFile << "unset ylabel" << std::endl;
        hFile << "unset ztics"  << std::endl;
        hFile << "unset zlabel" << std::endl;

        hFile << "set xrange[0:1]" << std::endl;
        hFile << "set yrange[1:0]" << std::endl;
        hFile << std::endl;
    }

    // ====================================================================== //

    Report::Report()
    {}

    Report::~Report()
    {
        reset();
    }

    void Report::reset()
    {
        fileType = FileType::Pdf;
        terminal = "pdfcairo";

        for (auto ptr : sheets)
        {
            delete ptr;
        }
        sheets.clear();

        outputDirectory = "";
        filenameBase = "report";

        extTxt = "txt";
        extDat = "dat";
        extOut = "pdf";
        extGnu = "gnuplot";

        verbose       = true;
        autoRunScript = true;
        standaloneTex = true;

        numberPrecision = 6;           // used only in txt and tex output

        columnSeparatorTxt = "\t";
        columnSeparatorDat = "\t";

        pageSeparatorTxt  = "================================================================================\n";
        frameSeparatorTxt = "--------------------------------------------------------------------------------\n";

        stylesCollection.reset();
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

    Sheet& Report::sheet(const size_t i) const
    {
        CHECK_INDEX(i, sheets, "sheet index");
        return *(sheets[i]);
    }

    // ====================================================================== //

    FileType Report::getFileType() const
    {
        return fileType;
    }

    void Report::setFileType(FileType newFileType)
    {
        fileType = newFileType;
        switch (newFileType)
        {
            case FileType::Pdf:
                terminal = "pdfcairo";
                extOut = "pdf";
                break;
            case FileType::Png:
                terminal = "pngcairo";
                extOut = "png";
                break;
            case FileType::PostScript:
                terminal = "epscairo";
                extOut = "eps";
                break;
        }
    }

    const std::string& Report::getTerminal() const
    {
        return terminal;
    }

    void Report::setTerminal(const std::string& newTerminal)
    {
        terminal = newTerminal;
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

    const std::string& Report::getExtOut() const
    {
        return extOut;
    }

    void Report::setExtOut(const std::string& newExtPDF)
    {
        throwIfInvalidFilename("extension for PDF files", newExtPDF);
        extOut = newExtPDF;
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

    std::string Report::getOutputFilename(const std::string& extension, const std::string& infix) const
    {
        fs::path p(outputDirectory);
        p.append(filenameBase);

        if (!infix.empty())
        {
            p.concat(infix);
        }

        if (!extension.empty())
        {
            p.concat(".");
            p.concat(extension);
        }

        return p;
    }

    bool Report::getVerbose() const
    {
        return verbose;
    }

    void Report::setVerbose(bool newVerbose)
    {
        verbose = newVerbose;
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

    const std::string& Report::getColumnSeparatorTxt() const
    {
        return columnSeparatorTxt;
    }

    void Report::setColumnSeparatorTxt(const std::string& newSeparatorTXT)
    {
        columnSeparatorTxt = newSeparatorTXT;
    }

    const std::string& Report::getColumnSeparatorDat() const
    {
        return columnSeparatorDat;
    }

    void Report::setColumnSeparatorDat(const std::string& newSeparatorDAT)
    {
        columnSeparatorDat = newSeparatorDAT;
    }

    const std::string& Report::getOutputDirectory() const
    {
        return outputDirectory;
    }

    const std::string& Report::getPageSeparatorTxt() const
    {
        return pageSeparatorTxt;
    }

    void Report::setPageSeparatorTxt(const std::string& newNewPageTXT)
    {
        pageSeparatorTxt = newNewPageTXT;
    }

    StylesCollection& Report::getStylesCollection()
    {
        return stylesCollection;
    }

    void Report::setStylesCollection(const StylesCollection& newStylesCollection)
    {
        stylesCollection = newStylesCollection;
    }

    // ====================================================================== //

    void Report::preprocessSheets(const std::string& extension) const
    {
        for (size_t i = 1u; auto sheet : sheets)
        {
            const std::string autoOutputFilename = getOutputFilename("", "_" + std::to_string(i));
            sheet->preprocessSheet(autoOutputFilename, extension);
            ++i;
        }
    }

    void Report::writeTxt() const
    {
        const std::string filename = getOutputFilename(extTxt);
        std::fstream hFile = openOrThrow(filename);
        writeTxt(hFile);
    }

    void Report::writeDat() const
    {
        const std::string filename = getOutputFilename(extDat);
        std::fstream hFile = openOrThrow(filename);
        writeDat(hFile);
    }

    void Report::writeScript() const
    {
        const std::string filenameGnu = getOutputFilename(extGnu);
        std::fstream hFile = openOrThrow(filenameGnu);

        writeScript(hFile);
        hFile.close();

        if (autoRunScript)
        {
            runGnuplot(filenameGnu, verbose);
        }
    }

    void Report::writeTxt(std::ostream& hFile) const
    {
        preprocessSheets(extTxt);

        for (size_t i = 1u; auto sheet : sheets)
        {
            sheet->writeTxtHead  (hFile);
            sheet->writeTxtData  (hFile);
            sheet->writeTxtLabels(hFile);
            sheet->writeTxtFooter(hFile, i);

            if (i != sheets.size())
            {
                hFile << pageSeparatorTxt;
            }
            ++i;
        }
    }

    void Report::writeDat(std::ostream& hFile) const
    {
        preprocessSheets(extDat);


    }

    void Report::writeScript(std::ostream& hFile) const
    {
        preprocessSheets(extDat);

        const std::string   outputFilename  = getOutputFilename(extOut);
        bool                needCleanSheetCommands = true;

        hFile << "# " << std::string(76, '=') << " #" << std::endl;
        hFile << "# output setup" << std::endl << std::endl;
        hFile << "set term " << terminal << std::endl;
        hFile << "set output '" << outputFilename << "'" << std::endl << std::endl;

        stylesCollection.writeBoxStyles (hFile);
        stylesCollection.writeLineStyles(hFile);

        for (size_t i = 1u; auto sheet : sheets)
        {
            hFile << "# " << std::string(76, '=') << " #\n";
            hFile << "# page " << i << std::endl << std::endl;

            // *INDENT-OFF*
            if (needCleanSheetCommands && sheet->getType() == PlotType::Sheet) {needCleanSheetCommands = false; writeCleanSheetCommands(hFile);
            } else if                    (sheet->getType() != PlotType::Sheet) {needCleanSheetCommands = true ;}
            // *INDENT-ON*

            sheet->writeScriptHead  (hFile);
            sheet->writeScriptData  (hFile);
            sheet->writeScriptLabels(hFile);
            sheet->writeScriptFooter(hFile, i);
            ++i;
        }
    }
}
