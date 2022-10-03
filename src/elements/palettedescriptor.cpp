#include <numeric>

#include "palettedescriptor.h"

namespace Plotypus
{
    const PaletteDescriptor::paletteData_t PaletteDescriptor::EMPTY_PALETTE_DATA = gradientElementList_t();

    // ====================================================================== //

    void PaletteDescriptor::writePredefinedMapping(std::ostream& hFile) const
    {
        const auto& formulae = std::get<PaletteVariantIndices::PredefinedMapping>(mapping.value());
        hFile << " rgbformulae "
              << formulae[0] << ", "
              << formulae[1] << ", "
              << formulae[2];
    }

    void PaletteDescriptor::writeCustomMapping(std::ostream& hFile) const
    {
        const auto& formulae = std::get<PaletteVariantIndices::CustomMapping>(mapping.value());
        hFile << " functions "
              << formulae[0] << ", "
              << formulae[1] << ", "
              << formulae[2];
    }

    void PaletteDescriptor::writeCubeHelixMapping(std::ostream& hFile) const
    {
        const auto& params = std::get<PaletteVariantIndices::CubeHelixMapping>(mapping.value());

        hFile << " cubehelix";

        // *INDENT-OFF*
        if (params[0].has_value()) {hFile << " start "      << params[0].value();}
        if (params[1].has_value()) {hFile << " cycles "     << params[1].value();}
        if (params[2].has_value()) {hFile << " saturation " << params[2].value();}
        // *INDENT-ON*
    }

    void PaletteDescriptor::writeGradientMapping(std::ostream& hFile) const
    {
        const auto& gradient = std::get<PaletteVariantIndices::GradientElementList>(mapping.value());

        hFile << " defined (";

        const auto N = gradient.size();
        for (auto i = 1u; const auto& [grey, color] : gradient)
        {
            hFile << grey << " " << std::quoted(color);

            // *INDENT-OFF*
            if (i < N)  {hFile << ", ";}
            else        {hFile << ")";}
            // *INDENT-ON*
        }
    }

    void PaletteDescriptor::writeFileSpecMapping(std::ostream& hFile) const
    {
        const auto& fileSpec = std::get<PaletteVariantIndices::FileSpec>(mapping.value());

        hFile << " file '" << fileSpec.first;
        hFile << optionalStringArgument("", fileSpec.second);
    }

    // ====================================================================== //

    PaletteDescriptor& PaletteDescriptor::reset()
    {
        mapping = predefinedMapping_t{7,5,15};
        return *this;
    }

