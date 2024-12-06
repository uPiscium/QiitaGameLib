cmake_minimum_required(VERSION 3.20)

include(FetchContent)

function(CloneGLFW)
  message(STATUS "Cloning GLFW...")
  set(GLFW_BUILD_EXAMPLES OFF)
  set(GLFW_BUILD_TESTS OFF)
  set(GLFW_BUILD_DOCS OFF)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4)
  FetchContent_MakeAvailable(glfw)
  message(STATUS "GLFW cloned.")
endfunction()

cloneglfw()
add_subdirectory(Article0)
add_subdirectory(Article1)
