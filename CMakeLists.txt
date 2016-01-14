cmake_minimum_required(VERSION 2.8)

project(glue_test)

set(PROJECT_BINARY_DIR bin)
set(PROJECT_SOURCE_DIR src)
set(PROJECT_INCLUDE_DIR include/icp)

# Look for c++11 support
if(CMAKE_COMPILER_IS_GNUCXX)
   execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        message(STATUS "C++11 activated.")
        add_definitions("-std=c++11")
   elseif(GCC_VERSION VERSION_GREATER 4.3 OR GCC_VERSION VERSION_EQUAL 4.3)
        message(WARNING "C++0x activated. If you get any errors update to a compiler which fully supports C++11")
        add_definitions("-std=gnu++0x")
   else ()
        message(FATAL_ERROR "C++11 needed. Therefore a gcc compiler with a version higher than 4.3 is needed.")   
   endif()
else(CMAKE_COMPILER_IS_GNUCXX)
   add_definitions("-std=c++0x") 
endif(CMAKE_COMPILER_IS_GNUCXX)

add_definitions(-g -Wall -Wno-comment -Wno-unused-local-typedefs)
include_directories(include)
add_executable(gluetest main.cpp)
target_link_libraries(gluetest
  ${CMAKE_SOURCE_DIR}/libglue/libglue.a
  ${CMAKE_SOURCE_DIR}/libglue/libSmartData.a
  ${CMAKE_SOURCE_DIR}/libglue/librng.a
  pthread
  )
