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
            std::string defaultFont = "Arial,7";
            std::string titleFont = "Arial:bold*2";

            std::string customScriptBegin = "";
            std::string customScriptEnd   = "";

            std::string datalineSeparatorTxt = "................................................................................\n";

            std::vector<Label> labels;
            /**
             * @todo objects (rects, ellipses, ...)
             *      arrows
             */

        public:
            Sheet(const std::string& title);

            PlotType getType() const;

            virtual void reset();

            const std::string&          getTitle() const;
            void                        setTitle(const std::string& newTitle);

            const std::string&          getDefaultFont() const;
            void                        setDefaultFont(const std::string& newDefaultFont);
            const std::string&          getTitleFont() const;
            void                        setTitleFont(const std::string& newTitleFont);

            const std::string&          getCustomScriptBegin() const;
            void                        setCustomScriptBegin(const std::string& newCustomScriptBegin);
            const std::string&          getCustomScriptEnd() const;
            void                        setCustomScriptEnd(const std::string& newCustomScriptEnd);

            const std::string&          getDatalineSeparatorTxt() const;
            void                        setDatalineSeparatorTxt(const std::string& newDatalineSeparatorTxt);

            size_t                      getLabelCount() const;
            const std::vector<Label>&   getLabels() const;
            void                        setLabels(const std::vector<Label>& newLabels);
            Label&                         label (const size_t i);
            Label&                      addLabel (const Label& newLabel);
            Label&                      addLabel (const std::string& text, double x, double y, bool boxed = false, int boxStyleID = 0);
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

    // ====================================================================== //
    /**
     * @brief foo bar
     */
    template <typename T>
    concept SheetLike = std::is_base_of<Sheet, T>::value;
}

#endif // SHEET_H
