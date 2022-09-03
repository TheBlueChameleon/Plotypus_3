#include "sheetscollection.h"
#include "../base/mulitplot.h"

using namespace Plotypus;
namespace Plotypus
{
    SheetsCollection::SheetsCollection(const std::vector<SheetType>& allowedSheetTypes) :
        allowedSheetTypes(allowedSheetTypes)
    {}

    SheetsCollection::~SheetsCollection()
    {
        clearSheets();
    }

    Sheet& SheetsCollection::addSheet(Sheet* newSheet)
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

        return *sheets.back();
    }

    void SheetsCollection::clearSheet(Sheet* sheet)
    {
        switch (sheet->getType())
        {
            case SheetType::Sheet:
                delete dynamic_cast<Sheet*>(sheet);
                break;

            case SheetType::PlotOrthogonalAxis:
                delete dynamic_cast<PlotOrthogonalAxes*>(sheet);
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
        return addSheet(new Sheet(SheetType::Sheet));
    }

    Sheet& SheetsCollection::addSheet(const std::string& title)
    {
        return addSheet(new Sheet(SheetType::Sheet, title) );
    }

    PlotOrthogonalAxes& SheetsCollection::addPlotOrthogonalAxes()
    {
        return dynamic_cast<PlotOrthogonalAxes&>(addSheet( new PlotOrthogonalAxes() ));
    }

    PlotOrthogonalAxes& SheetsCollection::addPlotOrthogonalAxes(const std::string& title)
    {
        return dynamic_cast<PlotOrthogonalAxes&>(addSheet( new PlotOrthogonalAxes(title) ));
    }
}
