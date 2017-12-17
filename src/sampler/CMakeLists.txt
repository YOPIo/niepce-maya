cmake_minimum_required (VERSION 2.8)

set (SAMPLER_SOURCE_FILES
    "sampler.cc"
    "sampler_utils.cc"
    "random_sampler.cc")

add_library (Sampler STATIC ${SAMPLER_SOURCE_FILES})