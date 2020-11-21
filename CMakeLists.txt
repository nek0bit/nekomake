# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(nekomake)

include_directories(include)

# Add source to this project's executable.
add_executable(nekomake
	"src/glad.c"
	"src/nekomake.cpp"
	"src/nekomake.hpp"
	"src/game.hpp"
	"src/game.cpp"
	"src/shader.hpp"
	"src/shader.cpp" "src/textures.hpp" "src/textures.cpp" "src/mesh.hpp" "src/mesh.cpp")

target_link_libraries(nekomake ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib)
