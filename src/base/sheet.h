#ifndef SHEET_H
#define SHEET_H

#include <fstream>
#include <string>
#include <vector>

#include "../definitions/types.h"

namespace Plotypus
{
    class Sheet
    {
        protected:
            // .............................................................. //
            // behaviour objects

            PlotType type;

            std::string title = "";
            std::string defaultFont = "arial,7";

            std::string customScriptBegin = "";
            std::string customScriptEnd   = "";

            std::vector<Label>    labels;

        public:
            Sheet(const std::string& title);

            PlotType getType() const;

            virtual void reset();

            const std::string&  getTitle() const;
            void                setTitle(const std::string& newTitle);

            const std::string&  getDefaultFont() const;
            void                setDefaultFont(const std::string& newDefaultFont);

            const std::string&  getCustomScriptBegin() const;
            void                setCustomScriptBegin(const std::string& newCustomScriptBegin);
            const std::string&  getCustomScriptEnd() const;
            void                setCustomScriptEnd(const std::string& newCustomScriptEnd);

            const std::vector<Label>&       getLabels() const;
            void                            setLabels(const std::vector<Label>& newLabels);
            Label&                             label (const size_t i);
            void                            addLabel (const Label& newLabel);
            void                            addLabel (const std::string& text, double x, double y, bool boxed = false, int boxStyleID = -1);
            void                            clearLabels();

            // writers
            virtual void writeTxtHead   (std::ofstream& hFile);
            virtual void writeTxtData   (std::ofstream& hFile);
            virtual void writeTxtLabels (std::ofstream& hFile);
            virtual void writeTxtFooter (std::ofstream& hFile, int pageNum);

            virtual void writePdfHead   (std::ofstream& hFile);
            virtual void writePdfData   (std::ofstream& hFile);
            virtual void writePdfLabels (std::ofstream& hFile);
            virtual void writePdfFooter (std::ofstream& hFile, int pageNum);
    };

}

#endif // SHEET_H
