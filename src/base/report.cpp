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

    // ====================================================================== //

    Report::Report() :
        SheetsCollection(allowedSheetTypes)
    {}

    Report::Report(FileType fileType) :
        SheetsCollection(allowedSheetTypes)
    {
        setFileType(fileType);
    }

    Report& Report::reset()
    {
        clearSheets();

        outputDirectory     = "";
        filenameBase        = "report";

        extTxt              = "txt";
        extDat              = "dat";
        extGnu              = "gnuplot";

        verbose             = true;
        autoRunScript       = true;

        pageSeparatorTxt    = "================================================================================\n";

        m_stylesCollection.reset();
        m_terminalInfoProvider.reset();

        return *this;
    }

    TerminalInfoProvider& Report::terminalInfoProvider()
    {
        return m_terminalInfoProvider;
    }

    // ====================================================================== //

    Report& Report::setFileType(FileType newFileType)
    {
        m_terminalInfoProvider.setFileType(newFileType);
        return *this;
    }

    const std::string& Report::getTerminal() const
    {
        return m_terminalInfoProvider.getTerminal();
    }

    Report& Report::setTerminal(const std::string& newTerminal)
    {
        m_terminalInfoProvider.setTerminal(newTerminal);
        return *this;
    }

    Report& Report::setOutputDirectory(const std::string& newOutputDirectory)
    {
        throwIfInvalidFilename("output directory", newOutputDirectory);
        outputDirectory = newOutputDirectory;
        return *this;
    }

    const std::string& Report::getFilenameBase() const
    {
        return filenameBase;
    }

    Report& Report::setFilenameBase(const std::string& newFilenameBase)
    {
        throwIfInvalidFilename("filename base", newFilenameBase);
        filenameBase = newFilenameBase;
        return *this;
    }

    const std::string& Report::getExtTxt() const
    {
        return extTxt;
    }

    Report& Report::setExtTxt(const std::string& newExtTxt)
    {
        throwIfInvalidFilename("extension for text files", newExtTxt);
        extTxt = newExtTxt;
        return *this;
    }

    const std::string& Report::getExtDat() const
    {
        return extDat;
    }

    Report& Report::setExtDat(const std::string& newExtDat)
    {
        throwIfInvalidFilename("extension for gnuplot data files", newExtDat);
        extDat = newExtDat;
        return *this;
    }

    const std::string& Report::getExtOut() const
    {
        return m_terminalInfoProvider.getExtOut();
    }

    Report& Report::setExtOut(const std::string& newExtOut)
    {
        m_terminalInfoProvider.setExtOut(newExtOut);
        return *this;
    }

    const std::string& Report::getExtGnu() const
    {
        return extGnu;
    }

    Report& Report::setExtGnu(const std::string& newExtGnu)
    {
        throwIfInvalidFilename("extension for gnuplot script files", newExtGnu);
        extGnu = newExtGnu;
        return *this;
    }

    bool Report::getVerbose() const
    {
        return verbose;
    }

    Report& Report::setVerbose(bool newVerbose)
    {
        verbose = newVerbose;
        return *this;
    }

    bool Report::getAutoRunScript() const
    {
        return autoRunScript;
    }

    Report& Report::setAutoRunScript(bool newAutoRunScript)
    {
        autoRunScript = newAutoRunScript;
        return *this;
    }

    const std::string& Report::getOutputDirectory() const
    {
        return outputDirectory;
    }

    const std::string& Report::getPageSeparatorTxt() const
    {
        return pageSeparatorTxt;
    }

    Report& Report::setPageSeparatorTxt(const std::string& newNewPageTXT)
    {
        pageSeparatorTxt = newNewPageTXT;
        return *this;
    }

    StylesCollection& Report::stylesCollection()
    {
        return m_stylesCollection;
    }


    std::string Report::getCustomScriptBegin() const
    {
        return customScriptBegin.value_or("");
    }

    Report& Report::setCustomScriptBegin(const std::string& newCustomScriptBegin)
    {
        customScriptBegin = newCustomScriptBegin;
        return *this;
    }

    Report& Report::clearCustomScriptBegin()
    {
        customScriptBegin.reset();
        return *this;
    }

    std::string Report::getCustomScriptEnd() const
    {
        return customScriptEnd.value_or("");
    }

    Report& Report::setCustomScriptEnd(const std::string& newCustomScriptEnd)
    {
        customScriptEnd = newCustomScriptEnd;
        return *this;
    }

    Report& Report::clearCustomScriptEnd()
    {
        customScriptEnd.reset();
        return *this;
    }

    // ====================================================================== //

    void Report::writeReport() const
    {
        writeDat();
        writeScript();
    }

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
        // *INDENT-OFF*
        if (verbose) {std::cout << "about to write TXT report " << filenameBase << " ..." << std::endl;}
        // *INDENT-OFF*

        preprocessSheets(extTxt);

        for (size_t i = 1u; auto sheet : sheets)
        {
            sheet->writeTxtHead  (hFile);
            sheet->writeTxtData  (hFile);
            sheet->writeTxtOverlays(hFile);
            sheet->writeTxtFooter(hFile, i);

            if (i != sheets.size())
            {
                hFile << pageSeparatorTxt;
            }
            ++i;
        }

        // *INDENT-OFF*
        if (verbose) {std::cout << "TXT report for " << filenameBase << " completed." << std::endl;}
        // *INDENT-OFF*
    }

    void Report::writeScript(std::ostream& hFile) const
    {
        const std::string outputFilename = getOutputFilename(m_terminalInfoProvider.getExtOut());

        // *INDENT-OFF*
        if (verbose) {std::cout << "about to write script for " << outputFilename << " ..." << std::endl;}

        preprocessSheets(extDat);

        hFile << "# " << std::string(76, '=') << " #" << std::endl;
        hFile << "# terminal setup" << std::endl << std::endl;

        m_terminalInfoProvider.writeTerminalInfo(hFile);

        if (customScriptBegin.has_value()) {
            hFile << "# " << std::string(76, '=') << " #" << std::endl;
            hFile << "# user setup script" << std::endl << std::endl;

            hFile << customScriptBegin.value() << std::endl << std::endl;
        }

        if (m_terminalInfoProvider.getOutputToFile()) {
            hFile << "set output '" << outputFilename << "'" << std::endl << std::endl;
        }

        m_stylesCollection.writeStyles(hFile);

        for (size_t i = 1u; auto sheet : sheets)
        {
            if (verbose) {std::cout << "writing scrpt for sheet #" << i << " ... ";}

            hFile << "# " << std::string(76, '=') << " #\n";
            hFile << "# page " << i << std::endl << std::endl;

            sheet->writeScriptHead      (hFile);
            sheet->writeScriptOverlays  (hFile);
            sheet->writeScriptData      (hFile, m_stylesCollection);
            sheet->writeScriptFooter    (hFile, i);
            ++i;

            if (verbose) {std::cout << "done." << std::endl;}
        }

        if (customScriptEnd.has_value()) {
            hFile << "# " << std::string(76, '=') << " #" << std::endl;
            hFile << "# user finalize script" << std::endl << std::endl;

            hFile << customScriptEnd.value() << std::endl << std::endl;
        }

        if (verbose) {std::cout << "script for " << outputFilename << " completed." << std::endl;}
        // *INDENT-ON*
    }
}
