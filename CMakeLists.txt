cmake_minimum_required(VERSION 3.20)

project(Insight CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(EXTERNALS_DIR "${PROJECT_SOURCE_DIR}/libs")

include(scripts/git.cmake)

message("\nFetching modules")
include(scripts/minhook.cmake)
include(scripts/g3log.cmake)
include(scripts/json.cmake)
include(scripts/zydis.cmake)
message("\nFetching custom modules")
include(scripts/gtav-classes.cmake)
include(scripts/pugixml.cmake)

message(STATUS "Insight")
message("SRC_DIR: ${SRC_DIR}")
message("json_SOURCE_DIR: ${json_SOURCE_DIR}")
message("gtav_classes_SOURCE_DIR: ${gtav_classes_SOURCE_DIR}")


# set(CMAKE_COMPILE_PDB_NAME "Insight")  (PDB REMOVE ME AND #)
# set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) (PDB REMOVE ME AND #)


# set(PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/Release") (PDB REMOVE ME AND #)

if (MSVC)
   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /Ot /GL /Oi /Oy /Zi") (PDB REPLACE ME AND # BOTTOM ONE)  
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /Ot /GL /Oi /Oy")
endif()

string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c-")
add_definitions(-D_HAS_EXCEPTIONS=0)
  
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)

add_library(Insight MODULE "${SRC_MAIN}" )

set_target_properties(Insight PROPERTIES PDB_NAME "Insight")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Insight PROPERTY CXX_STANDARD 23)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN})

target_include_directories(Insight PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${gtav_classes_SOURCE_DIR}"
    ${EXTERNALS_DIR}
)

target_precompile_headers(Insight PRIVATE "${SRC_DIR}/common.hpp")
add_compile_options("$<$<CONFIG:DEBUG>:-g>")
target_link_directories(Insight PRIVATE "${CMAKE_SOURCE_DIR}/libs")
target_link_libraries(Insight PRIVATE
    discord-rpc
    VMProtectSDK64
    SecureEngineSDK64
    libcrypto
    pugixml
    minhook
    g3log
    libcurl_a.lib
    Zydis 
)

add_compile_definitions(Insight 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)
