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

cmake_minimum_required(VERSION 3.15)

project(libhal-micromod VERSION 0.0.1 LANGUAGES CXX)

set(platform_library $ENV{LIBHAL_PLATFORM_LIBRARY})
set(platform $ENV{LIBHAL_PLATFORM})

message(NOTICE ">> 🔎 Building with CMake version: ${CMAKE_VERSION}")
message(NOTICE ">> 🔎 Platform library = ${platform_library}")
message(NOTICE ">> 🔎 Platform library = ${platform}")

if("${platform_library}" STREQUAL "")
  message(FATAL_ERROR
    "Build environment variable LIBHAL_PLATFORM_LIBRARY is required for " "this project.")
endif()

find_package(libhal-${platform_library} REQUIRED CONFIG)

add_library(libhal-micromod src/${platform}.cpp)
target_include_directories(libhal-micromod PUBLIC include)
target_compile_features(libhal-micromod PRIVATE cxx_std_20)
target_compile_options(libhal-micromod PRIVATE -Wall -Wextra)
target_link_libraries(libhal-micromod PRIVATE
  libhal::${platform_library}
)

install(TARGETS libhal-micromod)
