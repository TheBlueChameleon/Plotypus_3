#ifndef SHEET_H
#define SHEET_H

#include <string>
#include <vector>

#include "../definitions/types.h"

namespace Plotypus
{
    /**
     * @todo objects (rects, ellipses, ...), arrows
     * @todo introduce customScriptInter, before plot, after generated.
     */
    class Sheet
    {
        protected:
            // .............................................................. //
            // behaviour objects

            SheetType type;

            std::optional<std::string> title;
            std::optional<std::string> defaultFont = "Arial,7";
            std::optional<std::string> titleFont = "Arial:bold*2";

            std::optional<std::string> customScriptBegin;
            std::optional<std::string> customScriptInter;
            std::optional<std::string> customScriptEnd;

            std::vector<Label_deprecated> labels;

        public:
            Sheet(const std::string& title);

            SheetType getType() const;

            virtual Sheet& reset();

            const std::string           getTitle() const;
            Sheet&                      setTitle(const std::string& newTitle);
            Sheet&                      clearTitle();

            const std::string           getDefaultFont() const;
            Sheet&                      setDefaultFont(const std::string& newDefaultFont);
            Sheet&                      clearDefaultFont();

            const std::string           getTitleFont() const;
            Sheet&                      setTitleFont(const std::string& newTitleFont);
            Sheet&                      clearTitleFont();

            const std::string           getCustomScriptBegin() const;
            Sheet&                      setCustomScriptBegin(const std::string& newCustomScriptBegin);
            Sheet&                      clearCustomScriptBegin();

            const std::string           getCustomScriptInter() const;
            Sheet&                      setCustomScriptInter(const std::string& newCustomScriptInter);
            Sheet&                      clearCustomScriptInter();

            const std::string           getCustomScriptEnd() const;
            Sheet&                      setCustomScriptEnd(const std::string& newCustomScriptEnd);
            Sheet&                      clearCustomScriptEnd();

            size_t                      getLabelCount() const;
            const std::vector<Label_deprecated>&   getLabels() const;
            Sheet&                      setLabels(const std::vector<Label_deprecated>& newLabels);
            Label_deprecated&                         label (const size_t i);
            Label_deprecated&                      addLabel (const Label_deprecated& newLabel);
            Label_deprecated&                      addLabel (const std::string& text, double x, double y, bool boxed = false, size_t boxStyleID = OPTIONAL_SIZE_T_DEFAULT);
            void                        clearLabels();

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeTxtHead       (std::ostream& hFile) const;
            virtual void writeTxtData       (std::ostream& hFile) const;
            virtual void writeTxtLabels     (std::ostream& hFile) const;
            virtual void writeTxtFooter     (std::ostream& hFile, const int pageNum) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesColloction) const;
            virtual void writeScriptLabels  (std::ostream& hFile) const;
            virtual void writeScriptFooter  (std::ostream& hFile, const int pageNum) const;
    };
}

#endif // SHEET_H
