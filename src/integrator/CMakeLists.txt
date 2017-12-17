cmake_minimum_required (VERSION 2.8)

set (INTEGRATOR_SOURCE_FILES
    "integrator.cc"
    "sample_integrator.cc"
    "path_tracer.cc"
    "debug.cc")

add_library (Integrator STATIC ${INTEGRATOR_SOURCE_FILES})