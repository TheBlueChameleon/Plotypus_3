#ifndef DATAVIEW2D_H
#define DATAVIEW2D_H

#include <concepts>
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
            std::span<const double> dataX;
            std::span<const T>      dataY;
            DataSelector<T>         selector;

            // function view
            std::string             func;

            // both
            int lineStyle = -1;

        public:
            DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            virtual void reset();

            const std::span<const double>&  getDataX() const;
            void                            setDataX(const std::span<const double>& newData);
            void                            setDataX(const double* newData, size_t N);

            const std::span<const T>&       getDataY() const;
            void                            setDataY(const std::span<const T>& newData);
            void                            setDataY(const T* newData, size_t N);

            const DataSelector<T>&          getSelector() const;
            void                            setSelector(const DataSelector<T>& newSelector);

            const std::string&              getFunc() const;
            void                            setFunc(const std::string& newFunc);

            int                             getLineStyle() const;
            void                            setLineStyle(int newLineStyle);

            bool complete() const;

            // writers
            virtual void writePdfData   (std::ofstream& hFile) const;
    };
}

#include "dataview2d.txx"
#endif // DATAVIEW2D_H
