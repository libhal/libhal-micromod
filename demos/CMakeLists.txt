# Copyright 2024 Khalil Estell
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

cmake_minimum_required(VERSION 3.25)

project(demos LANGUAGES CXX)

if(NOT DEFINED LIBHAL_MICROMOD_DEMO)
    message(FATAL_ERROR
        "Build environment variable LIBHAL_MICROMOD_DEMO is required to "
        "select the appropriate demo source file for this project.")
endif()

cmake_minimum_required(VERSION 3.25)

project(demos LANGUAGES CXX)

set(current_project ${LIBHAL_MICROMOD_DEMO}.elf)
message(STATUS "Generating Demo for \"${current_project}\"")
libhal_build_demos(
    DEMOS
    ${LIBHAL_MICROMOD_DEMO}

    PACKAGES
    libhal-micromod

    LINK_LIBRARIES
    libhal::micromod
)