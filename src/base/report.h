#ifndef REPORT_H
#define REPORT_H

#include <fstream>
#include <string>
#include <vector>

#include "../definitions/types.h"
#include "../plot/plot2d.h"

#include "util.h"
#include "sheet.h"
#include "stylescollection.h"

namespace Plotypus
{
    /**
     * @brief Collection of individual Sheets that together form the output document
     *
     * A Plotypus::Report represents a collection of instances of Sheet and provides an interface to create
     * Sheets and write all related output to files.
     */

    class Report
    {
        private:
            std::string terminal = "pdfcairo";

            std::vector<Plotypus::Sheet*> sheets;

            std::string outputDirectory = "";
            std::string filenameBase    = "report";

            std::string extTxt = "txt";
            std::string extDat = "dat";
            std::string extOut = "pdf";
            std::string extGnu = "gnuplot";

            bool verbose       = true;
            bool autoRunScript = true;

            std::string pageSeparatorTxt        = "================================================================================\n";
            std::string frameSeparatorTxt       = "--------------------------------------------------------------------------------\n";

            StylesCollection stylesCollection;

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
            void reset();

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
            //! @brief adds an empty Plot2D to the report and returns a modifiably reference to the newly created Plot2D.
            Plotypus::Plot2D& addPlot2D(const std::string& title = "");

            // -------------------------------------------------------------- //
            // file output specs

            /**
             * @brief changes the default values for terminal engine and output filename extension associated with the new FileType
             *
             * | FileType     | Terminal Engine | Extension |
             * |--------------|-----------------|-----------|
             * | `Pdf`        | pdfcairo        | pdf       |
             * | `Png`        | pngcairo        | png       |
             * | `PostScript` | epscairo        | eps       |
             * | `Gif`        | gif animate     | gif       |
             */
            void                setFileType(FileType newFileType);

            //! @brief returns the name of the currently used terminal engine
            const std::string&  getTerminal() const;
            //! @brief sets the currently used terminal engine. Plotypus makes no checks of validity.
            void                setTerminal(const std::string& newTerminal);

            //! @brief returns the directory, in which all output files will be written
            const std::string&  getOutputDirectory() const;
            //! @brief sets the output file, in which all output files will be written, or throws InvalidFilenameError, if an invalid character was detected.
            void                setOutputDirectory(const std::string& newOutputDirectory);
            //! @brief returns the string from which the filenames of the output files will be derived by appending page- subplot- and data-ID
            const std::string&  getFilenameBase() const;
            //! @brief sets the string from which the filenames of the output files will be derived by appending page- supblot- and data-ID
            void                setFilenameBase(const std::string& newFilenameBase);

            //! @brief returns the extension used for human-readable text reports
            const std::string&  getExtTxt() const;
            //! @brief sets the extension used for human-readable text reports. A leading dot should \em not be used.
            void                setExtTxt(const std::string& newExtTXT);
            //! @brief returns the extension used for gnuplot data files.
            const std::string&  getExtDat() const;
            //! @brief sets the extension used for gnuplot data files. A leading dot should \em not be used.
            void                setExtDat(const std::string& newExtDAT);
            //! @brief returns the extension of the output of the gnuplot script.
            const std::string&  getExtOut() const;
            //! @brief sets the extension of the output of the gnuplot script. A leading dot should \em not be used.
            void                setExtOut(const std::string& newExtOUT);
            //! @brief returns the extension of the generated gnuplot script.
            const std::string&  getExtGnu() const;
            //! @brief setsthe extension of the generated gnuplot script. A leading dot should \em not be used.
            void                setExtGnu(const std::string& newExtGNU);

            bool                getVerbose() const;
            void                setVerbose(bool newVerbose);
            bool                getAutoRunScript() const;
            void                setAutoRunScript(bool newAutoRunScript);

            const std::string&  getPageSeparatorTxt() const;
            void                setPageSeparatorTxt(const std::string& newNewPageTXT);

            StylesCollection&   getStylesCollection();
            void                setStylesCollection(const StylesCollection& newStylesCollection);

            // -------------------------------------------------------------- //
            // writers

            void writeTxt   () const;
            void writeDat   () const;
            void writeScript() const;

            void writeTxt   (std::ostream& hFile) const;
            void writeScript(std::ostream& hFile) const;
    };

}

#include "report.txx"
#endif // REPORT_H

