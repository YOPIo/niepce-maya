cmake_minimum_required (VERSION 2.8)

set (CORE_SOURCE_FILES
    "object.cc"
    "image.cc"
    "pixel.cc"
    "geometry.cc"
    "transform.cc")

add_library (Core STATIC ${CORE_SOURCE_FILES})