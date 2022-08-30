#ifndef LABEL_H
#define LABEL_H

#include <optional>

#include "../definitions/constants.h"
#include "overlay.h"

namespace Plotypus
{
    class Label : public Overlay
    {
        private:
            std::string                         text = "label";

            std::optional<std::string>          font;
            std::optional<std::string>          textcolor;
            std::optional<HorizontalAlignment>  alignment;

            bool                                boxed = false;
            std::optional<size_t>               boxStyleID;

            std::optional<double>               rotateBy;

        public:
            Label();
            Label(const std::string& text, double x, double y,           bool boxed = false, size_t boxStyleID = OPTIONAL_SIZE_T_DEFAULT);
            Label(const std::string& text, double x, double y, double z, bool boxed = false, size_t boxStyleID = OPTIONAL_SIZE_T_DEFAULT);

            const std::string&      getText() const;
            Label&                  setText(const std::string& newText);

            std::string             getFont() const;
            Label&                  setFont(const std::string& newFont);
            Label&                  clearFont();

            std::string             getTextcolor() const;
            Label&                  setTextcolor(const std::string& newTextcolor);
            Label&                  clearTextColor();

            HorizontalAlignment     getAlignment() const;
            Label&                  setAlignment(const HorizontalAlignment newHorizontalAlignment);
            Label&                  clearAlignment();

            bool                    getBoxed() const;
            Label&                  setBoxed(bool newBoxed);

            size_t                  getBoxStyleID() const;
            Label&                  setBoxStyleID(size_t newBoxStyleID);
            Label&                  clearBoxStyleID();

            double                  getRotateBy() const;
            Label&                  setRotateBy(double newRotateBy);
            Label&                  clearRotate();

            // writers

            virtual void writeTxt   (std::ostream& hFile) const;
            virtual void writeScript(std::ostream& hFile) const;
    };
}

#endif // LABEL_H
