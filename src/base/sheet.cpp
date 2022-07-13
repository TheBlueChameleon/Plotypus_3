#include <cmath>
#include <iostream>

#include "localMacros.h"
#include "sheet.h"

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

        labels   .clear();
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

    size_t Sheet::getLabelCount() const
    {
        return labels.size();
    }

    // ====================================================================== //

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
        CHECK_INDEX(i, labels, "label index");
        return labels[i];
    }

    size_t Sheet::addLabel(const Label& newLabel)
    {
        labels.push_back(newLabel);
        return labels.size() - 1;
    }

    size_t Sheet::addLabel(const std::string& text, double x, double y, bool boxed, int boxStyleID)
    {
        Label l;     // use the default values, in case options and/or boxStyle are empty.

        l.text        = text;
        l.coordinates = std::make_pair(x, y);
        l.boxed       = boxed;
        l.boxStyleID  = boxStyleID;

        return addLabel(l);
    }

    // ====================================================================== //

    void Sheet::writeTxtHead(std::ostream& hFile) const
    {
        if (title.size())
        {
            hFile << title << std::endl;
            hFile << std::string(title.size(), '~') << std::endl;
        }
    }

    void Sheet::writeTxtData(std::ostream& hFile) const
    {

    }

    void Sheet::writeTxtLabels(std::ostream& hFile) const
    {
        for (const auto& label : labels)
        {
            hFile << label.text << std::endl;
        }
    }

    void Sheet::writeTxtFooter(std::ostream& hFile, int pageNum) const
    {
        const int lineWidth = 80;
        const int spaces = pageNum ?
                           lineWidth - (std::log10(pageNum) + 1) :
                           lineWidth - 1;
        hFile << std::string(spaces, ' ') << std::to_string(pageNum) << std::endl;
    }

    void Sheet::writeScriptHead(std::ostream& hFile) const
    {
        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# generated setup script" << std::endl << std::endl;

        hFile << "set font \"" << defaultFont << "\"" << std::endl;
        hFile << "set title \"" << title << "\"" << std::endl;
        hFile << std::endl;

        if (customScriptBegin.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script I" << std::endl << std::endl;
            hFile << customScriptBegin << std::endl;
            hFile << std::endl;
        }
    }

    void Sheet::writeScriptData(std::ostream& hFile) const {}

    void Sheet::writeScriptLabels(std::ostream& hFile) const
    {
        if (labels.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# labels" << std::endl << std::endl;

            for (auto& label : labels)
            {
                /* cf. gnuplot 5.4 documentation, p. 164
                 *
                 * set label {<tag>} {"<label text>"} {at <position>}
                 *           {left | center | right}
                 *           {norotate | rotate {by <degrees>}}
                 *           {font "<name>{,<size>}"}
                 *           {noenhanced}
                 *           {front | back}
                 *           {textcolor <colorspec>}
                 *           {point <pointstyle> | nopoint}
                 *           {offset <offset>}
                 *           {nobox} {boxed {bs <boxstyle>}}
                 *           {hypertext}
                 */

                hFile << "set label ";
                hFile << (label.ID               ? std::to_string(label.ID) + " "                     : ""s);
                hFile << "\"" << label.text << "\" ";
                hFile << "at ";
                hFile << (label.screenCS         ? "screen "                                          : "") ;
                hFile <<  label.coordinates.first << ", " << label.coordinates.second << " ";
                hFile << (label.alignment.size() ? label.alignment + " "                              : ""s);
                hFile << (label.rotate           ? "rotate by "s + std::to_string(label.rotate) + " " : "");
                hFile << (label.font.size()      ? "font \""s + label.font + "\" "                    : ""s);
                hFile << "front ";
                hFile << (label.textcolor.size() ? "textcolor \""s + label.textcolor+ "\" "           : ""s);
                if (label.boxed)
                {
                    hFile << "boxed ";
                    hFile << (label.boxStyleID     ? "bs "s + std::to_string(label.boxStyleID) + " "  : "");
                }
                hFile << label.options;
                hFile << std::endl;
            }
            hFile << std::endl;
        }
    }

    void Sheet::writeScriptFooter(std::ostream& hFile, int pageNum) const
    {
        if (customScriptEnd.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script II" << std::endl << std::endl;
            hFile << customScriptEnd << std::endl;
            hFile << std::endl;
        }

        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# dummy plot for empty page" << std::endl << std::endl;

        hFile << "plot [][] 1/0 t\"\"" << std::endl;
        hFile << "unset label" << std::endl;
        hFile << std::endl;
    }

    // ====================================================================== //
}
