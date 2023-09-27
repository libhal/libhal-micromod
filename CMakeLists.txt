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

project(libhal-micromod LANGUAGES CXX)

set(platform_library $ENV{LIBHAL_PLATFORM_LIBRARY})
set(platform $ENV{LIBHAL_PLATFORM})

message(NOTICE ">> 🔎 Building with CMake version: ${CMAKE_VERSION}")
message(NOTICE ">> 🔎 Platform library = ${platform_library}")
message(NOTICE ">> 🔎 Platform library = ${platform}")

if("${platform_library}" STREQUAL "")
  message(FATAL_ERROR
    "Build environment variable LIBHAL_PLATFORM_LIBRARY is required for "
    "this project.")
endif()

libhal_make_library(
  LIBRARY_NAME libhal-micromod

  SOURCES
  src/${platform}.cpp

  PACKAGES
  libhal-${platform_library}

  LINK_LIBRARIES
  libhal::${platform_library}
)
