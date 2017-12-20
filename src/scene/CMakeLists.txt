cmake_minimum_required (VERSION 2.8)

set (SCENE_SOURCE_FILES
    "scene.cc")

add_library (Scene STATIC ${SCENE_SOURCE_FILES})