#include "styles.h"
#include "constants.h"

namespace Plotypus
{
    PointStyle::PointStyle(
        const PointForm                     form,
        const std::string&                  customSymbol,
        const std::string&                  color,
        const double                        size,
        const std::optional<std::string>&   options
    ) :
        form(form), customSymbol(customSymbol), color(color), size(size), options(options)
    {}

    PointStyle::PointStyle(
        const PointForm                     form,
        const std::optional<std::string>&   color,
        const std::optional<double>&        size
    ) :
        form(form), color(color), size(size)
    {}

    PointStyle::PointStyle(
        const std::string&                  customSymbol,
        const std::optional<std::string>&   color,
        const std::optional<double>&        size
    ) :
        form(PointForm::Custom), customSymbol(customSymbol), color(color), size(size)
    {}

    // ---------------------------------------------------------------------- //

    PointForm PointStyle::getForm() const
    {
        return form;
    }

    PointStyle&  PointStyle::setForm(PointForm newForm)
    {
        form = newForm;
        return *this;
    }

    std::optional<std::string> PointStyle::getCustomSymbol() const
    {
        return customSymbol;
    }

    PointStyle& PointStyle::setCustomSymbol(const std::string& newCustomSymbol)
    {
        form = PointForm::Custom;
        customSymbol = newCustomSymbol;
        return *this;
    }

    PointStyle& PointStyle::clearCustomSymbol()
    {
        form = PointForm::None;
        customSymbol.reset();
        return *this;
    }

    std::optional<std::string> PointStyle::getColor() const
    {
        return color;
    }

    PointStyle& PointStyle::setColor(const std::string& newColor)
    {
        color = newColor;
        return *this;
    }

    PointStyle& PointStyle::clearColor()
    {
        color.reset();
        return *this;
    }

    std::optional<double> PointStyle::getSize() const
    {
        return size;
    }

    PointStyle& PointStyle::setSize(const double newSize)
    {
        size = newSize;
        return *this;
    }

    PointStyle& PointStyle::clearSize()
    {
        size.reset();
        return *this;
    }

    std::optional<std::string> PointStyle::getOptions() const
    {
        return options;
    }

    PointStyle& PointStyle::setOptions(const std::string& newOptions)
    {
        options = newOptions;
        return *this;
    }

    PointStyle& PointStyle::clearOptions()
    {
        options.reset();
        return *this;
    }

// ========================================================================== //
}
