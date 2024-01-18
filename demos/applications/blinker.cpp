// Copyright 2024 Khalil Estell
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

  auto& clock = hal::micromod::v1::uptime_clock();
  auto& led = hal::micromod::v1::led();

  while (true) {
    HAL_CHECK(led.level(true));
    hal::delay(clock, 500ms);
    HAL_CHECK(led.level(false));
    hal::delay(clock, 500ms);
  }

  return hal::success();
}
