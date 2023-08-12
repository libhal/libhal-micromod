# Copyright 2023 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.20)

project(demos VERSION 0.0.1 LANGUAGES CXX)

set(platform_library $ENV{LIBHAL_PLATFORM_LIBRARY})
set(platform $ENV{LIBHAL_PLATFORM})

message(WARNING "${platform_library}")
message(WARNING "${demo}")

if("${platform_library}" STREQUAL "")
    message(FATAL_ERROR
        "Build environment variable LIBHAL_PLATFORM_LIBRARY is required for " "this project.")
endif()

if(NOT DEFINED LIBHAL_MICROMOD_DEMO)
    message(FATAL_ERROR
        "Build environment variable LIBHAL_MICROMOD_DEMO is required to "
        "select the appropriate demo source file for this project.")
endif()

find_package(libhal-${platform_library} REQUIRED CONFIG)
find_package(libhal-micromod REQUIRED CONFIG)
find_package(libhal-util REQUIRED CONFIG)
find_package(libhal REQUIRED CONFIG)

add_library(startup_code main.cpp)
target_include_directories(startup_code PUBLIC .)
target_compile_features(startup_code PRIVATE cxx_std_20)
target_link_libraries(startup_code PRIVATE
    libhal::micromod
    libhal::util
    libhal::libhal)

set(current_project ${LIBHAL_MICROMOD_DEMO}.elf)
message(STATUS "Generating Demo for \"${current_project}\"")
add_executable(${current_project} applications/${LIBHAL_MICROMOD_DEMO}.cpp)
target_include_directories(${current_project} PUBLIC .)
target_compile_features(${current_project} PRIVATE cxx_std_20)
target_link_libraries(${current_project} PRIVATE
    libhal::micromod
    libhal::util
    libhal::libhal
    libhal::${platform_library}
    startup_code)
libhal_post_build(${current_project})
libhal_disassemble(${current_project})
