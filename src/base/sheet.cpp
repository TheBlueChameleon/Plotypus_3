#include "sheet.h"
#include <iostream>

using namespace std::string_literals;

namespace Plotypus
{
    Sheet::Sheet(const SheetType& type) :
        type(type)
    {}

    Sheet::Sheet(const SheetType& type, const std::string& title) :
        type(type),
        title(title)
    {}

    Sheet::~Sheet()
    {
        clearOverlays();
    }

    // ====================================================================== //

    Sheet& Sheet::reset()
    {
        title.reset();
        defaultFont = "Arial,7";

        customScriptBegin.reset();
        customScriptInter.reset();
        customScriptEnd  .reset();

        clearOverlays();

        return *this;
    }

    SheetType Sheet::getType() const
    {
        return type;
    }

    const std::string Sheet::getTitle() const
    {
        return title.value_or("");
    }

    Sheet& Sheet::setTitle(const std::string& newTitle)
    {
        title = newTitle;
        return *this;
    }

    Sheet& Sheet::clearTitle()
    {
        title.reset();
        return *this;
    }

    const std::string Sheet::getDefaultFont() const
    {
        return defaultFont.value_or("");
    }

    Sheet& Sheet::setDefaultFont(const std::string& newDefaultFont)
    {
        defaultFont = newDefaultFont;
        return *this;
    }

    Sheet& Sheet::clearDefaultFont()
    {
        defaultFont.reset();
        return *this;
    }

    const std::string Sheet::getTitleFont() const
    {
        return titleFont.value_or("");
    }

    Sheet& Sheet::setTitleFont(const std::string& newTitleFont)
    {
        titleFont = newTitleFont;
        return *this;
    }

    Sheet& Sheet::clearTitleFont()
    {
        titleFont.reset();
        return *this;
    }

    const std::string Sheet::getCustomScriptBegin() const
    {
        return customScriptBegin.value_or("");
    }

    Sheet& Sheet::setCustomScriptBegin(const std::string& newCustomScriptBegin)
    {
        customScriptBegin = newCustomScriptBegin;
        return *this;
    }

    Sheet& Sheet::clearCustomScriptBegin()
    {
        customScriptBegin.reset();
        return *this;
    }

    const std::string Sheet::getCustomScriptInter() const
    {
        return customScriptInter.value_or("");
    }

    Sheet& Sheet::setCustomScriptInter(const std::string& newCustomScriptInter)
    {
        customScriptInter = newCustomScriptInter;
        return *this;
    }

    Sheet& Sheet::clearCustomScriptInter()
    {
        customScriptInter.reset();
        return *this;
    }

    const std::string Sheet::getCustomScriptEnd() const
    {
        return customScriptEnd.value_or("");
    }

    Sheet& Sheet::setCustomScriptEnd(const std::string& newCustomScriptEnd)
    {
        customScriptEnd = newCustomScriptEnd;
        return *this;
    }

    Sheet& Sheet::clearCustomScriptEnd()
    {
        customScriptEnd.reset();
        return *this;
    }

    // ====================================================================== //

    size_t Sheet::getOverlayCount() const
    {
        return overlays.size();
    }

    Overlay& Sheet::overlay(const size_t i)
    {
        throwIfInvalidIndex("label index", i, overlays);
        return *overlays[i];
    }

    void Sheet::clearOverlays()
    {
        for (auto overlay : overlays)
        {
            delete overlay;
        }
        overlays.clear();
    }

    Overlay& Sheet::addOverlay(Overlay* newOverlay)
    {
        overlays.push_back(newOverlay);
        return *overlays.back();
    }

    Label& Sheet::addLabel(const std::string& text, double x, double y, bool boxed, size_t boxStyleID)
    {
        return reinterpret_cast<Label&>(addOverlay( new Label(text, x, y, boxed, boxStyleID) ));
    }

    // ====================================================================== //
    // writers

    void Sheet::preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const {}

    void Sheet::writeTxtHead(std::ostream& hFile) const
    {
        if (title.has_value())
        {
            hFile << title.value() << std::endl;
            hFile << std::string(title.value().size(), '~') << std::endl;
        }
    }

    void Sheet::writeTxtData(std::ostream& hFile) const {}

    void Sheet::writeTxtOverlays(std::ostream& hFile) const
    {
        for (const auto& overlay : overlays)
        {
            overlay->writeTxt(hFile);
        }
    }

    void Sheet::writeTxtFooter(std::ostream& hFile, const int pageNum) const
    {
        const int lineWidth = 80;
        const int spaces = pageNum > 0 ?
                           lineWidth - (std::log10(pageNum + 1) + 1) :
                           lineWidth - 1;
        hFile << std::string(spaces, ' ') << std::to_string(pageNum) << std::endl;
    }

    void Sheet::writeDatData() const {}

    void Sheet::writeScriptHead(std::ostream& hFile) const
    {
        if (customScriptBegin.has_value())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script I" << std::endl << std::endl;
            hFile << customScriptBegin.value() << std::endl;
            hFile << std::endl;
        }

        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# generated setup script" << std::endl << std::endl;

        if (defaultFont.has_value())
        {
            hFile << "set font " << std::quoted(defaultFont.value()) << std::endl;
        }

        if (title.has_value())
        {
            hFile << "set title " << std::quoted("{/" + titleFont.value_or("") + " " + title.value() + "}") << std::endl;
        }
        hFile << std::endl;
    }

    void Sheet::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
    {
        if (customScriptInter.has_value())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script II" << std::endl << std::endl;
            hFile << customScriptInter.value() << std::endl;
            hFile << std::endl;
        }

        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# plot commands" << std::endl << std::endl;
    }

    void Sheet::writeScriptOverlays(std::ostream& hFile) const
    {
        if (overlays.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# overlays" << std::endl << std::endl;

            for (auto& overlay : overlays)
            {
                overlay->writeScript(hFile);
            }
            hFile << std::endl;
        }
    }

    void Sheet::writeScriptFooter(std::ostream& hFile, const int pageNum) const
    {
        if (customScriptEnd.has_value())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script III" << std::endl << std::endl;
            hFile << customScriptEnd.value() << std::endl;
            hFile << std::endl;
        }

        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# tidy up code" << std::endl << std::endl;

        if (type == SheetType::Sheet)
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# dummy plot for empty page" << std::endl << std::endl;

            hFile << "plot [][] 1/0 t\"\"" << std::endl;
        }
        else
        {
            hFile << "set key default" << std::endl;
        }

        hFile << "unset label" << std::endl;
        hFile << "unset arrow" << std::endl;
        hFile << "unset object" << std::endl;
        hFile << std::endl;
    }

    // ====================================================================== //
}
