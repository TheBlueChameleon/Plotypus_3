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

            std::string separatorTXT = "\t";
            std::string separatorDAT = "\t";

            std::string outputDirectory;
            std::string filenameBase = "report";

            std::string extTXT = "txt";
            std::string extDAT = "dat";
            std::string extTEX = "tex";
            std::string extPDF = "pdf";
            std::string extGNU = "gnuplot";

            bool autoRunScript = true;
            bool standaloneTEX = true;

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

            const std::string&  getSeparatorTXT() const;
            void                setSeparatorTXT(const std::string& newSeparatorTXT);
            const std::string&  getSeparatorDAT() const;
            void                setSeparatorDAT(const std::string& newSeparatorDAT);

            const std::string&  getOutputDirectory() const;
            void                setOutputDirectory(const std::string& newOutputDirectory);
            const std::string&  getFilenameBase() const;
            void                setFilenameBase(const std::string& newFilenameBase);

            const std::string&  getExtTXT() const;
            void                setExtTXT(const std::string& newExtTXT);
            const std::string&  getExtDAT() const;
            void                setExtDAT(const std::string& newExtDAT);
            const std::string&  getExtTEX() const;
            void                setExtTEX(const std::string& newExtTEX);
            const std::string&  getExtPDF() const;
            void                setExtPDF(const std::string& newExtPDF);
            const std::string&  getExtGNU() const;
            void                setExtGNU(const std::string& newExtGNU);

            bool                getAutoRunScript() const;
            void                setAutoRunScript(bool newAutoRunScript);
            bool                getStandaloneTEX() const;
            void                setStandaloneTEX(bool newStandaloneTEX);

            int                 getNumberPrecision() const;
            void                setNumberPrecision(int newNumberPrecision);

            // -------------------------------------------------------------- //
            // writers

            void writeTXT();
            void writeTEX();
            void writeGNU();
            void writeSCRIPT();
    };

}
#endif // REPORT_H
