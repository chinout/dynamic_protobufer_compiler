set(protobuf_source_dir "${PROJECT_SOURCE_DIR}/protobuf")

if(UNIX)
  if(COMPILE_PROTOBUF)
    add_definitions(-DHAVE_PTHREAD)
    #add_compile_options(-fPIC)
    #add_compile_options(-Wno-sign-compare)
    #add_compile_options(-Wno-unused-function)

    include(cmake/libprotobuf.cmake)
    include(cmake/libprotoc.cmake)
    include(cmake/protoc.cmake)
    set(PROTOBUF_PROTOC_EXECUTABLE protoc)
    set(PROTOBUF_LIBRARIES libprotobuf)
  else()
    set(PROTOBUF_PROTOC_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/linux/protoc")
    set(PROTOBUF_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/linux/libprotobuf.a")
  endif()
else()
  if (COMPILE_PROTOBUF)
    set(CMAKE_STATIC_LINKER_FLAGS /ignore:4221)
    include(cmake/libprotobuf.cmake)
    include(cmake/libprotoc.cmake)
    include(cmake/protoc.cmake)
    set(PROTOBUF_LIBRARIES libprotobuf)
    set(PROTOBUF_PROTOC_EXECUTABLE protoc)
  else()
    set(PROTOBUF_PROTOC_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/windows/protoc.exe")
    set(PROTOBUF_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/windows/lib/libprotobuf.lib")
  endif()
endif()

file(GLOB PROTOS "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
set(INPUT_DIR   ${CMAKE_CURRENT_SOURCE_DIR})
set(PROTOC_C_OUT_FLAG --cpp_out)
set(PROTO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out)
foreach(PROTO ${PROTOS})
  get_filename_component(PROTO_NAME ${PROTO} NAME_WE)
  set(CUR_PROTO_GEN
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.cc)
  set(PROTO_GEN
    ${PROTO_GEN}
    ${CUR_PROTO_GEN})
  add_custom_command(
    OUTPUT ${CUR_PROTO_GEN}
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO} ${PROTOC_C_OUT_FLAG} ${PROTO_GEN_DIR} -I${INPUT_DIR}
    DEPENDS ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

add_library(pblib ${PROTO_GEN} ${PROTOS})
target_link_libraries(pblib ${PROTOBUF_LIBRARIES})
set_target_properties(pblib PROPERTIES PREFIX "")