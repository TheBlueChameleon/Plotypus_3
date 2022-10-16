#ifndef PALETTEDESCRIPTOR_H
#define PALETTEDESCRIPTOR_H

#include <optional>
#include <variant>
#include <vector>

#include "../definitions/types.h"

namespace Plotypus
{
    /**
     * @todo tidy up code: restore default palette
     */
    class PaletteDescriptor
    {
        public:
            using predefinedMapping_t = std::array<size_t, 3>;
            using customMapping_t     = std::array<std::string, 3>;
            using cubeHelixMapping_t  = std::array<std::optional<double>, 3>;

            using gradientElement_t   = std::pair<double, std::string>;
            using gradientElementList_t = std::vector<gradientElement_t>;

            using fileSpec_t = std::pair<std::string, std::optional<std::string>>;

            enum PaletteVariantIndices
            {
                PredefinedMapping,
                CustomMapping,
                CubeHelixMapping,
                GradientElementList,
                FileSpec
            };

            using paletteData_t = std::variant<predefinedMapping_t, customMapping_t, cubeHelixMapping_t, gradientElementList_t, fileSpec_t>;
            static const paletteData_t EMPTY_PALETTE_DATA;

        private:
            std::optional<paletteData_t>            mapping;
            std::optional<ColorSpace>               colorSpace;
            std::optional<std::string>              options;

            void writePredefinedMapping (std::ostream& hFile) const;
            void writeCustomMapping     (std::ostream& hFile) const;
            void writeCubeHelixMapping  (std::ostream& hFile) const;
            void writeGradientMapping   (std::ostream& hFile) const;
            void writeFileSpecMapping   (std::ostream& hFile) const;

        public:
            PaletteDescriptor() = default;

            PaletteDescriptor&                      reset();

            const paletteData_t                     getMapping() const;
            PaletteDescriptor&                      setMapping(const NamedPalette               newMapping);
            PaletteDescriptor&                      setMapping(const predefinedMapping_t&       newMapping);
            PaletteDescriptor&                      setMapping(const customMapping_t&           newMapping);
            PaletteDescriptor&                      setMapping(const cubeHelixMapping_t&        newMapping);
            PaletteDescriptor&                      setMapping(const gradientElementList_t&     newMapping);
            PaletteDescriptor&                      setMapping(const std::vector<std::string>&  newMapping);
            PaletteDescriptor&                      setMapping(const std::string& filename, const std::optional<std::string>& modifiers = std::optional<std::string>());
            PaletteDescriptor&                      clearMapping();

            ColorSpace                              getColorSpace() const;
            PaletteDescriptor&                      setColorSpace(const ColorSpace newColorSpace);
            PaletteDescriptor&                      clearColorSpace();

            std::string                             getOptions() const;
            PaletteDescriptor&                      setOptions(const std::string& newOptions);
            PaletteDescriptor&                      clearOptions();

            void writePaletteDescriptor(std::ostream& hFile) const;
            //! @todo implement
            void writeUnsetCommands (std::ostream& hFile) const;
    };
}

#endif // PALETTEDESCRIPTOR_H
