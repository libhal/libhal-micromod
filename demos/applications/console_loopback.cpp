// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <array>

#include <libhal-micromod/micromod.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>

hal::status application()
{
  using namespace std::chrono_literals;
  using namespace hal::literals;

  std::array<hal::byte, 512> console_buffer;
  std::array<hal::byte, 1> read_buffer;

  auto& console = hal::micromod::v1::console(console_buffer);

  hal::print(console, "Anything sent will be echoed back> ");

  while (true) {
    auto read_bytes = console.read(read_buffer).value().data;
    if (read_bytes.size() > 0) {
      HAL_CHECK(console.write(read_bytes));
    }
  }

  return hal::success();
}
