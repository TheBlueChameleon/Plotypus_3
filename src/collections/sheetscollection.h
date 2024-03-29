#ifndef SHEETSCOLLECTION_H
#define SHEETSCOLLECTION_H

#include <string>
#include <vector>

#include "../base/util.h"
#include "../definitions/types.h"
#include "../sheets/plotdefault.h"

namespace Plotypus
{
    enum class SheetType;
    class Multiplot;

    //! @todo copy sheet funcs

    class SheetsCollection
    {
        protected:
            std::vector<Sheet*>             sheets;
            const std::vector<SheetType>    allowedSheetTypes;
            bool                            adjustDefaultFontSize;

            std::string                     alternativeHeadFont = "Arial:bold*1.3";

            Sheet* addSheet (Sheet* newSheet);
            static void clearSheet(Sheet* sheet);

        public:
            SheetsCollection(const std::vector<SheetType>& allowedSheetTypes, bool adjustDefaultFontSize = false);
            ~SheetsCollection();

            SheetsCollection&               reset();
            SheetsCollection&               clearSheets();

            const std::string&              getAlternativeHeadFont() const;
            SheetsCollection&               setAlternativeHeadFont(const std::string& newAlternativeHeadFont);

            size_t                          getSheetCount() const;

            const std::vector<Sheet*>&      getSheets() const;
            const std::vector<SheetType>&   getAllowedSheetTypes() const;

            Sheet& sheet(const size_t i);
            template<SheetLike T>
            T& sheetAs(const size_t i);

            Sheet&          addSheet();
            Sheet&          addSheet(const std::string& title);

            Multiplot&      addMultiplot();
            Multiplot&      addMultiplot(const std::string& title);

            PlotDefault&    addPlotDefault();
            PlotDefault&    addPlotDefault(const std::string& title);
    };
}

#include "sheetscollection.txx"
#endif // SHEETSCOLLECTION_H
