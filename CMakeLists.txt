cmake_minimum_required(VERSION 2.8)

# Project settings
project (niepce)

# c++ basic definitions
add_definitions ("-std=c++11 -O2")

# In this application, we are going to use OpenMP and OpenMaya
# Find OpenMP
find_package (OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  include_directories (SYSTEM ${OpenMP_INCLUDE_PATH})
endif ()

# Find OpenMaya
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

add_subdirectory (src/random)
add_subdirectory (src/core)
add_subdirectory (src/memory)
add_subdirectory (src/sampler)
add_subdirectory (src/shape)
add_subdirectory (src/texture)
add_subdirectory (src/bxdf)
add_subdirectory (src/material)
add_subdirectory (src/light)
add_subdirectory (src/primitive)
add_subdirectory (src/accelerator)
add_subdirectory (src/scene)
add_subdirectory (src/integrator)
add_subdirectory (src/maya)

# add_executable (${PROJECT_NAME})

