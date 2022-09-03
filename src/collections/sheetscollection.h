#ifndef SHEETSCOLLECTION_H
#define SHEETSCOLLECTION_H

#include <vector>

namespace Plotypus
{
    class PlotOrthogonalAxes;
    class Sheet;

    //! @todo copy sheet funcs
    class SheetsCollection
    {
        protected:
            std::vector<Plotypus::Sheet*> sheets;
            const std::vector<SheetType>  allowedSheetTypes;

            Plotypus::Sheet& addSheet (Plotypus::Sheet* newSheet);
            static void clearSheet(Sheet* sheet);

        public:
            SheetsCollection(const std::vector<SheetType>& allowedSheetTypes);
            ~SheetsCollection();

            SheetsCollection& reset();
            SheetsCollection& clearSheets();

            size_t getSheetCount() const;

            const std::vector<Plotypus::Sheet*>&    getSheets() const;
            const std::vector<SheetType>&           getAllowedSheetTypes() const;

            Plotypus::Sheet& sheet(const size_t i);
            template<SheetLike T>
            T& sheetAs(const size_t i);

            Plotypus::Sheet& addSheet ();
            Plotypus::Sheet& addSheet (const std::string& title);

            Plotypus::PlotOrthogonalAxes& addPlotOrthogonalAxes();
            Plotypus::PlotOrthogonalAxes& addPlotOrthogonalAxes(const std::string& title = "");
    };
}

#include "sheetscollection.txx"
#endif // SHEETSCOLLECTION_H