    const PaletteDescriptor::paletteData_t PaletteDescriptor::getMapping() const
    {
        return mapping.value_or(EMPTY_PALETTE_DATA);
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const NamedPalette newMapping)
    {
        switch (newMapping)
        {
            case NamedPalette::Gnu_Traditional:
                mapping = predefinedMapping_t{5,7,15};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_Autumn:
                mapping = predefinedMapping_t{3,11,6};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_Ocean:
                mapping = predefinedMapping_t{23,28,3};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_Hot:
                mapping = predefinedMapping_t{21,22,23};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_Brilliant:
                mapping = predefinedMapping_t{30,31,32};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_Rainbow:
                mapping = predefinedMapping_t{33,13,10};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_AFM_Hot:
                mapping = predefinedMapping_t{34,35,36};
                colorSpace = ColorSpace::RGB;
                break;
            case NamedPalette::Gnu_Colorwheel:
                mapping = predefinedMapping_t{3,2,2};
                colorSpace = ColorSpace::HSV;
                break;

            case NamedPalette::Plt_Viridis:
                mapping = gradientElementList_t
                {
                    {  0, "#440154"}, {  1, "#460c5f"}, {  2, "#47186a"}, {  3, "#482273"}, {  4, "#472c7b"}, {  5, "#453681"}, {  6, "#424085"}, {  7, "#3e4989"},
                    {  8, "#3a528b"}, {  9, "#365a8c"}, { 10, "#32628d"}, { 11, "#2f6a8d"}, { 12, "#2c728e"}, { 13, "#287a8e"}, { 14, "#26818e"}, { 15, "#23898d"},
                    { 16, "#20908c"}, { 17, "#1e988a"}, { 18, "#1e9f88"}, { 19, "#21a784"}, { 20, "#28ae7f"}, { 21, "#32b57a"}, { 22, "#3ebc73"}, { 23, "#4dc26b"},
                    { 24, "#5ec961"}, { 25, "#70ce56"}, { 26, "#83d34b"}, { 27, "#97d83e"}, { 28, "#addc30"}, { 29, "#c2df22"}, { 30, "#d7e219"}, { 31, "#ece41a"}
                };
                break;
            case NamedPalette::Plt_Plasma:
                mapping = gradientElementList_t
                {
                    {  0, "#0c0786"}, {  1, "#21058f"}, {  2, "#310496"}, {  3, "#3f039c"}, {  4, "#4c02a1"}, {  5, "#5901a4"}, {  6, "#6500a7"}, {  7, "#7200a8"},
                    {  8, "#7e03a7"}, {  9, "#8908a5"}, { 10, "#9511a1"}, { 11, "#9f1a9b"}, { 12, "#a92395"}, { 13, "#b22c8e"}, { 14, "#bb3586"}, { 15, "#c33e7f"},
                    { 16, "#cb4777"}, { 17, "#d25070"}, { 18, "#d95969"}, { 19, "#df6262"}, { 20, "#e56c5b"}, { 21, "#eb7654"}, { 22, "#f0804d"}, { 23, "#f48a47"},
                    { 24, "#f89540"}, { 25, "#faa039"}, { 26, "#fcac32"}, { 27, "#fdb82c"}, { 28, "#fdc427"}, { 29, "#fbd124"}, { 30, "#f8df24"}, { 31, "#f3ec26"}
                };
                break;
            case NamedPalette::Plt_Inferno:
                mapping = gradientElementList_t
                {
                    {  0, "#000003"}, {  1, "#030212"}, {  2, "#0a0723"}, {  3, "#140b36"}, {  4, "#200c4a"}, {  5, "#2e0a5a"}, {  6, "#3c0965"}, {  7, "#4a0b6a"},
                    {  8, "#570f6d"}, {  9, "#63146e"}, { 10, "#70196e"}, { 11, "#7d1d6c"}, { 12, "#892269"}, { 13, "#962666"}, { 14, "#a32b61"}, { 15, "#af315b"},
                    { 16, "#bb3754"}, { 17, "#c73e4c"}, { 18, "#d14643"}, { 19, "#db4f3a"}, { 20, "#e45a31"}, { 21, "#eb6527"}, { 22, "#f1721d"}, { 23, "#f68012"},
                    { 24, "#f98e08"}, { 25, "#fb9d06"}, { 26, "#fbac10"}, { 27, "#fabb21"}, { 28, "#f8cb34"}, { 29, "#f4db4b"}, { 30, "#f1e968"}, { 31, "#f3f689"}
                };
                break;
            case NamedPalette::Plt_Magma:
                mapping = gradientElementList_t
                {
                    {  0, "#000003"}, {  1, "#030311"}, {  2, "#0a0722"}, {  3, "#120d33"}, {  4, "#1c1046"}, {  5, "#281159"}, {  6, "#350f6a"}, {  7, "#430f75"},
                    {  8, "#50127b"}, {  9, "#5d177e"}, { 10, "#691c80"}, { 11, "#762181"}, { 12, "#822581"}, { 13, "#8f2a80"}, { 14, "#9c2e7f"}, { 15, "#a9327c"},
                    { 16, "#b63679"}, { 17, "#c33b74"}, { 18, "#d0416f"}, { 19, "#dc4869"}, { 20, "#e65162"}, { 21, "#ee5d5d"}, { 22, "#f56a5b"}, { 23, "#f9795c"},
                    { 24, "#fb8861"}, { 25, "#fd9768"}, { 26, "#fea671"}, { 27, "#feb57c"}, { 28, "#fec488"}, { 29, "#fdd295"}, { 30, "#fde1a3"}, { 31, "#fcf0b1"}
                };
                break;
            case NamedPalette::Plt_Cividis:
                mapping = gradientElementList_t
                {
                    {  0, "#00224d"}, {  1, "#00285b"}, {  2, "#002d69"}, {  3, "#043270"}, {  4, "#1a386f"}, {  5, "#273d6d"}, {  6, "#31436c"}, {  7, "#3a486b"},
                    {  8, "#434e6b"}, {  9, "#4b546c"}, { 10, "#52596c"}, { 11, "#595f6d"}, { 12, "#61646f"}, { 13, "#686a70"}, { 14, "#6e7073"}, { 15, "#757575"},
                    { 16, "#7c7b78"}, { 17, "#848178"}, { 18, "#8b8778"}, { 19, "#938d77"}, { 20, "#9b9376"}, { 21, "#a39a74"}, { 22, "#aba072"}, { 23, "#b3a66f"},
                    { 24, "#bbad6c"}, { 25, "#c4b468"}, { 26, "#ccbb63"}, { 27, "#d5c25e"}, { 28, "#dec957"}, { 29, "#e6d04f"}, { 30, "#efd846"}, { 31, "#f9df3a"}
                };
                break;

            case NamedPalette::Greys:
                mapping = customMapping_t{"gray**.7", "gray**.7", "gray**.7"};
                break;
        };

        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const predefinedMapping_t& newMapping)
    {
        mapping = newMapping;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const customMapping_t& newMapping)
    {
        mapping = newMapping;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const cubeHelixMapping_t& newMapping)
    {
        mapping = newMapping;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const gradientElementList_t& newMapping)
    {
        mapping = newMapping;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const std::vector<std::string>& newMapping)
    {
        const size_t N = newMapping.size();
        gradientElementList_t fullMapping(N);

        auto enumeration = std::views::iota(1u, N);

        std::transform(newMapping.begin(), newMapping.end(),
                       enumeration.begin(),
                       fullMapping.begin(),
                       [] (const auto& colorName, const auto& pos)
        {
            return gradientElement_t(pos, colorName);
        });

        mapping = fullMapping;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::setMapping(const std::string& filename, const std::optional<std::string>& modifiers)
    {
        mapping = std::make_pair(filename, modifiers);
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::clearMapping()
    {
        mapping.reset();
        return *this;
    }

    ColorSpace PaletteDescriptor::getColorSpace() const
    {
        return colorSpace.value_or(ColorSpace::RGB);
    }

    PaletteDescriptor& PaletteDescriptor::setColorSpace(const ColorSpace newColorSpace)
    {
        colorSpace = newColorSpace;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::clearColorSpace()
    {
        colorSpace.reset();
        return *this;
    }

    std::string PaletteDescriptor::getOptions() const
    {
        return options.value_or("");
    }

    PaletteDescriptor& PaletteDescriptor::setOptions(const std::string& newOptions)
    {
        options = newOptions;
        return *this;
    }

    PaletteDescriptor& PaletteDescriptor::clearOptions()
    {
        options.reset();
        return *this;
    }

    // ====================================================================== //

    void PaletteDescriptor::writePaletteDescriptor(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if (!mapping   .has_value() &&
            !colorSpace.has_value() &&
            !options   .has_value()
        ) {return;}
        // *INDENT-ON*

        hFile << "set palette";

        if (mapping.has_value())
        {
            const auto& paletteValue = mapping.value();
            switch (paletteValue.index())
            {
                case PaletteVariantIndices::PredefinedMapping:
                    writePredefinedMapping (hFile);
                    break;
                case PaletteVariantIndices::CustomMapping:
                    writeCustomMapping     (hFile);
                    break;
                case PaletteVariantIndices::CubeHelixMapping:
                    writeCubeHelixMapping  (hFile);
                    break;
                case PaletteVariantIndices::GradientElementList:
                    writeGradientMapping   (hFile);
                    break;
                case PaletteVariantIndices::FileSpec:
                    writeFileSpecMapping   (hFile);
                    break;
            }
        }

        hFile << optionalEnumArgument<ColorSpace>("model", colorSpace, getColorSpaceName);
        hFile << optionalStringArgument("", options);

        hFile << std::endl;
    }

    void PaletteDescriptor::writeUnsetCommands(std::ostream& hFile) const
    {
        hFile << "set palette" << std::endl;
    }
}
