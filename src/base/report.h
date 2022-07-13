#ifndef REPORT_H
#define REPORT_H

#include <fstream>
#include <string>
#include <vector>

#include "../definitions/types.h"
#include "../plot/plot2d.h"

#include "sheet.h"
#include "stylescollection.h"

namespace Plotypus
{
    class Report
    {
        private:
            std::vector<Plotypus::Sheet*> sheets;

            constexpr static auto invalidFilenameChars = "*~|:;<> '\"";

            std::string outputDirectory;
            std::string filenameBase = "report";

            std::string extTxt = "txt";
            std::string extDat = "dat";
            std::string extTex = "tex";
            std::string extPdf = "pdf";
            std::string extGnu = "gnuplot";

            bool verbose       = true;
            bool autoRunScript = true;
            bool standaloneTex = true;

            int  numberPrecision = 6;           // used only in txt and tex output

            std::string columnSeparatorTxt = "\t";
            std::string columnSeparatorDat = "\t";

            std::string pageSeparatorTxt  = "================================================================================\n";
            std::string frameSeparatorTxt = "--------------------------------------------------------------------------------\n";

            StylesCollection stylesCollection;

            void throwIfInvalidFilename(const std::string& component, const std::string& stringToTest) const;
            void runGnuplot(const std::string& filename) const;
            void writeCleanSheetCommands(std::ostream& hFile);

        public:
            Report();
            ~Report();

            void reset();

            // -------------------------------------------------------------- //
            // content management

            size_t getReportSize() const;

            Plotypus::Sheet& addSheet (const std::string& title = "");

            template <class T>
            Plotypus::Plot2D<T>& addPlot2D(const std::string& title = "");

            Plotypus::Sheet& sheet(const size_t i) const;

            // -------------------------------------------------------------- //
            // file output specs

            const char*         getInvalidFilenameChars() const;

            const std::string&  getOutputDirectory() const;
            void                setOutputDirectory(const std::string& newOutputDirectory);
            const std::string&  getFilenameBase() const;
            void                setFilenameBase(const std::string& newFilenameBase);

            const std::string&  getExtTxt() const;
            void                setExtTxt(const std::string& newExtTXT);
            const std::string&  getExtDat() const;
            void                setExtDat(const std::string& newExtDAT);
            const std::string&  getExtTex() const;
            void                setExtTex(const std::string& newExtTEX);
            const std::string&  getExtPdf() const;
            void                setExtPdf(const std::string& newExtPDF);
            const std::string&  getExtGnu() const;
            void                setExtGnu(const std::string& newExtGNU);

            std::string         getOutputFilename(const std::string& extension) const;

            bool                getVerbose() const;
            void                setVerbose(bool newVerbose);
            bool                getAutoRunScript() const;
            void                setAutoRunScript(bool newAutoRunScript);
            bool                getStandaloneTex() const;
            void                setStandaloneTex(bool newStandaloneTEX);

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

            void writeTxt   ();
            void writeTex   ();
            void writeDat   ();
            void writeScript();

            void writeTxt   (std::ostream& hFile);
            void writeTex   (std::ostream& hFile);
            void writeDat   (std::ostream& hFile);
            void writeScritp(std::ostream& hFile);
    };

}
#endif // REPORT_H

#include "report.txx"
