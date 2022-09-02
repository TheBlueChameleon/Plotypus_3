#include <string>

#include "plotypus.h"

namespace Plotypus
{
    template PlotOrthogonalAxes& SheetsCollection::sheetAs<PlotOrthogonalAxes>(const size_t index);
    template PlotRadial&         SheetsCollection::sheetAs<PlotRadial>        (const size_t index);

    template Label& Sheet::overlayAs<Label>(const size_t i);

    template bool contains<std::string>     (const std::string&     toFind, const std::vector<std::string>&     container);
    template bool contains<FileType>        (const FileType&        toFind, const std::vector<FileType>&        container);
    template bool contains<SheetType>       (const SheetType&       toFind, const std::vector<SheetType>&       container);
    template bool contains<PlotStyle>       (const PlotStyle&       toFind, const std::vector<PlotStyle>&       container);
    template bool contains<PlotStyleFamily> (const PlotStyleFamily& toFind, const std::vector<PlotStyleFamily>& container);
    template bool contains<Layer>           (const Layer&           toFind, const std::vector<Layer>&           container);

    template void throwIfInvalidIndex<std::vector<Overlay*>>    (const std::string& indexName, const size_t i, const std::vector<Overlay*>&     collection);
    template void throwIfInvalidIndex<std::vector<Sheet*>>      (const std::string& indexName, const size_t i, const std::vector<Sheet*>&       collection);
    template void throwIfInvalidIndex<std::vector<BoxStyle*>>   (const std::string& indexName, const size_t i, const std::vector<BoxStyle*>&    collection);
    template void throwIfInvalidIndex<std::vector<LineStyle*>>  (const std::string& indexName, const size_t i, const std::vector<LineStyle*>&   collection);
    template void throwIfInvalidIndex<std::vector<PointStyle*>> (const std::string& indexName, const size_t i, const std::vector<PointStyle*>&  collection);
}
