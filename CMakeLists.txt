cmake_minimum_required (VERSION 3.1)
project (json_packer)
set (CMAKE_CXX_STANDARD 11)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    if( OUTPUTCONFIG STREQUAL "RELEASE" )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    else()
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG} )
    endif()
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(JSONCONS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/jsoncons/src)
set(NLOHMANNJSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/json/src)
if(MSVC)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${JSONCONS_INCLUDE_DIR} ${NLOHMANNJSON_INCLUDE_DIR})

add_executable(packer_jsoncons ${CMAKE_SOURCE_DIR}/src/packer_jsoncons.cpp)
add_executable(packer_nlohmannjson ${CMAKE_SOURCE_DIR}/src/packer_nlohmannjson.cpp)
