#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>

#include "util.h"

#include "stylescollection.h"
#include "terminalinfoprovider.h"

namespace Plotypus
{
    /**
     * @brief Collection of individual Sheets that together form the output document
     *
     * A Plotypus::Report represents a collection of instances of Sheet and provides an interface to create
     * Sheets and write all related output to files.
     *
     * @todo better support for Filetype Screen
     * @todo move responsibility for "tidy up code" to individual sheets
     * @todo monadic design: setters return ref to self
     */

    class PlotOrthogonalAxes;
    class Sheet;
    class StylesCollection;
    class TerminalInfoProvider;

    class Report
    {
        private:
            std::vector<Plotypus::Sheet*> sheets;

            std::string outputDirectory     = "";
            std::string filenameBase        = "report";

            std::string extTxt              = "txt";
            std::string extDat              = "dat";
            std::string extGnu              = "gnuplot";

            bool verbose                    = true;
            bool autoRunScript              = true;

            std::string pageSeparatorTxt    = "================================================================================\n";
            std::string frameSeparatorTxt   = "--------------------------------------------------------------------------------\n";

            StylesCollection        m_stylesCollection;
            TerminalInfoProvider    m_terminalInfoProvider;

            void preprocessSheets(const std::string& extension) const;
            std::string getOutputFilename(const std::string& extension, const std::string& infix = "") const;

            void writeCleanSheetCommands(std::ostream& hFile) const;

        public:
            //! @brief Default CTor for setting up a PDF report with pdfcairo as terminal engine.
            Report();
            /**
             * @brief Sets up a Report using a specified FileType.
             *
             * see Report::setFileType for the effects of the different FileTypes.
             */
            Report(FileType fileType);
            ~Report();

            //! @brief restores the state generated by the default CTor
            Report& reset();

            TerminalInfoProvider& terminalInfoProvider();

            // -------------------------------------------------------------- //
            // content management

            //! @brief returns the number of Sheets currently registered to the Report.
            size_t getReportSize() const;

            //! @brief returns a modifiable reference to the `i`<sup>th</sup> Sheet or throws an InvalidIndexError if `i` does not refer to an existing sheet.
            Plotypus::Sheet& sheet(const size_t i) const;

            //! @brief returns a modifiable reference to the `i`<sup>th</sup> Sheet and applies a dynamic cast to class `T`.
            template<SheetLike T>
            T& sheetAs(const size_t i);

            //! @brief adds an empty Sheet to the report and returns a modifiably reference to the newly created Sheet.
            Plotypus::Sheet&  addSheet (const std::string& title = "");
            //! @brief adds an empty PlotWithAxes to the report and returns a modifiably reference to the newly created PlotWithAxes.
            Plotypus::PlotOrthogonalAxes& addPlotOrthogonalAxes(const std::string& title = "");

            Report& clearSheets();

            // -------------------------------------------------------------- //
            // file output specs

            /**
             * @brief changes the default values for terminal engine and output filename extension associated with the new FileType
             */
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

            StylesCollection&   stylesCollection();

            // -------------------------------------------------------------- //
            // writers

            Report& writeTxt   ();
            Report& writeDat   ();
            Report& writeScript();

            Report& writeTxt   (std::ostream& hFile);
            Report& writeScript(std::ostream& hFile);
    };
}

#include "report.txx"
#endif // REPORT_H

