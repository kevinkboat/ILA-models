# CMakeLists.txt for cmac
cmake_minimum_required(VERSION 3.14.0)
project(cmac LANGUAGES CXX)

option(ILATOR_PROFILING "Enable instruction sequence logging and profiling" OFF)
option(ILATOR_VERBOSE "Enable instruction state updates logging" OFF)
option(JSON_SUPPORT "Build JSON parser support" OFF)

find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

aux_source_directory(extern extern_src)
add_executable(cmac
  ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cc
  ${extern_src}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/all_valid_funcs_in_hier.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/compute.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/constant_memory_def.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_cache_weights.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_conv_direct.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_set_config_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_set_config_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_set_producer.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_set_start_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_set_start_group1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_cmac_start_from_idle.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_pend2busy.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_1.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_10.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_11.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_12.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_13.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_14.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_15.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_16.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_17.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_18.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_19.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_2.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_20.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_21.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_22.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_23.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_24.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_25.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_26.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_27.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_28.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_29.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_3.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_30.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_31.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_32.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_4.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_5.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_6.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_7.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_8.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_9.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/setup_initial_condition.cc
)

target_include_directories(cmac PRIVATE include)
target_link_libraries(cmac SystemC::systemc)
if(${ILATOR_PROFILING})
  target_compile_definitions(cmac PRIVATE ILATOR_PROFILING)
endif()
if(${ILATOR_VERBOSE})
  target_compile_definitions(cmac PRIVATE ILATOR_PROFILING ILATOR_VERBOSE)
endif()
if(${JSON_SUPPORT})
  include(FetchContent)
  FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.8.0
  )
  FetchContent_MakeAvailable(json)
  target_link_libraries(cmac nlohmann_json::nlohmann_json)
endif()
