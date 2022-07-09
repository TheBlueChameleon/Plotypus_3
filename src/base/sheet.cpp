#include <cmath>
#include <iostream>

#include "localMacros.h"
#include "sheet.h"

namespace Plotypus
{

    Sheet::Sheet(const std::string& title) :
        title(title)
    {}

    Sheet::~Sheet()
    {
//        std::cout << "DTor Sheet at " << this << std::endl;
    }

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

        boxStyles.clear();
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

    const std::vector<BoxStyle>& Sheet::getBoxStyles() const
    {
        return boxStyles;
    }

    BoxStyle& Sheet::getBoxStyle(int i)
    {
        CHECK_INDEX_EXT(i, boxStyles, "box style index")
        return boxStyles[i];
    }

    void Sheet::setBoxStyles(const std::vector<BoxStyle>& newBoxstyles)
    {
        boxStyles = newBoxstyles;
    }

    void Sheet::addBoxstyle(const BoxStyle& newBoxstyle)
    {
        boxStyles.push_back(newBoxstyle);
    }

    void Sheet::addBoxstyle(const std::string& fillcolor, bool border, const std::string& bordercolor, int ID)
    {
        addBoxstyle(
        {
            (ID < 0 ? static_cast<signed>(boxStyles.size()) : ID),  // ID
            true,                                                   // opaque
            fillcolor,
            border,
            bordercolor
        });
    }

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
        hFile << "set term pdfcairo font \"" << defaultFont << "\"" << std::endl;
        hFile << std::endl;
    }

    void Sheet::writePdfData(std::ofstream& hFile)
    {

    }

    void Sheet::writePdfLabels(std::ofstream& hFile)
    {

    }

    void Sheet::writePdfFooter(std::ofstream &hFile, int pageNum)
    {

    }

    // ====================================================================== //

}
