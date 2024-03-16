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

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class demos(ConanFile):
    settings = "compiler", "build_type", "os", "arch"
    # generators = "CMakeToolchain", "CMakeDeps", "VirtualBuildEnv"
    options = {"platform": ["ANY"]}
    default_options = {"platform": "unspecified"}

    python_requires = "libhal-bootstrap/[^1.0.0]"
    python_requires_extend = "libhal-bootstrap.demo"

    def requirements(self):
        bootstrap = self.python_requires["libhal-bootstrap"]
        bootstrap.module.add_demo_requirements(self)
        self.requires("libhal-micromod/[^1.0.0 || latest]")

    def build(self):
        demos = ["blinker", "hello_world", "console_loopback"]
        statuses = []
        for demo in demos:
            cmake = CMake(self)
            cmake.configure(variables={"LIBHAL_MICROMOD_DEMO": demo})
            try:
                cmake.build()
                statuses.append({"demo_name": demo, "success": True})
            except:
                statuses.append({"demo_name": demo, "success": False})

        banner = """\x1b[38;5;202m
███╗   ███╗██╗ ██████╗██████╗  ██████╗ ███╗   ███╗ ██████╗ ██████╗
████╗ ████║██║██╔════╝██╔══██╗██╔═══██╗████╗ ████║██╔═══██╗██╔══██╗
██╔████╔██║██║██║     ██████╔╝██║   ██║██╔████╔██║██║   ██║██║  ██║
██║╚██╔╝██║██║██║     ██╔══██╗██║   ██║██║╚██╔╝██║██║   ██║██║  ██║
██║ ╚═╝ ██║██║╚██████╗██║  ██║╚██████╔╝██║ ╚═╝ ██║╚██████╔╝██████╔╝
╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝ ╚═════╝ ╚═════╝ """

        banner2 = """\x1b[38;5;214m
██████╗ ███████╗███╗   ███╗ ██████╗ ███████╗
██╔══██╗██╔════╝████╗ ████║██╔═══██╗██╔════╝
██║  ██║█████╗  ██╔████╔██║██║   ██║███████╗
██║  ██║██╔══╝  ██║╚██╔╝██║██║   ██║╚════██║
██████╔╝███████╗██║ ╚═╝ ██║╚██████╔╝███████║
╚═════╝ ╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝
\x1b[1;0m"""

        print(banner,
              banner2,
              "\nDemos available for this MicroMod Profile "
              f"({self.options.platform}):\n")

        for status in statuses:
            if status["success"]:
                print(f"    ✅ {status['demo_name']}")
            else:
                print(f"    ❌ {status['demo_name']}")

        print("")
