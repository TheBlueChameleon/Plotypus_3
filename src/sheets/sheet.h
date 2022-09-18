#ifndef SHEET_H
#define SHEET_H

#include <string>
#include <vector>

#include "../collections/overlayscollection.h"

#include "../definitions/types.h"

#include "../elements/overlay.h"
#include "../elements/label.h"

namespace Plotypus
{
    /**
     * @todo objects (rects, ellipses, ...), arrows
     *
     * @todo externalize OverlayCollection
     */
    class Sheet : public OverlaysCollection
    {
        protected:
            const SheetType type;

            std::optional<std::string> title;
            std::optional<std::string> defaultFont = "Arial,7";
            std::optional<std::string> titleFont = "Arial:bold*2";

            std::optional<SheetPosition_t> origin;
            std::optional<SheetPosition_t> size;

            std::optional<std::string> customScriptBegin;
            std::optional<std::string> customScriptInter;
            std::optional<std::string> customScriptEnd;

            Overlay& addOverlay (Overlay* newOverlay);

        public:
            Sheet(const SheetType& type);
            Sheet(const SheetType& type, const std::string& title);

            virtual Sheet& reset();

            SheetType                   getType() const;

            const std::string           getTitle() const;
            Sheet&                      setTitle(const std::string& newTitle);
            Sheet&                      clearTitle();

            const std::string           getDefaultFont() const;
            Sheet&                      setDefaultFont(const std::string& newDefaultFont);
            Sheet&                      clearDefaultFont();

            const std::string           getTitleFont() const;
            Sheet&                      setTitleFont(const std::string& newTitleFont);
            Sheet&                      clearTitleFont();

            const SheetPosition_t       getOrigin() const;
            Sheet&                      setOrigin(const SheetPosition_t& newOrigin);
            Sheet&                      clearOrigin();

            const SheetPosition_t       getSize() const;
            Sheet&                      setSize(const SheetPosition_t& newSize);
            Sheet&                      clearSize();

            const std::string           getCustomScriptBegin() const;
            Sheet&                      setCustomScriptBegin(const std::string& newCustomScriptBegin);
            Sheet&                      clearCustomScriptBegin();

            const std::string           getCustomScriptInter() const;
            Sheet&                      setCustomScriptInter(const std::string& newCustomScriptInter);
            Sheet&                      clearCustomScriptInter();

            const std::string           getCustomScriptEnd() const;
            Sheet&                      setCustomScriptEnd(const std::string& newCustomScriptEnd);
            Sheet&                      clearCustomScriptEnd();

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            //! @todo implement reasonable specific body
            virtual void writeTxtHead       (std::ostream& hFile) const;
            virtual void writeTxtData       (std::ostream& hFile) const;
            virtual void writeTxtOverlays   (std::ostream& hFile) const;
            virtual void writeTxtFooter     (std::ostream& hFile, const int pageNum) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesCollection) const;
            virtual void writeScriptOverlays(std::ostream& hFile) const;
            virtual void writeScriptFooter  (std::ostream& hFile, const int pageNum) const;
    };
}

#include "sheet.txx"
#endif // SHEET_H
