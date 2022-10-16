#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>

#include "util.h"

#include "terminalinfoprovider.h"

#include "../collections/sheetscollection.h"
#include "../collections/stylescollection.h"
#include "../definitions/types.h"

namespace Plotypus
{
    /**
     * @brief Collection of individual Sheets that together form the output document
     *
     * A Plotypus::Report represents a collection of instances of Sheet and provides an interface to create
     * Sheets and write all related output to files.
     *
     * @todo better support for Filetype Screen
     * @todo rethink auto-preprocess mechanism wrt. repetition of same action on write{txt|dat|script}
     * @todo runScript only via writeReport?
     */

    class Sheet;
    class StylesCollection;
    class TerminalInfoProvider;

    class Report : public SheetsCollection
    {
        private:
            static constexpr std::initializer_list<SheetType> allowedSheetTypes = {SheetType::Sheet,
                                                                                   SheetType::PlotDefault,
                                                                                   SheetType::PlotRadial,
                                                                                   SheetType::Multiplot
                                                                                  };

            StylesCollection            m_stylesCollection;
            TerminalInfoProvider        m_terminalInfoProvider;

            bool                        verbose             = true;
            bool                        autoRunScript       = true;

            std::string                 pageSeparatorTxt    = "================================================================================\n";

            std::optional<std::string>  customScriptBegin;
            std::optional<std::string>  customScriptEnd;

            void preprocessSheets(const std::string& extension) const;

        public:
            //! @brief Default CTor for setting up a PDF report with pdfcairo as terminal engine.
            Report();
            Report(FileType fileType);

            //! @brief restores the state generated by the default CTor
            Report& reset();

            StylesCollection&     stylesCollection();
            TerminalInfoProvider& terminalInfoProvider();

            // -------------------------------------------------------------- //
            // file output specs

            FileType            getFileType() const;
            //! @brief changes the default values for terminal engine and output filename extension associated with the new FileType
            Report&             setFileType(FileType newFileType);

            //! @brief returns the name of the currently used terminal engine
            const std::string&  getTerminal() const;
            //! @brief sets the currently used terminal engine. Plotypus makes no checks of validity.
            Report&             setTerminal(const std::string& newTerminal);

            //! @brief returns the directory, in which all output files will be written
            const std::string&  getOutputDirectory() const;
            //! @brief sets the output file, in which all output files will be written, or throws InvalidFilenameError, if an invalid character was detected.
            Report&             setOutputDirectory(const std::string& newOutputDirectory);
            //! @brief returns the string from which the filenames of the output files will be derived by appending page- subplot- and data-ID
            const std::string&  getFilenameBase() const;
            //! @brief sets the string from which the filenames of the output files will be derived by appending page- supblot- and data-ID
            Report&             setFilenameBase(const std::string& newFilenameBase);

            //! @brief returns the extension used for human-readable text reports
            const std::string&  getExtTxt() const;
            //! @brief sets the extension used for human-readable text reports. A leading dot should \em not be used.
            Report&             setExtTxt(const std::string& newExtTxt);
            //! @brief returns the extension used for gnuplot data files.
            const std::string&  getExtDat() const;
            //! @brief sets the extension used for gnuplot data files. A leading dot should \em not be used.
            Report&             setExtDat(const std::string& newExtDat);
            //! @brief returns the extension of the output of the gnuplot script.
            const std::string&  getExtOut() const;
            //! @brief sets the extension of the output of the gnuplot script. A leading dot should \em not be used.
            Report&             setExtOut(const std::string& newExtOut);
            //! @brief returns the extension of the generated gnuplot script.
            const std::string&  getExtGnu() const;
            //! @brief setsthe extension of the generated gnuplot script. A leading dot should \em not be used.
            Report&             setExtGnu(const std::string& newExtGnu);

            bool                getVerbose() const;
            Report&             setVerbose(bool newVerbose);
            bool                getAutoRunScript() const;
            Report&             setAutoRunScript(bool newAutoRunScript);

            const std::string&  getPageSeparatorTxt() const;
            Report&             setPageSeparatorTxt(const std::string& newNewPageTXT);

            std::string         getCustomScriptBegin() const;
            Report&             setCustomScriptBegin(const std::string& newCustomScriptBegin);
            Report&             clearCustomScriptBegin();

            std::string         getCustomScriptEnd() const;
            Report&             setCustomScriptEnd(const std::string& newCustomScriptEnd);
            Report&             clearCustomScriptEnd();

            // -------------------------------------------------------------- //
            // writers

            void writeReport() const;

            void writeTxt   () const;
            void writeDat   () const;
            void writeScript() const;

            void writeTxt   (std::ostream& hFile) const;
            void writeScript(std::ostream& hFile) const;
    };
}

//#include "report.txx"
#endif // REPORT_H
