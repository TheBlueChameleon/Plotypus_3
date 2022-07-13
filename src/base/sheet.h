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

            std::vector<Label> labels;

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

            size_t                          getLabelCount() const;
            const std::vector<Label>&       getLabels() const;
            void                            setLabels(const std::vector<Label>& newLabels);
            Label&                             label (const size_t i);
            size_t                          addLabel (const Label& newLabel);
            size_t                          addLabel (const std::string& text, double x, double y, bool boxed = false, int boxStyleID = -1);
            void                            clearLabels();

            // writers
            virtual void writeTxtHead       (std::ostream& hFile) const;
            virtual void writeTxtData       (std::ostream& hFile) const;
            virtual void writeTxtLabels     (std::ostream& hFile) const;
            virtual void writeTxtFooter     (std::ostream& hFile, int pageNum) const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile) const;
            virtual void writeScriptLabels  (std::ostream& hFile) const;
            virtual void writeScriptFooter  (std::ostream& hFile, int pageNum) const;
    };
}

#endif // SHEET_H
