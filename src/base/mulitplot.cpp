#include "mulitplot.h"

namespace Plotypus
{
    MulitPlot::MulitPlot(const std::string& title) :
        Sheet(SheetType::Multiplot, title), SheetsCollection(allowedSheetTypes)
    {}

    // ====================================================================== //

    MulitPlot& MulitPlot::reset()
    {
        Sheet::reset();

        layout.reset();
        blanks.clear();
        options.reset();

        frameSeparatorTxt = "--------------------------------------------------------------------------------\n";

        return *this;
    }

    MultiplotLayout_t MulitPlot::getLayout() const
    {
        return layout.value_or(DEFAULT_MULTIPLOT_LAYOUT);
    }

    MulitPlot& MulitPlot::setLayout(const MultiplotLayout_t& newLayout)
    {
        layout = newLayout;
        return *this;
    }

    MulitPlot& MulitPlot::clearLayout()
    {
        layout.reset();
        return *this;
    }

    GridPosition_t MulitPlot::getGridDimensions() const
    {
        if (layout.has_value())
        {
            return layout->gridDimensions;
        }
        else
        {
            return DEFAULT_GRID_POSITION;
        }
    }

    MulitPlot& MulitPlot::setGridDimensions(const GridPosition_t& newGridDimensions)
    {
        if (layout.has_value())
        {
            layout->gridDimensions = newGridDimensions;
        }
        else
        {
            layout = {newGridDimensions};
        }

        return *this;
    }

    StackingOrder MulitPlot::getStackingOrder() const
    {
        if (layout.has_value())
        {
            return layout->stackingOrder;
        }
        else
        {
            return StackingOrder::Default;
        }
    }

    MulitPlot& MulitPlot::setStackingOrder(const StackingOrder newStackingOrder)
    {
        if (layout.has_value())
        {
            layout->stackingOrder = newStackingOrder;
        }
        else
        {
            layout = {DEFAULT_GRID_POSITION};
            layout->stackingOrder = newStackingOrder;
        }

        return *this;
    }

    StackingDirection MulitPlot::getStackingDirection() const
    {
        if (layout.has_value())
        {
            return layout->stackingDirection;
        }
        else
        {
            return StackingDirection::Default;
        }
    }

    MulitPlot& MulitPlot::setStackingDirection(const StackingDirection newStackingDirection)
    {
        if (layout.has_value())
        {
            layout->stackingDirection = newStackingDirection;
        }
        else
        {
            layout = {DEFAULT_GRID_POSITION};
            layout->stackingDirection = newStackingDirection;
        }

        return *this;
    }

    Margins_t MulitPlot::getMargins() const
    {
        if (layout.has_value())
        {
            return layout->margins.value_or(DEFAULT_MARGIN_SIZE);
        }
        else
        {
            return DEFAULT_MARGIN_SIZE;
        }
    }

    MulitPlot& MulitPlot::setMargins(const Margins_t& newMargins)
    {
        if (layout.has_value())
        {
            layout->margins = newMargins;
        }
        else
        {
            layout = {DEFAULT_GRID_POSITION};
            layout->margins = newMargins;
        }

        return *this;
    }

    MulitPlot& MulitPlot::clearMargins()
    {
        if (layout.has_value())
        {
            layout->margins.reset();
        }

        return *this;
    }

    MultiplotSpacing_t MulitPlot::getSpacing() const
    {
        if (layout.has_value())
        {
            return layout->spacing.value_or(DEFAULT_MULTIPLOT_SPACING);
        }
        else
        {
            return DEFAULT_MULTIPLOT_SPACING;
        }
    }

    MulitPlot& MulitPlot::setSpacing(const MultiplotSpacing_t& newSpacing)
    {
        if (layout.has_value())
        {
            layout->spacing = newSpacing;
        }
        else
        {
            layout = {DEFAULT_GRID_POSITION};
            layout->spacing = newSpacing;
        }

        return *this;
    }

