#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "../definitions/errors.h"

#include "../plot/plot2d.h"

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

    void Report::runGnuplot(const std::string& filename) const
    {
        // *INDENT-OFF*
        if (verbose)    {std::cout << "About to run gnuplot script '" << filename << "' ..." << std::endl;}

        const auto error = std::system((std::string("gnuplot ") + filename).data());

        if (verbose) {
            if (error)  {std::cerr << "gnuplot did not succeed. Error code: " << error << std::endl;}
            else        {std::cout << "done." << std::endl;}
        }
        // *INDENT-ON*
    }

    void Report::writeCleanSheetCommands(std::ofstream& hFile)
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
        for (auto ptr : sheets)
        {
            delete ptr;
        }
        sheets.clear();

        outputDirectory = "";
        filenameBase = "report";

        extTxt = "txt";
        extDat = "dat";
        extTex = "tex";
        extPdf = "pdf";
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

    Sheet& Report::addPlot2D(const std::string& title)
    {
        sheets.push_back(new Plot2D(title));
        return *sheets.back();
    }

    Sheet& Report::sheet(int i) const
    {
        CHECK_INDEX_EXT(i, sheets, "sheet index");
        return *(sheets[i]);
    }

    // ====================================================================== //

    const char* Report::getInvalidFilenameChars() const
    {
        return invalidFilenameChars;
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
                hFile << pageSeparatorTxt;
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

        bool needCleanSheetCommands = true;

        hFile << "# " << std::string(76, '=') << " #" << std::endl;
        hFile << "# output setup" << std::endl << std::endl;
        hFile << "set term pdfcairo" << std::endl;
        hFile << "set output '" << filenamePdf << "'" << std::endl << std::endl;

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

            sheet->writePdfHead  (hFile);
            sheet->writePdfData  (hFile);
            sheet->writePdfLabels(hFile);
            sheet->writePdfFooter(hFile, i);
            ++i;
        }

        hFile.close();

        if (autoRunScript)
        {
            runGnuplot(filenameGnu);
        }
    }
}
