#ifndef MULTIPLOT_H
#define MULTIPLOT_H

#include <optional>
#include <set>
#include <string>

#include "../definitions/types.h"
#include "../sheets/sheet.h"

namespace Plotypus
{
    //! @todo add convenience non-uniform grid creators aka arrangeX
    //! @todo lock adding overlays (as positioning cannot be distinguished from in-frame); maybe add boolean 'locked' to OverlaysCollection

    class Multiplot : public Sheet, public SheetsCollection
    {
        protected:
            static constexpr std::initializer_list<SheetType> allowedSheetTypes = {SheetType::Sheet,
                                                                                   SheetType::PlotDefault,
                                                                                   SheetType::PlotRadial
                                                                                  };

            // note: optional string 'title' present from Sheet

            std::optional<MultiplotLayout_t>    layout;
            std::set<size_t>                    blanks; // triggers "set multiplot next"

            std::optional<std::string>          options;

            std::string                         frameSeparatorTxt   = "--------------------------------------------------------------------------------\n";

        public:
            Multiplot();
            Multiplot(const std::string& title);

            Multiplot&              reset();

            MultiplotLayout_t       getLayout() const;
            Multiplot&              setLayout(const MultiplotLayout_t& newLayout);
            Multiplot&              clearLayout();

            const std::set<size_t>& getBlanks() const;
            Multiplot&              setBlanks(const std::set<size_t>& newBlanks);

            GridPosition_t          getGridDimensions() const;
            Multiplot&              setGridDimensions(const GridPosition_t& newGridDimensions);

            StackingOrder           getStackingOrder() const;
            Multiplot&              setStackingOrder(const StackingOrder newStackingOrder);

            StackingDirection       getStackingDirection() const;
            Multiplot&              setStackingDirection(const StackingDirection newStackingDirection);

            Margins_t               getMargins() const;
            Multiplot&              setMargins(const Margins_t& newMargins);
            Multiplot&              clearMargins();

            MultiplotSpacing_t      getSpacing() const;
            Multiplot&              setSpacing(const MultiplotSpacing_t& newSpacing);
            Multiplot&              clearSpacing();

            std::string             getOptions() const;
            Multiplot&              setOptions(const std::string& newOptions);
            Multiplot&              clearOptions();

            const std::string&      getFrameSeparatorTxt() const;
            void                    setFrameSeparatorTxt(const std::string& newFrameSeparatorTxt);

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoFilenameBase, const std::string& extension) const;

            virtual void writeTxtHead       (std::ostream& hFile) const;
            virtual void writeTxtData       (std::ostream& hFile) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesCollection) const;
            virtual void writeScriptFooter  (std::ostream& hFile, const int pageNum) const;
    };
}

#endif // MULTIPLOT_H
