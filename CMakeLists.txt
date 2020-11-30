cmake_minimum_required (VERSION 3.8)

project(nekomake)

if (MSVC)
  include_directories(include/)
elseif(UNIX)
  include_directories(/usr/include include/)
endif()

add_definitions(-DDATA="${DATA}")

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable(nekomake ${SOURCES})

if (MSVC)
  target_link_libraries(nekomake ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib)
elseif(UNIX)
  target_link_libraries(nekomake dl glfw)
endif()
