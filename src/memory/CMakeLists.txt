cmake_minimum_required (VERSION 2.8)

set (MEMORY_SOURCE_FILES
    "arena_allocator.cc")

add_library (Memory STATIC ${MEMORY_SOURCE_FILES})
