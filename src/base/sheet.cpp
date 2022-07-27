#include <cmath>
#include <iostream>

#include "sheet.h"

using namespace std::string_literals;

namespace Plotypus
{
    Sheet::Sheet(const std::string& title) :
        title(title),
        type(PlotType::Sheet)
    {}

    // ====================================================================== //

    PlotType Sheet::getType() const
    {
        return type;
    }

    void Sheet::reset()
    {
        title = "";
        defaultFont = "arial,7";

        customScriptBegin = "";
        customScriptEnd   = "";

        datalineSeparatorTxt = "................................................................................\n";

        labels.clear();
    }

    const std::string& Sheet::getTitle() const
    {
        return title;
    }

    void Sheet::setTitle(const std::string& newTitle)
    {
        title = newTitle;
    }

    const std::string& Sheet::getDefaultFont() const
    {
        return defaultFont;
    }

    void Sheet::setDefaultFont(const std::string& newDefaultFont)
    {
        defaultFont = newDefaultFont;
    }

    const std::string& Sheet::getTitleFont() const
    {
        return titleFont;
    }

    void Sheet::setTitleFont(const std::string& newTitleFont)
    {
        titleFont = newTitleFont;
    }

    const std::string& Sheet::getCustomScriptBegin() const
    {
        return customScriptBegin;
    }

    void Sheet::setCustomScriptBegin(const std::string& newCustomScriptBegin)
    {
        customScriptBegin = newCustomScriptBegin;
    }

    const std::string& Sheet::getCustomScriptEnd() const
    {
        return customScriptEnd;
    }

    void Sheet::setCustomScriptEnd(const std::string& newCustomScriptEnd)
    {
        customScriptEnd = newCustomScriptEnd;
    }

    const std::string& Sheet::getDatalineSeparatorTxt() const
    {
        return datalineSeparatorTxt;
    }

    void Sheet::setDatalineSeparatorTxt(const std::string& newDatalineSeparatorTxt)
    {
        datalineSeparatorTxt = newDatalineSeparatorTxt;
    }

    // ====================================================================== //

    size_t Sheet::getLabelCount() const
    {
        return labels.size();
    }

    const std::vector<Label>& Sheet::getLabels() const
    {
        return labels;
    }

    void Sheet::setLabels(const std::vector<Label>& newLabels)
    {
        labels = newLabels;
    }

    Label& Sheet::label(const size_t i)
    {
        checkIndex("label index", i, labels);
        return labels[i];
    }

    Label& Sheet::addLabel(const Label& newLabel)
    {
        labels.push_back(newLabel);
        return labels.back();
    }

    Label& Sheet::addLabel(const std::string& text, double x, double y, bool boxed, int boxStyleID)
    {
        Label l;

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
        if (title.size())
        {
            hFile << title << std::endl;
            hFile << std::string(title.size(), '~') << std::endl;
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
        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# generated setup script" << std::endl << std::endl;

        hFile << "set font " << std::quoted(defaultFont) << std::endl;
        hFile << "set title " << std::quoted("{/" + titleFont + " " + title + "}") << std::endl;
        hFile << std::endl;

        if (!customScriptBegin.empty())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script I" << std::endl << std::endl;
            hFile << customScriptBegin << std::endl;
            hFile << std::endl;
        }
    }

    void Sheet::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const {}

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
                hFile << optionalNumber          ("rotate by", label.rotate);

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
        if (!customScriptEnd.empty())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script II" << std::endl << std::endl;
            hFile << customScriptEnd << std::endl;
            hFile << std::endl;
        }

        if (type == PlotType::Sheet)
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
