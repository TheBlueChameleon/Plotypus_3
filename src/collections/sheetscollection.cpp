#include "sheetscollection.h"

using namespace Plotypus;
namespace Plotypus
{
    SheetsCollection::SheetsCollection(const std::vector<SheetType>& forbiddenSheetTypes) :
        forbiddenSheetTypes(forbiddenSheetTypes)
    {}

    SheetsCollection::~SheetsCollection()
    {
        clearSheets();
    }

    Sheet& SheetsCollection::addSheet(Sheet* newSheet)
    {
        auto sheetType = newSheet->getType();
        if (contains(sheetType, forbiddenSheetTypes))
        {
            delete newSheet;
            throw UnsupportedOperationError("Cannot add Sheet of type " + getSheetTypeName(sheetType));
        }

        sheets.push_back(newSheet);
        return *sheets.back();
    }

    // ====================================================================== //

    SheetsCollection& SheetsCollection::reset()
    {
        sheets.clear();
        return *this;
    }

    size_t SheetsCollection::getSheetCount() const
    {
        return sheets.size();
    }

    Sheet& SheetsCollection::sheet(const size_t i)
    {
        throwIfInvalidIndex("sheet index", i, sheets);
        return *(sheets[i]);
    }

    Sheet& SheetsCollection::addSheet()
    {
        return addSheet(new Sheet());
    }

    Sheet& SheetsCollection::addSheet(const std::string& title)
    {
        return addSheet(new Sheet(title) );
    }

    PlotOrthogonalAxes& SheetsCollection::addPlotOrthogonalAxes()
    {
        return dynamic_cast<PlotOrthogonalAxes&>(addSheet( new PlotOrthogonalAxes() ));
    }

    PlotOrthogonalAxes& SheetsCollection::addPlotOrthogonalAxes(const std::string& title)
    {
        return dynamic_cast<PlotOrthogonalAxes&>(addSheet( new PlotOrthogonalAxes(title) ));
    }

    SheetsCollection& SheetsCollection::clearSheets()
    {
        for (auto ptr : sheets)
        {
            delete ptr;
        }
        sheets.clear();

        return *this;
    }
}
