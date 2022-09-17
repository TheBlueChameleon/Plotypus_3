#ifndef SHEETSCOLLECTION_H
#define SHEETSCOLLECTION_H

#include <vector>

namespace Plotypus
{
    class PlotDefault;
    class Sheet;
    class MulitPlot;

    //! @todo copy sheet funcs
    //! @todo abstract writers?

    class SheetsCollection
    {
        protected:
            std::vector<Sheet*> sheets;
            const std::vector<SheetType>  allowedSheetTypes;

            Sheet* addSheet (Sheet* newSheet);
            static void clearSheet(Sheet* sheet);

        public:
            SheetsCollection(const std::vector<SheetType>& allowedSheetTypes);
            ~SheetsCollection();

            SheetsCollection& reset();
            SheetsCollection& clearSheets();

            size_t getSheetCount() const;

            const std::vector<Sheet*>&      getSheets() const;
            const std::vector<SheetType>&   getAllowedSheetTypes() const;

            Sheet& sheet(const size_t i);
            template<SheetLike T>
            T& sheetAs(const size_t i);

            Sheet& addSheet ();
            Sheet& addSheet (const std::string& title);

            PlotDefault& addPlotDefault();
            PlotDefault& addPlotDefault(const std::string& title);

            MulitPlot& addMultiPlot(const std::string& title);

            // -------------------------------------------------------------- //
            // writers

            // ???
    };
}

#include "sheetscollection.txx"
#endif // SHEETSCOLLECTION_H
