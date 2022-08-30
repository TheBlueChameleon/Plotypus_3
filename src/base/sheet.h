#ifndef SHEET_H
#define SHEET_H

#include <string>
#include <vector>

#include "../definitions/types.h"

#include "../elements/overlay.h"
#include "../elements/label.h"

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

            std::vector<Overlay*> overlays;

        public:
            Sheet(const std::string& title);
            ~Sheet();

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

            size_t                      getOverlayCount() const;

            Overlay&                    overlay (const size_t i);
            template<OverlayLike T>
            T&                          overlayAs(const size_t i);

            Overlay&                    addOverlay (Overlay* newOverlay);
            void                        clearOverlays();

            Label&                      addLabel (const std::string& text, double x, double y, bool boxed = false, size_t boxStyleID = OPTIONAL_SIZE_T_DEFAULT);

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeTxtHead       (std::ostream& hFile) const;
            virtual void writeTxtData       (std::ostream& hFile) const;
            virtual void writeTxtOverlays   (std::ostream& hFile) const;
            virtual void writeTxtFooter     (std::ostream& hFile, const int pageNum) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesColloction) const;
            virtual void writeScriptOverlays(std::ostream& hFile) const;
            virtual void writeScriptFooter  (std::ostream& hFile, const int pageNum) const;
    };
}

#include "sheet.txx"
#endif // SHEET_H
