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
            std::vector<Plotypus::Sheet*> pages;

            constexpr static auto invalidFilenameChars = "*~|:;<> '\"";

            std::string outputDirectory;
            std::string filenameBase = "report";

            std::string extTXT       = "txt";
            std::string extGNU       = "dat";
            std::string extTEX       = "tex";
            std::string extPDF       = "pdf";
            std::string extSCRIPT    = "gnuplot";

            bool autoRunScript = true;
            bool standaloneTEX = true;

            int  numberPrecision = 6;           // used only in txt output

        public:
            Report();

            //const std::string& getInvalidFilenameChars() const;

            const std::string&  getOutputDirectory() const;
            void                setOutputDirectory(const std::string& newOutputDirectory);
            const std::string&  getFilenameBase() const;
            void                setFilenameBase(const std::string& newFilenameBase);

            const std::string&  getExtTXT() const;
            void                setExtTXT(const std::string& newExtTXT);
            const std::string&  getExtGNU() const;
            void                setExtGNU(const std::string& newExtGNU);
            const std::string&  getExtTEX() const;
            void                setExtTEX(const std::string& newExtTEX);
            const std::string&  getExtPDF() const;
            void                setExtPDF(const std::string& newExtPDF);
            const std::string&  getExtScript() const;
            void                setExtScript(const std::string& newExtSCRIPT);

            bool                getAutoRunScript() const;
            void                setAutoRunScript(bool newAutoRunScript);
            bool                getStandaloneTEX() const;
            void                setStandaloneTEX(bool newStandaloneTEX);

            int                 getNumberPrecision() const;
            void                setNumberPrecision(int newNumberPrecision);
    };

}
#endif // REPORT_H
