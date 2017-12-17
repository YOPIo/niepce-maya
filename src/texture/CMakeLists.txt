cmake_minimum_required (VERSION 2.8)

set (TEXTURE_SOURCE_FILES
    "texture.cc"
    "image_map.cc"
    "constant_texture.cc")

add_library (Texture STATIC ${TEXTURE_SOURCE_FILES})