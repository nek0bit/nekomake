cmake_minimum_required (VERSION 3.8)

project(nekomake)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (MSVC)
  include_directories(include/)
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ffast-math")
  
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
