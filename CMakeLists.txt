cmake_minimum_required(VERSION 3.5)

# ============================================================================ #
# lanugage definition

project(Plotypus
    VERSION 3.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# library definition

add_library(Plotypus-lib SHARED
    src/plotypus.h src/plotypus.cpp
    #
    src/definitions/types.h
    src/definitions/styles.h src/definitions/styles.cpp
    src/definitions/errors.h
    src/definitions/constants.h
    src/definitions/internalconstants.h
    #
    src/collections/stylescollection.h src/collections/stylescollection.cpp
    src/collections/sheetscollection.h src/collections/sheetscollection.cpp src/collections/sheetscollection.txx
    src/collections/overlayscollection.h src/collections/overlayscollection.cpp src/collections/overlayscollection.txx
    src/collections/dataviewcollection.h src/collections/dataviewcollection.cpp src/collections/dataviewcollection.txx
    #
    src/base/util.h src/base/util.cpp src/base/util.txx
    src/base/report.h src/base/report.cpp
    src/base/terminalinfoprovider.h src/base/terminalinfoprovider.cpp
    src/base/multiplot.h src/base/multiplot.cpp
    #
    src/sheets/sheet.h src/sheets/sheet.cpp src/sheets/sheet.txx
    src/sheets/abstractplot.h src/sheets/abstractplot.cpp
    src/sheets/plotdefault.h src/sheets/plotdefault.cpp src/sheets/plotdefault.txx
    src/sheets/plotradial.h src/sheets/plotradial.cpp
    #
    src/elements/axisdescriptor.h src/elements/axisdescriptor.cpp
    src/elements/keydescriptor.h src/elements/keydescriptor.cpp
    src/elements/overlay.h src/elements/overlay.cpp
    src/elements/label.h src/elements/label.cpp
    src/elements/palettedescriptor.h src/elements/palettedescriptor.cpp
    #
    src/dataview/dataview.h src/dataview/dataview.cpp
    src/dataview/dataviewdefault.h src/dataview/dataviewdefault.cpp
    src/dataview/dataviewdefaultcompound.h src/dataview/dataviewdefaultcompound.txx
    src/dataview/dataviewdefaultseparate.h src/dataview/dataviewdefaultseparate.cpp
    src/dataview/dataviewmatrix.h src/dataview/dataviewmatrix.cpp
)

set_target_properties(Plotypus-lib PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PUBLIC_HEADER src/plotypus.h
)

target_precompile_headers(Plotypus-lib PUBLIC
  src/plotypus.h
)

# ============================================================================ #

add_executable(Plotypus-unittest
    src/unittest/main.cpp

    src/unittest/unittest_procs.h
    src/unittest/unittest_report_sheet.cpp
    src/unittest/unittest.h src/unittest/unittest.cpp

    src/unittest/showcase.h
    src/unittest/showcase.cpp src/unittest/showcase_data.cpp
)

target_link_libraries(Plotypus-unittest
    Plotypus-lib
)
