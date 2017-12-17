cmake_minimum_required (VERSION 2.8)

set (SHAPE_SOURCE_FILES
    "shape.cc"
    "sphere.cc"
    "triangle.cc")

add_library (Shape STATIC ${SHAPE_SOURCE_FILES})