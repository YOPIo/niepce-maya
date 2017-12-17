cmake_minimum_required(VERSION 2.8)

set (ACCELERATOR_SOURCE_FILES
    "bvh.cc")

add_library (Accelerator STATIC ${ACCELERATOR_SOURCE_FILES})