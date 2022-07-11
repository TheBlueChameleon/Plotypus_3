#ifndef DATAVIEW2D_H
#define DATAVIEW2D_H

#include <span>
#include <string>
#include <vector>

#include "../definitions/types.h"

#include "dataview.h"

namespace Plotypus
{
    template<class T>
    class DataView2D : public DataView
    {
        protected:
            // data view
            std::span<const T>  data;
            DataSelector<T>     selector;

            // function view
            std::string         func;

            // both
            int lineStyle;

        public:
            DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            virtual void reset();

            const std::span<const T>&   getData() const;
            void                        setData(const std::span<const T>& newData);

            const DataSelector<T>&      getSelector() const;
            void                        setSelector(const DataSelector<T>& newSelector);

            const std::string&          getFunc() const;
            void                        setFunc(const std::string& newFunc);

            int                         getLineStyle() const;
            void                        setLineStyle(int newLineStyle);
    };

}

#include "dataview2d.txx"
#endif // DATAVIEW2D_H
