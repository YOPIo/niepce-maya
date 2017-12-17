cmake_minimum_required (VERSION 2.8)

set (RANDOM_SOURCE_FILES
    "pcg.cc"
    "xorshift.cc")

add_library (Random STATIC ${RANDOM_SOURCE_FILES})