cmake_minimum_required(VERSION 3.5)

project(protobuf_test)
if(UNIX)
  set(THREAD_LIBRARY pthread)
endif()

option(COMPILE_PROTOBUF "Compile protobuf" OFF)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/protobuf/src")
add_subdirectory(proto)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/proto/out")
add_executable(main main.cpp)
target_link_libraries(main pblib)
