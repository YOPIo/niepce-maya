cmake_minimum_required (VERSION 2.8)

set (MATERIAL_SOURCE_FILES
    "material.cc"
    "matte.cc"
    "glass.cc"
    "microfacet_test.cc"
    "mirror.cc")

add_library (Material STATIC ${MATERIAL_SOURCE_FILES})