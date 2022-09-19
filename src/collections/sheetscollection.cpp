#include "sheetscollection.h"
#include "../base/mulitplot.h"

using namespace Plotypus;
namespace Plotypus
{
    SheetsCollection::SheetsCollection(const std::vector<SheetType>& allowedSheetTypes, bool adjustDefaultFontSize) :
        allowedSheetTypes(allowedSheetTypes), adjustDefaultFontSize(adjustDefaultFontSize)
    {}

    SheetsCollection::~SheetsCollection()
    {
        clearSheets();
    }

    Sheet* SheetsCollection::addSheet(Sheet* newSheet)
    {
        auto sheetType = newSheet->getType();
        if (contains(sheetType, allowedSheetTypes))
        {
            sheets.push_back(newSheet);
        }
        else
        {
            clearSheet(newSheet);
            throw UnsupportedOperationError("Cannot add Sheet of type " + getSheetTypeName(sheetType));
        }

        if (adjustDefaultFontSize)
        {
            newSheet->setTitleFont(alternativeHeadFont);
        }

        return sheets.back();
    }

    void SheetsCollection::clearSheet(Sheet* sheet)
    {
        switch (sheet->getType())
        {
            case SheetType::Sheet:
                delete dynamic_cast<Sheet*>(sheet);
                break;

            case SheetType::PlotOrthogonalAxis:
                delete dynamic_cast<PlotDefault*>(sheet);
                break;

            case SheetType::PlotRadialAxes:
                delete dynamic_cast<PlotRadial*>(sheet);
                break;

            case SheetType::Multiplot:
                delete dynamic_cast<MulitPlot*>(sheet);
                break;
        }
    }

    // ====================================================================== //

    SheetsCollection& SheetsCollection::reset()
    {
        return clearSheets();

        alternativeHeadFont = "Arial:bold*1.3";
    }

    SheetsCollection& SheetsCollection::clearSheets()
    {
        for (auto sheet : sheets)
        {
            clearSheet(sheet);
        }
        sheets.clear();

        return *this;
    }

    const std::string& SheetsCollection::getAlternativeHeadFont() const
    {
        return alternativeHeadFont;
    }

    SheetsCollection& SheetsCollection::setAlternativeHeadFont(const std::string& newAlternativeHeadFont)
    {
        alternativeHeadFont = newAlternativeHeadFont;
        return *this;
    }

    size_t SheetsCollection::getSheetCount() const
    {
        return sheets.size();
    }

    const std::vector<Plotypus::Sheet*>& SheetsCollection::getSheets() const
    {
        return sheets;
    }

    const std::vector<SheetType>& SheetsCollection::getAllowedSheetTypes() const
    {
        return allowedSheetTypes;
    }

    Sheet& SheetsCollection::sheet(const size_t i)
    {
        throwIfInvalidIndex("sheet index", i, sheets);
        return *(sheets[i]);
    }

    Sheet& SheetsCollection::addSheet()
    {
        return *addSheet(new Sheet(SheetType::Sheet));
    }

    Sheet& SheetsCollection::addSheet(const std::string& title)
    {
        return *addSheet(new Sheet(SheetType::Sheet, title) );
    }

    MulitPlot& SheetsCollection::addMultiPlot()
    {
        return *dynamic_cast<MulitPlot*>(addSheet(new MulitPlot));
    }

    MulitPlot& SheetsCollection::addMultiPlot(const std::string& title)
    {
        return *dynamic_cast<MulitPlot*>(addSheet(new MulitPlot(title)));
    }

    PlotDefault& SheetsCollection::addPlotDefault()
    {
        return *dynamic_cast<PlotDefault*>(addSheet( new PlotDefault ));
    }

    PlotDefault& SheetsCollection::addPlotDefault(const std::string& title)
    {
        return *dynamic_cast<PlotDefault*>(addSheet( new PlotDefault(title) ));
    }
}
