#ifndef KEYDESCRIPTOR_H
#define KEYDESCRIPTOR_H

#include <optional>
#include <variant>

namespace Plotypus
{
    class KeyDescriptor
    {
        private:
            enum class AbstractAlignment {Minimal, Central, Maximal};

            using explicitPosition_t = std::pair<bool, OverlayPosition_t>;
            using marginPosition_t   = std::pair<MarginAlignment, AbstractAlignment>;
            using insidePosition_t   = std::pair<HorizontalAlignment, VerticalAlignment>;

            using keyPosition_t = std::variant<explicitPosition_t, marginPosition_t, insidePosition_t>;

        private:
            bool on;

            std::optional<keyPosition_t>        position;
            std::optional<StackingOrder>        stackOrder;
            std::optional<HorizontalAlignment>  justification;

            bool                                opaque = true;
            bool                                boxed;

            bool                                inverseOrder;
            bool                                reverseSymbol;

            std::optional<std::string>          title;

            std::optional<size_t>               lineStyle;
            std::optional<size_t>               maxGroupSize;

        public:
            KeyDescriptor();


            // void write(std::ostream& hFile);
    };
}

#endif // KEYDESCRIPTOR_H
