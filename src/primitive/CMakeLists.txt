cmake_minimum_required (VERSION 2.8)

set (PRIMITIVE_SOURCE_FILES
    "primitive.cc"
    "individual.cc"
    "aggregate.cc")

add_library (Primitive STATIC ${PRIMITIVE_SOURCE_FILES})