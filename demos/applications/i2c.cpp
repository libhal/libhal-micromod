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

#include <libhal-micromod/micromod.hpp>
#include <libhal-util/i2c.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>

void application()
{
  using namespace std::chrono_literals;
  using namespace hal::literals;

  auto& console = hal::micromod::v1::console(hal::buffer<8>);
  auto& clock = hal::micromod::v1::uptime_clock();
  auto& i2c = hal::micromod::v1::i2c();

  hal::print(console, "I2c scanner starting!\n");

  while (true) {
    using namespace std::literals;

    constexpr hal::byte first_i2c_address = 0x08;
    constexpr hal::byte last_i2c_address = 0x78;

    hal::print(console, "Devices Found: ");

    for (hal::byte address = first_i2c_address; address < last_i2c_address;
         address++) {
      // This can only fail if the device is not present
      if (hal::probe(i2c, address)) {
        hal::print<12>(console, "0x%02X ", address);
      }
    }

    print(console, "\n");
    hal::delay(clock, 1s);
  }
}
