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

            int  numberPrecision = 6;           // used only in txt output

            std::string columnSeparatorTxt = "\t";
            std::string columnSeparatorDat = "\t";

            std::string pageSeparatorTxt  = "================================================================================\n";
            std::string frameSeparatorTxt = "--------------------------------------------------------------------------------\n";

            StylesCollection stylesCollection;

            void writeCleanSheetCommands(std::ostream& hFile) const;

        public:
            Report();
            Report(FileType fileType);
            ~Report();

            void reset();

            // -------------------------------------------------------------- //
            // content management

            size_t getReportSize() const;

            Plotypus::Sheet& sheet(const size_t i) const;

            Plotypus::Sheet&  addSheet (const std::string& title = "");
            Plotypus::Plot2D& addPlot2D(const std::string& title = "");

            // -------------------------------------------------------------- //
            // file output specs

            void                setFileType(FileType newFileType);

            const std::string&  getTerminal() const;
            void                setTerminal(const std::string& newTerminal);

            const std::string&  getOutputDirectory() const;
            void                setOutputDirectory(const std::string& newOutputDirectory);
            const std::string&  getFilenameBase() const;
            void                setFilenameBase(const std::string& newFilenameBase);

            const std::string&  getExtTxt() const;
            void                setExtTxt(const std::string& newExtTXT);
            const std::string&  getExtDat() const;
            void                setExtDat(const std::string& newExtDAT);
            const std::string&  getExtOut() const;
            void                setExtOut(const std::string& newExtPDF);
            const std::string&  getExtGnu() const;
            void                setExtGnu(const std::string& newExtGNU);

            std::string         getOutputFilename(const std::string& extension, const std::string& infix = "") const;

            bool                getVerbose() const;
            void                setVerbose(bool newVerbose);
            bool                getAutoRunScript() const;
            void                setAutoRunScript(bool newAutoRunScript);

            int                 getNumberPrecision() const;
            void                setNumberPrecision(int newNumberPrecision);

            const std::string&  getColumnSeparatorTxt() const;
            void                setColumnSeparatorTxt(const std::string& newSeparatorTXT);
            const std::string&  getColumnSeparatorDat() const;
            void                setColumnSeparatorDat(const std::string& newSeparatorDAT);
            const std::string&  getPageSeparatorTxt() const;
            void                setPageSeparatorTxt(const std::string& newNewPageTXT);

            StylesCollection&   getStylesCollection();
            void                setStylesCollection(const StylesCollection& newStylesCollection);

            // -------------------------------------------------------------- //
            // writers

            void preprocessSheets(const std::string& extension) const;

            void writeTxt   () const;
            void writeDat   () const;
            void writeScript() const;

            void writeTxt   (std::ostream& hFile) const;
            void writeScript(std::ostream& hFile) const;
    };

}
#include "report.txx"
#endif // REPORT_H

