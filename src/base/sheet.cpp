#include <cmath>
#include <iostream>

#include "localMacros.h"
#include "sheet.h"

namespace Plotypus
{
    Sheet::Sheet(const std::string& title) :
        title(title)
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

    // ====================================================================== //

    const std::vector<Label>& Sheet::getLabels() const
    {
        return labels;
    }

    void Sheet::setLabels(const std::vector<Label>& newLabels)
    {
        labels = newLabels;
    }

    Label& Sheet::getLabel(int i)
    {
        CHECK_INDEX_EXT(i, labels, "label index")
        return labels[i];
    }

    void Sheet::addLabel(const Label& newLabel)
    {
        labels.push_back(newLabel);
    }

    void Sheet::addLabel(const std::string& text, double x, double y, bool boxed, int boxStyleID)
    {
        Label l;     // use the default values, in case options and/or boxStyle are empty.

        l.text        = text;
        l.coordinates = std::make_pair(x, y);
        l.boxed       = boxed;
        l.boxStyleID  = boxStyleID;

        addLabel(l);
    }

    // ====================================================================== //

    void Sheet::writeTxtHead(std::ofstream& hFile)
    {
        if (title.size())
        {
            hFile << title << std::endl;
            hFile << std::string(title.size(), '~') << std::endl;
        }
    }

    void Sheet::writeTxtData(std::ofstream& hFile)
    {

    }

    void Sheet::writeTxtLabels(std::ofstream& hFile)
    {
        for (const auto& label : labels)
        {
            hFile << label.text << std::endl;
        }
    }

    void Sheet::writeTxtFooter(std::ofstream& hFile, int pageNum)
    {
        const int lineWidth = 80;
        const int spaces = pageNum ?
                           lineWidth - (std::log10(pageNum) + 1) :
                           lineWidth - 1;
        hFile << std::string(spaces, ' ') << std::to_string(pageNum) << std::endl;
    }

    void Sheet::writePdfHead(std::ofstream& hFile)
    {
        hFile << "set font \"" << defaultFont << "\"" << std::endl;
        hFile << std::endl;
    }

    void Sheet::writePdfSetup(std::ofstream& hFile)
    {
        if (customScriptBegin.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script" << std::endl << std::endl;
            hFile << customScriptBegin << std::endl;
        }
    }

    void Sheet::writePdfData(std::ofstream& hFile)
    {
        if (customScriptEnd.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# custom setup script" << std::endl << std::endl;
            hFile << customScriptEnd << std::endl;
        }
    }

    void Sheet::writePdfLabels(std::ofstream& hFile)
    {
        /* cf. gnuplot 5.4 documentation, p. 159
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

    void Sheet::writePdfFooter(std::ofstream& hFile, int pageNum)
    {
        hFile << "# " << std::string(76, '-') << " #\n";
        hFile << "# dummy plot for empty page" << std::endl << std::endl;
        hFile << "set title \"" << title << "\"" << std::endl;

        hFile << "set key off" << std::endl;
        hFile << "unset border" << std::endl;
        hFile << "unset xtics" << std::endl;
        hFile << "unset xlabel" << std::endl;
        hFile << "unset ytics" << std::endl;
        hFile << "unset ylabel" << std::endl;

        hFile << "set xrange[0:1]" << std::endl;
        hFile << "set yrange[1:0]" << std::endl;

        hFile << "plot [][-1:1] 1/0 t\"\"" << std::endl;
        hFile << "unset label" << std::endl;
        hFile << std::endl;
    }

    // ====================================================================== //

}
