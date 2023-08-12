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

  std::array<hal::byte, 64> console_buffer;

  auto& clock = hal::micromod::v1::uptime_clock();
  auto& console = hal::micromod::v1::console(console_buffer);

  while (true) {
    hal::print(console, "Hello World\n");
    hal::delay(clock, 500ms);
  }

  return hal::success();
}
