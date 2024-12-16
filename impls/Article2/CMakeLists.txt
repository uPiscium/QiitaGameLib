cmake_minimum_required(VERSION 3.20)
project(Article2)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

function(SetIncludes)
  target_include_directories(${PROJECT_NAME} PUBLIC ../../includes/deps)
  target_include_directories(${PROJECT_NAME} PUBLIC ../../includes/Article2)
endfunction()

function(SetLibs)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endfunction()

function(Build)
  add_executable(${PROJECT_NAME} gl.cpp buffer.cpp init.cpp window.cpp main.cpp)
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                   ${CMAKE_BINARY_DIR}/bin)
  setincludes()
  setlibs()
endfunction()

build()
