#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "../definitions/errors.h"

#include "report.h"

namespace fs = std::filesystem;
using namespace Plotypus;

namespace Plotypus
{
    void Report::preprocessSheets(const std::string& extension) const
    {
        for (size_t i = 1u; auto sheet : sheets)
        {
            // *INDENT-OFF*
            if (verbose) {std::cout << "preprocessing sheet #" << i << " ... ";}

            const std::string autoOutputFilename = getOutputFilename("", "_" + std::to_string(i));
            sheet->preprocessSheet(autoOutputFilename, extension);
            ++i;

            if (verbose) {std::cout << "done." << std::endl;}
            // *INDENT-ON*
        }
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
        hFile << "unset rlabel" << std::endl;
        hFile << "unset rtics"  << std::endl;

        hFile << "set xrange[0:1]" << std::endl;
        hFile << "set yrange[1:0]" << std::endl;
        hFile << std::endl;
    }

    // ====================================================================== //

    Report::Report() {}

    Report::Report(FileType fileType)
    {
        setFileType(fileType);
    }

    Report::~Report()
    {
        clearSheets();
    }

    void Report::reset()
    {
        clearSheets();

        terminal            = "pdfcairo";

        outputDirectory     = "";
        filenameBase        = "report";

        extTxt              = "txt";
        extDat              = "dat";
        extOut              = "pdf";
        extGnu              = "gnuplot";

        verbose             = true;
        autoRunScript       = true;

        pageSeparatorTxt    = "================================================================================\n";
        frameSeparatorTxt   = "--------------------------------------------------------------------------------\n";

        m_stylesCollection.reset();
    }

    // ====================================================================== //

    size_t Report::getReportSize() const
    {
        return sheets.size();
    }

    Sheet& Report::sheet(const size_t i) const
    {
        checkIndex("sheet index", i, sheets);
        return *(sheets[i]);
    }

    Sheet& Report::addSheet(const std::string& title)
    {
        sheets.push_back(new Sheet(title));
        return *sheets.back();
    }

    Plot2D& Report::addPlot2D(const std::string& title)
    {
        Plot2D* newPlot = new Plot2D(title);
        sheets.push_back(newPlot);
        return *newPlot;
    }

    void Report::clearSheets()
    {
        for (auto ptr : sheets)
        {
            delete ptr;
        }
        sheets.clear();
    }

    // ====================================================================== //

    void Report::setFileType(FileType newFileType)
    {
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
            case FileType::Gif:
                terminal = "gif animate";
                extOut = "gif";
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
        checkFilename("output directory", newOutputDirectory);
        outputDirectory = newOutputDirectory;
    }

    const std::string& Report::getFilenameBase() const
    {
        return filenameBase;
    }

    void Report::setFilenameBase(const std::string& newFilenameBase)
    {
        checkFilename("filename base", newFilenameBase);
        filenameBase = newFilenameBase;
    }

    const std::string& Report::getExtTxt() const
    {
        return extTxt;
    }

    void Report::setExtTxt(const std::string& newExtTXT)
    {
        checkFilename("extension for text files", newExtTXT);
        extTxt = newExtTXT;
    }

    const std::string& Report::getExtDat() const
    {
        return extDat;
    }

    void Report::setExtDat(const std::string& newExtDAT)
    {
        checkFilename("extension for gnuplot data files", newExtDAT);
        extDat = newExtDAT;
    }

    const std::string& Report::getExtOut() const
    {
        return extOut;
    }

    void Report::setExtOut(const std::string& newExtOUT)
    {
        checkFilename("extension for PDF files", newExtOUT);
        extOut = newExtOUT;
    }

    const std::string& Report::getExtGnu() const
    {
        return extGnu;
    }

    void Report::setExtGnu(const std::string& newExtGNU)
    {
        checkFilename("extension for gnuplot script files", newExtGNU);
        extGnu = newExtGNU;
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

    StylesCollection& Report::stylesCollection()
    {
        return m_stylesCollection;
    }

    // ====================================================================== //

    void Report::writeTxt() const
    {
        const std::string filename = getOutputFilename(extTxt);
        std::fstream hFile = openOrThrow(filename);
        writeTxt(hFile);
    }

    void Report::writeDat() const
    {
        preprocessSheets(extDat);

        for (auto sheet : sheets)
        {
            sheet->writeDatData();
        }
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

    void Report::writeScript(std::ostream& hFile) const
    {
        const std::string   outputFilename  = getOutputFilename(extOut);
        bool                needCleanSheetCommands = true;

        if (verbose)
        {
            std::cout << "about to write script for " << outputFilename << " ..." << std::endl;
        }

        preprocessSheets(extDat);

        hFile << "# " << std::string(76, '=') << " #" << std::endl;
        hFile << "# output setup" << std::endl << std::endl;
        hFile << "set term " << terminal << std::endl;
        hFile << "set output '" << outputFilename << "'" << std::endl << std::endl;

        m_stylesCollection.writeStyles(hFile);

        for (size_t i = 1u; auto sheet : sheets)
        {
            // *INDENT-OFF*
            if (verbose) {std::cout << "writing scrpt for sheet #" << i << " ... ";}

            hFile << "# " << std::string(76, '=') << " #\n";
            hFile << "# page " << i << std::endl << std::endl;

            if (needCleanSheetCommands && sheet->getType() == PlotType::Sheet) {needCleanSheetCommands = false; writeCleanSheetCommands(hFile);}
            else if                      (sheet->getType() != PlotType::Sheet) {needCleanSheetCommands = true ;}

            sheet->writeScriptHead  (hFile);
            sheet->writeScriptData  (hFile, m_stylesCollection);
            sheet->writeScriptLabels(hFile);
            sheet->writeScriptFooter(hFile, i);
            ++i;

            if (verbose) {std::cout << "done." << std::endl;}
            // *INDENT-ON*
        }

        if (verbose)
        {
            std::cout << "script for " << outputFilename << " completed." << std::endl;
        }
    }
}
