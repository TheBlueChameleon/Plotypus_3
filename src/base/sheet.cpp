#include "sheet.h"

using namespace std::string_literals;

namespace Plotypus
{
    Sheet::Sheet(const std::string& title) :
        title(title),
        type(SheetType::Sheet)
    {}

    // ====================================================================== //

    SheetType Sheet::getType() const
    {
        return type;
    }

    Sheet& Sheet::reset()
    {
        title = "";
        defaultFont = "arial,7";

        customScriptBegin = "";
        customScriptEnd   = "";

        labels.clear();

        return *this;
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

    size_t Sheet::getLabelCount() const
    {
        return labels.size();
    }

    const std::vector<Label_deprecated>& Sheet::getLabels() const
    {
        return labels;
    }

    Sheet& Sheet::setLabels(const std::vector<Label_deprecated>& newLabels)
    {
        labels = newLabels;
        return *this;
    }

    Label_deprecated& Sheet::label(const size_t i)
    {
        throwIfInvalidIndex("label index", i, labels);
        return labels[i];
    }

    Label_deprecated& Sheet::addLabel(const Label_deprecated& newLabel)
    {
        labels.push_back(newLabel);
        return labels.back();
    }

    Label_deprecated& Sheet::addLabel(const std::string& text, double x, double y, bool boxed, size_t boxStyleID)
    {
        Label_deprecated l;

        l.text        = text;
        l.coordinates = std::make_pair(x, y);
        l.boxed       = boxed;
        l.boxStyleID  = boxStyleID;

        return addLabel(l);
    }

    void Sheet::clearLabels()
    {
        labels.clear();
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

    void Sheet::writeTxtLabels(std::ostream& hFile) const
    {
        for (const auto& label : labels)
        {
            hFile << label.text << std::endl;
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

        if (customScriptInter.has_value())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script II" << std::endl << std::endl;
            hFile << customScriptInter.value() << std::endl;
            hFile << std::endl;
        }
    }

    void Sheet::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
    {
        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# plot commands" << std::endl << std::endl;
    }

    void Sheet::writeScriptLabels(std::ostream& hFile) const
    {
        if (labels.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# labels" << std::endl << std::endl;

            for (auto& label : labels)
            {
                /* cf. gnuplot 5.4 documentation, p. 164 */

                hFile << "set label ";
                hFile << std::quoted(label.text) << " ";
                hFile << "at " << (label.screenCS ? "screen " : "") <<  label.coordinates.first << ", " << label.coordinates.second << " ";
                hFile << "front ";

                hFile << (label.alignment.size() ? label.alignment + " " : ""s);
                hFile << optionalNumberString("rotate by", label.rotate);

                hFile << optionalQuotedTextString("font", label.font);
                hFile << optionalQuotedTextString("textcolor", label.textcolor);
                if (label.boxed)
                {
                    hFile << "boxed " << optionalStyleString("bs", label.boxStyleID);
                }
                hFile << label.options;
                hFile << std::endl;
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

        hFile << "unset label" << std::endl;
        hFile << std::endl;
    }

    // ====================================================================== //
}
