# CMakeLists.txt for cacc
cmake_minimum_required(VERSION 3.14.0)
project(cacc LANGUAGES CXX)

option(ILATOR_PROFILING "Enable instruction sequence logging and profiling" OFF)
option(ILATOR_VERBOSE "Enable instruction state updates logging" OFF)
option(JSON_SUPPORT "Build JSON parser support" OFF)

find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

aux_source_directory(extern extern_src)
add_executable(cacc
  ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cc
  ${extern_src}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/all_valid_funcs_in_hier.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/compute.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/constant_memory_def.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_dc_accumulate.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_batch_number_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_batch_number_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_clip_cfg_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_clip_cfg_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_addr_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_addr_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_map_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_map_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_size_0_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_size_0_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_size_1_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_dataout_size_1_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_line_stride_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_line_stride_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_misc_cfg_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_misc_cfg_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_op_enable_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_op_enable_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_producer.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_surf_stride_reg_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_set_surf_stride_reg_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_start_from_idle.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cacc_truncate.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_pend2busy.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_2.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/setup_initial_condition.cc
)

target_include_directories(cacc PRIVATE include)
target_link_libraries(cacc SystemC::systemc)
if(${ILATOR_PROFILING})
  target_compile_definitions(cacc PRIVATE ILATOR_PROFILING)
endif()
if(${ILATOR_VERBOSE})
  target_compile_definitions(cacc PRIVATE ILATOR_PROFILING ILATOR_VERBOSE)
endif()
if(${JSON_SUPPORT})
  include(FetchContent)
  FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.8.0
  )
  FetchContent_MakeAvailable(json)
  target_link_libraries(cacc nlohmann_json::nlohmann_json)
endif()
