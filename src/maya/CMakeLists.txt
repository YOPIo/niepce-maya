set (MAYA_SOURCE_FILES
  "plugin_main.cc"
  "matte_shader.cc"
  "renderer_command.cc"
  "render_view.cc"
  "maya_tracer.cc"
)

find_package (Maya REQUIRED)

include_directories (${MAYA_INCLUDE_DIR})
link_directories (${MAYA_LIBRARY_DIR})

add_library (${PROJECT_NAME} SHARED ${MAYA_SOURCE_FILES})

target_link_libraries (
  ${PROJECT_NAME}
  ${MAYA_LIBRARIES}
  Integrator
  Scene  
  Accelerator
  Primitive
  Light
  Material
  Bxdf
  Texture  
  Shape
  Sampler  
  Random
  Memory
  Core  
)

MAYA_PLUGIN (${PROJECT_NAME})