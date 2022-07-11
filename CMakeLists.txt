cmake_minimum_required(VERSION 3.5)

# ============================================================================ #
# lanugage definition

project(Plotypus
    VERSION 0.0.1
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
    src/definitions/styles.h
    src/definitions/errors.h
    src/base/localMacros.h
    #
    src/base/stylescollection.h src/base/stylescollection.cpp
    src/base/sheet.h src/base/sheet.cpp
    src/base/report.h src/base/report.cpp src/base/report.txx
    #
    src/plot/plot.h src/plot/plot.cpp
    src/plot/plot2d.h src/plot/plot2d.txx
    #
    src/dataview/dataview.h src/dataview/dataview.cpp
    src/dataview/dataview2d.h src/dataview/dataview2d.txx
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
    src/unittest/unittest.h src/unittest/unittest.cpp
)

target_link_libraries(Plotypus-unittest
    Plotypus-lib
)
