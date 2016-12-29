cmake_minimum_required (VERSION 3.5)
project (cpp-data-types)

find_program( MEMORYCHECK_COMMAND valgrind )
set( CMAKE_BUILD_TYPE debug )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -g -Wall " )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

include_directories("${PROJECT_BINARY_DIR}")
file(GLOB cpp-data-types_src
  "src/*.h"
  "src/*.cpp"
  "src/*.hpp"
  )
file(GLOB cpp-data-types_tests
  "tests/*.h"
  "tests/*.cpp")

add_library(cpp-data-types ${cpp-data-types_src})

add_custom_target(run
  COMMAND tests
  DEPENDS tests
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )

add_executable(tests ${cpp-data-types_tests})
target_link_libraries(tests cpp-data-types)
target_compile_options(tests PUBLIC -ansi -g -Wall)


