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
            std::span<const T> dataX;
            std::span<const T> dataY;
            std::span<const T> dataErrorX;
            std::span<const T> dataErrorY;

            DataSelector<T>    selectorX;
            DataSelector<T>    selectorY;
            DataSelector<T>    selectorErrorX;
            DataSelector<T>    selectorErrorY;

            //! @todo add columns 5+6 for method arrows

            //! @todo using clause

            // function view
            std::string func;

            // both
            int lineStyle  = -1;
            int pointStyle = -1;

            // internal
            void clearFunctionMembers();
            void clearNonFunctionMembers();

        public:
            // TODO: PlotStyle2D CTor
            DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            virtual void reset();

            const std::span<const T>&   getDataX() const;
            void                        setDataX(const std::span<const T>& newData);
            void                        setDataX(const T* newData, size_t N);

            const std::span<const T>&   getDataY() const;
            void                        setDataY(const std::span<const T>& newData);
            void                        setDataY(const T* newData, size_t N);

            const std::span<const T>&   getDataErrorX() const;
            void                        setDataErrorX(const std::span<const T>& newDataErrorX);
            void                        setDataErrorX(const T* newData, size_t N);

            const std::span<const T>&   getDataErrorY() const;
            void                        setDataErrorY(const std::span<const T>& newDataErrorY);
            void                        setDataErrorY(const T* newData, size_t N);

            const DataSelector<T>&      getSelectorX() const;
            void                        setSelectorX(const DataSelector<T>& newSelector);

            const DataSelector<T>&      getSelectorY() const;
            void                        setSelectorY(const DataSelector<T>& newSelector);

            const DataSelector<T>&      getSelectorErrorX() const;
            void                        setSelectorErrorX(const DataSelector<T>& newSelectorErrorX);

            const DataSelector<T>&      getSelectorErrorY() const;
            void                        setSelectorErrorY(const DataSelector<T>& newSelectorErrorY);

            const std::string&          getFunc() const;
            void                        setFunc(const std::string& newFunc);

            int                         getLineStyle() const;
            void                        setLineStyle(int newLineStyle);

            bool isDummy() const;
            bool isComplete() const; // TODO: update

            // writers
            virtual void writeScriptData (std::ostream& hFile) const;
    };
}

#include "dataview2d.txx"
#endif // DATAVIEW2D_H
