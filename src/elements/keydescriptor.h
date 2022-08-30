#ifndef KEYDESCRIPTOR_H
#define KEYDESCRIPTOR_H

#include <optional>
#include <variant>

namespace Plotypus
{
    class KeyDescriptor
    {
        public:
            enum class AbstractAlignment {Default, Minimal, Central, Maximal};

            using explicitPosition_t = std::pair<bool, OverlayPosition_t>;
            using marginPosition_t   = std::pair<MarginAlignment, AbstractAlignment>;
            using insidePosition_t   = std::pair<HorizontalAlignment, VerticalAlignment>;

            using keyPosition_t = std::variant<explicitPosition_t, marginPosition_t, insidePosition_t>;

        private:
            std::optional<keyPosition_t>        position;
            StackingOrder                       stackingOrder = StackingOrder::Default;
            HorizontalAlignment                 justification = HorizontalAlignment::Default;

            bool                                on = true;

            bool                                opaque = true;
            bool                                boxed  = false;

            bool                                inverseOrder  = false;
            bool                                reverseSymbol = false;

            std::optional<std::string>          title;

            std::optional<size_t>               lineStyle;
            std::optional<size_t>               maxGroupSize;

            void writePosition(std::ostream& hFile) const;

        public:
            KeyDescriptor() = default;

            KeyDescriptor&      reset();

            bool                getOn() const;
            KeyDescriptor&      setOn(bool newOn);

            keyPosition_t       getPosition() const;
            KeyDescriptor&      setPosition(const bool fixed, const OverlayPosition_t& coordinates);
            KeyDescriptor&      setPosition(const MarginAlignment marginAlignment, const HorizontalAlignment horizontalAlignment);
            KeyDescriptor&      setPosition(const MarginAlignment marginAlignment, const VerticalAlignment verticalAlignment);
            KeyDescriptor&      setPosition(const HorizontalAlignment horizontalAlignment, const VerticalAlignment verticalAlignment);
            KeyDescriptor&      clearPosition();

            StackingOrder       getStackingOrder() const;
            KeyDescriptor&      setStackingOrder(StackingOrder newStackingOrder);

            HorizontalAlignment getJustification() const;
            KeyDescriptor&      setJustification(const HorizontalAlignment newJustification);

            bool                getOpaque() const;
            KeyDescriptor&      setOpaque(bool newOpaque);

            bool                getBoxed() const;
            KeyDescriptor&      setBoxed(bool newBoxed);

            bool                getInverseOrder() const;
            KeyDescriptor&      setInverseOrder(bool newInverseOrder);

            bool                getReverseSymbol() const;
            KeyDescriptor&      setReverseSymbol(bool newReverseSymbol);

            std::string         getTitle() const;
            KeyDescriptor&      setTitle(const std::string& newTitle);
            KeyDescriptor&      clearTitle();

            size_t              getLineStyle() const;
            KeyDescriptor&      setLineStyle(std::optional<size_t> newLineStyle);
            KeyDescriptor&      clearLineStyle();

            size_t              getMaxGroupSize() const;
            KeyDescriptor&      setMaxGroupSize(std::optional<size_t> newMaxGroupSize);
            KeyDescriptor&      clearMaxGroupSize();

            void writeKeyDescriptor(std::ostream& hFile) const;
    };
}

#endif // KEYDESCRIPTOR_H
