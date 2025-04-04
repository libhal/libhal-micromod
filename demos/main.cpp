// Copyright 2024 - 2025 Khalil Estell and the libhal contributors
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

#include <libhal-exceptions/control.hpp>
#include <libhal-micromod/micromod.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/error.hpp>

void application();

[[noreturn]] void terminate_handler() noexcept
{
  using namespace std::chrono_literals;
  using namespace hal::literals;
  // Replace this with something that makes sense...
  auto& clock = hal::micromod::v1::uptime_clock();
  auto& led = hal::micromod::v1::led();

  while (true) {
    led.level(false);
    hal::delay(clock, 100ms);
    led.level(true);
    hal::delay(clock, 100ms);
    led.level(false);
    hal::delay(clock, 100ms);
    led.level(true);
    hal::delay(clock, 1000ms);
  }
}

int main()
{
  hal::micromod::v1::initialize_platform();
  hal::set_terminate(terminate_handler);

  application();

  // If application returns for some reason, reset the device.
  hal::micromod::v1::reset();
  return 0;
}
