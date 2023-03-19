# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(DriftTube)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

#---Build executable------------------------------------------------------------
add_executable(bdc_DriftLine bdc_DriftLine.C)
target_link_libraries(bdc_DriftLine Garfield::Garfield)

add_executable(bdc_DriftLine2 bdc_DriftLine2.C)
target_link_libraries(bdc_DriftLine2 Garfield::Garfield)

add_executable(map_fieldMap_BDC map_fieldMap_BDC.C)
target_link_libraries(map_fieldMap_BDC Garfield::Garfield)

find_package(ROOT REQUIRED)
find_package(OpenMP)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file P10_0_500000.gas mdt_elx_delta.txt)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