    MulitPlot& MulitPlot::clearSpacing()
    {
        if (layout.has_value())
        {
            layout->spacing.reset();
        }

        return *this;
    }

    std::string MulitPlot::getOptions() const
    {
        return options.value_or("");
    }

    MulitPlot& MulitPlot::setOptions(const std::string& newOptions)
    {
        options = newOptions;
        return *this;
    }

    MulitPlot& MulitPlot::clearOptions()
    {
        options.reset();
        return *this;
    }

    const std::string& MulitPlot::getFrameSeparatorTxt() const
    {
        return frameSeparatorTxt;
    }

    void MulitPlot::setFrameSeparatorTxt(const std::string& newFrameSeparatorTxt)
    {
        frameSeparatorTxt = newFrameSeparatorTxt;
    }

    // ====================================================================== //
    // writers

    void MulitPlot::preprocessSheet(const std::string& autoFilenameBase, const std::string& extension) const
    {
        for (size_t i = 1u; auto sheet : sheets)
        {
            const std::string autoOutputFilename = autoFilenameBase + "_" + std::to_string(i);
            sheet->preprocessSheet(autoOutputFilename, extension);
            ++i;
        }
    }

    void MulitPlot::writeTxtHead(std::ostream& hFile) const
    {
        Sheet::writeTxtHead(hFile);

        hFile << "page contents:" << std::endl;
        for (const auto& sheet : sheets)
        {
            hFile << " * " << sheet->getTitle() << std::endl;
        }
        hFile << std::endl;
    }

    void MulitPlot::writeTxtData(std::ostream& hFile) const
    {
        Sheet::writeTxtData(hFile);

        for (auto sheet : sheets)
        {
            hFile << frameSeparatorTxt;

            sheet->writeTxtHead  (hFile);
            sheet->writeTxtData  (hFile);
            sheet->writeTxtOverlays(hFile);
        }
    }

    void MulitPlot::writeDatData() const
    {
        for (auto sheet : sheets)
        {
            sheet->writeDatData();
        }
    }

    void MulitPlot::writeScriptHead(std::ostream& hFile) const
    {
        // explicitly no call to parent due to different handling of title

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

        hFile << "set title \"\"" << std::endl;
        hFile << "set multiplot";
        // title, titleFont aka font

        if (title.has_value())
        {
            hFile << " title " << std::quoted("{/" + titleFont.value_or("") + " " + title.value() + "}");
        }

        if (layout.has_value())
        {
            const auto& layoutData = layout.value();

            hFile << " layout " << layoutData.gridDimensions.first << ", " << layoutData.gridDimensions.second;
        }

        hFile << optionalStringArgument("", options);

        hFile << std::endl;
    }

    void MulitPlot::writeScriptData(std::ostream& hFile, const StylesCollection& stylesCollection) const
    {
        Sheet::writeScriptData(hFile, stylesCollection);

        for (size_t i = 1u; auto sheet : sheets)
        {
            hFile << "# " << std::string(76, '=') << " #\n";
            hFile << "# subplot " << i << std::endl << std::endl;

            // maybe: move writeCleanSheetCommands to util?
//            if (needCleanSheetCommands && sheet->getType() == SheetType::Sheet) {needCleanSheetCommands = false; writeCleanSheetCommands(hFile);}
//            else if                      (sheet->getType() != SheetType::Sheet) {needCleanSheetCommands = true ;}

            sheet->writeScriptHead      (hFile);
            sheet->writeScriptOverlays  (hFile);
            sheet->writeScriptData      (hFile, stylesCollection);
            sheet->writeScriptFooter    (hFile, i);
            ++i;
        }
    }

    void MulitPlot::writeScriptFooter(std::ostream& hFile, const int pageNum) const
    {
        // explicityl call parent at END of method

        hFile << "unset multiplot" << std::endl;

        Sheet::writeScriptFooter(hFile, pageNum);
    }
}
