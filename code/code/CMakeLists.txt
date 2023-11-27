cmake_minimum_required(VERSION 3.20)
project(GLIII_Introduction)

set(CMAKE_CXX_STANDARD 17)

option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF)
add_subdirectory(extern/box2d)

add_subdirectory(extern/glad)

add_subdirectory(extern/glfw)

add_subdirectory(extern/glm)

add_subdirectory(extern/soloud)

add_subdirectory(extern/tinygltf)


add_subdirectory(game)

add_subdirectory(engine)

file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/game")