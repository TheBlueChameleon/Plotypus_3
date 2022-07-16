#ifndef PLOT2D_H
#define PLOT2D_H

#include <fstream>
#include <span>
#include <string>
#include <vector>

#include "../dataview/dataview2dcompound.h"

#include "plot.h"

namespace Plotypus
{
    class Plot2D : public Plot
    {
            /**
             * @todo appy point styles in script
             */

            /**
             * @todo rework as abstract non-template class
             *      dataViews becomes vector<DataView*>
             *      requires DTor which deallocates
             *      requires adders instaintiate via new
             *      requires hidden addDataViewCompound(const DataView2DCompound<T>& dataView) copies data into new'd object
             */

        private:
            std::vector<DataView*> dataViews;

        public:
            Plot2D(const std::string& title);

            virtual void reset();

            const std::vector<DataView*>& getDataViews() const;

            DataView&   dataView(const size_t i);
            template<class T>
            size_t      addDataViewCompound(const DataView2DCompound<T>& dataView);
            template<class T>
            size_t      addDataViewCompound(const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            size_t      addDataViewCompound(const std::span<T>& data, const DataSelector<T>& selectorY, const std::string& label = ""); //! @todo deal with selector
            template<class T>
            size_t      addDataViewCompound(const std::string& func, const std::string& label = "");

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeDatData() const;

            virtual void writeScriptData   (std::ostream& hFile) const;
            virtual void writeScriptFooter (std::ostream& hFile, int pageNum) const;
    };
}

#include "plot2d.txx"
#endif // PLOT2D_H
