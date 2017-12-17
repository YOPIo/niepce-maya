cmake_minimum_required (VERSION 2.8)

set (LIGHT_SOURCE_FILES
    "area.cc"
    "ibl.cc"
    "light.cc")

add_library (Light STATIC ${LIGHT_SOURCE_FILES})