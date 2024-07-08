# Copyright 2024 Khalil Estell
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake
from conan import ConanFile

required_conan_version = ">=2.2.2"


class libhal_micromod_conan(ConanFile):
    name = "libhal-micromod"
    license = "Apache-2.0"
    description = (
        "A collection of drivers for the MicroMod processor interface.")
    topics = ("micromod", "libhal", "driver")
    settings = "compiler", "build_type", "os", "arch"
    options = {
        "platform": ["ANY"],
        "micromod_board": ["ANY"],
    }
    default_options = {
        "platform": "unspecified",
        "micromod_board": "unspecified",
    }

    python_requires = "libhal-bootstrap/[^2.1.2]"
    python_requires_extend = "libhal-bootstrap.library"

    def build(self):
        cmake = CMake(self)

        micromod_board = str(self.options.micromod_board)
        if micromod_board == "mod-lpc40-v5":
            platform_library = "lpc40"
        elif micromod_board == "mod-stm32f1-v4":
            platform_library = "stm32f1"

        cmake.configure(variables={
            "LIBHAL_MICROMOD_BOARD": str(self.options.micromod_board),
            "LIBHAL_PLATFORM_LIBRARY": platform_library
        })

        cmake.build()

    def requirements(self):
        bootstrap = self.python_requires["libhal-bootstrap"]
        bootstrap.module.add_library_requirements(self)

        LPC40_PACKAGE = "libhal-lpc40/[^5.1.0]"
        STM32F1_PACKAGE = "libhal-stm32f1/[^5.0.0]"

        micromod_board = str(self.options.micromod_board)
        if micromod_board == "mod-lpc40-v5":
            self.requires(LPC40_PACKAGE, transitive_headers=True)
        elif micromod_board == "mod-stm32f1-v4":
            self.requires(STM32F1_PACKAGE, transitive_headers=True)
        else:
            raise ConanInvalidConfiguration(
                f"MicroMod Board '{micromod_board}' not supported!")

    def package_info(self):
        self.cpp_info.libs = ["libhal-micromod"]
        self.cpp_info.set_property("cmake_target_name", "libhal::micromod")
        self.buildenv_info.define("LIBHAL_PLATFORM", "micromod")
        self.buildenv_info.define("LIBHAL_PLATFORM_LIBRARY", "micromod")

    def validate(self):
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, self._min_cppstd)
        if "micromod" != str(self.options.platform):
            raise ConanInvalidConfiguration(
                f"Invalid platform '{str(self.options.platform)}'. This package cannot be used if the platform is not set to 'micromod'")
