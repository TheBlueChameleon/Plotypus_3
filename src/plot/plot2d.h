#ifndef PLOT2D_H
#define PLOT2D_H

#include <fstream>
#include <span>
#include <string>
#include <vector>

#include "../dataview/dataview2d.h"

#include "plot.h"

namespace Plotypus
{
    template<class T>
    class Plot2D : public Plot
    {
            /**
             * @todo appy point styles in script
             */

        private:
            std::vector<DataView2D<T>> dataViews;

        public:
            Plot2D(const std::string& title);

            virtual void reset();

            const std::vector<DataView2D<T> >&  getDataViews() const;
            void                                setDataViews(const std::vector<DataView2D<T> >& newDataViews);

            DataView2D<T>&  dataView(const size_t i);
            size_t          addDataView(const DataView2D<T>& dataView);
            size_t          addDataView(                               const std::span<T> dataY, const DataSelector<T>& selector, const std::string& label = "");
            size_t          addDataView(const std::span<double> dataX, const std::span<T> dataY, const DataSelector<T>& selector, const std::string& label = "");
            size_t          addDataView(const std::string& func, const std::string& label = "");


            /** @todo virtual std::vector<std::string> getDatafiles() const;
             *  returns names of all data files as produced by the added data views (empty list by default); null string for funcs */

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeScriptData   (std::ostream& hFile) const;
            virtual void writeScriptFooter (std::ostream& hFile, int pageNum) const;
    };
}

#include "plot2d.txx"
#endif // PLOT2D_H
