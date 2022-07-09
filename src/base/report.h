#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>

#include "../definitions/types.h"
#include "sheet.h"

namespace Plotypus
{
    class Report
    {
        private:
            std::vector<Plotypus::Sheet*> sheets;

            constexpr static auto invalidFilenameChars = "*~|:;<> '\"";

            std::string separatorTxt = "\t";
            std::string separatorDat = "\t";

            std::string newPageTxt  = "================================================================================\n";
            std::string newFrameTxt = "--------------------------------------------------------------------------------\n";

            std::string outputDirectory;
            std::string filenameBase = "report";

            std::string extTxt = "txt";
            std::string extDat = "dat";
            std::string extTex = "tex";
            std::string extPdf = "pdf";
            std::string extGnu = "gnuplot";

            bool autoRunScript = true;
            bool standaloneTex = true;

            int  numberPrecision = 6;           // used only in txt output

            void throwIfInvalidFilename(const std::string& component, const std::string& stringToTest) const;

        public:
            Report();
            ~Report();

            // -------------------------------------------------------------- //
            // content management

            size_t getReportSize() const;

            Plotypus::Sheet& addSheet(const std::string& title = "");
            Plotypus::Sheet& getSheet(int i) const;

            // -------------------------------------------------------------- //
            // file output specs

            const char*         getInvalidFilenameChars() const;

            const std::string&  getSeparatorTxt() const;
            void                setSeparatorTxt(const std::string& newSeparatorTXT);
            const std::string&  getSeparatorDat() const;
            void                setSeparatorDat(const std::string& newSeparatorDAT);
            const std::string&  getNewPageTxt() const;
            void                setNewPageTxt(const std::string& newNewPageTXT);
            const std::string&  getNewFrameTxt() const;
            void                setNewFrameTxt(const std::string& newNewFrameTXT);

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

            std::string getOutputFilename(const std::string& extension) const;

            bool                getAutoRunScript() const;
            void                setAutoRunScript(bool newAutoRunScript);
            bool                getStandaloneTex() const;
            void                setStandaloneTex(bool newStandaloneTEX);

            int                 getNumberPrecision() const;
            void                setNumberPrecision(int newNumberPrecision);

            // -------------------------------------------------------------- //
            // writers

            void writeTxt();
            void writeTex();
            void writeDat();
            void writePdf();
    };

}
#endif // REPORT_H
