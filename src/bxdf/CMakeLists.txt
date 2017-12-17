cmake_minimum_required (VERSION 2.8)

set (BXDF_SOURCE_FILES
    "bsdf.cc"
    "bsdf_utils.cc"
    "fresnel.cc"
    "microfacet.cc"
    "lambert.cc"
    "specular.cc")

add_library (Bxdf STATIC ${BXDF_SOURCE_FILES})