#ifndef SHEETSCOLLECTION_H
#define SHEETSCOLLECTION_H

#include <vector>

namespace Plotypus
{
    class PlotOrthogonalAxes;
    class Sheet;

    class SheetsCollection
    {
        protected:
            std::vector<Plotypus::Sheet*> sheets;
            const std::vector<SheetType>  forbiddenSheetTypes;

            Plotypus::Sheet& addSheet (Plotypus::Sheet* newSheet);

        public:
            SheetsCollection(const std::vector<SheetType>& forbiddenSheetTypes);
            ~SheetsCollection();

            SheetsCollection& reset();

            size_t getSheetCount() const;

            Plotypus::Sheet& sheet(const size_t i);

            template<SheetLike T>
            T& sheetAs(const size_t i);

            Plotypus::Sheet& addSheet ();
            Plotypus::Sheet& addSheet (const std::string& title);

            Plotypus::PlotOrthogonalAxes& addPlotOrthogonalAxes();
            Plotypus::PlotOrthogonalAxes& addPlotOrthogonalAxes(const std::string& title = "");

            //! @todo cast and properly deallocate sheets by const SheetType type;
            SheetsCollection& clearSheets();
    };
}

#include "sheetscollection.txx"
#endif // SHEETSCOLLECTION_H
