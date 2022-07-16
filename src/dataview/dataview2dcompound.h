#ifndef DATAVIEW2DCOMPOUND_H
#define DATAVIEW2DCOMPOUND_H

#include "dataview2d.h"

namespace Plotypus
{
    template<class T>
    class DataView2DCompound : public DataView2D<T>
    {
        protected:
            std::span<T>                 data;
            std::vector<DataSelector<T>> selectors;

            virtual void clearNonFunctionMembers();

        public:
            DataView2DCompound(const std::string& label, const PlotStyle2D  style, const std::string& dataColumnFormat = "#");
            DataView2DCompound(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            const std::span<T>&                     getData() const;
            void                                    setData(const std::span<T>& newDataSource);

            const std::vector<DataSelector<T> >&    getSelectors() const;
            void                                    setSelectors(const std::vector<DataSelector<T> >& newSelectors);
    };
}

#include "dataview2dcompound.txx"
#endif // DATAVIEW2DCOMPOUND_H
