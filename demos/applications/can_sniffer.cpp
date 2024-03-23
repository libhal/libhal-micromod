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
#include <libhal-util/serial.hpp>
#include <libhal/units.hpp>

void application()
{
  using namespace std::chrono_literals;
  using namespace hal::literals;

  auto& can = hal::micromod::v1::can();
  auto& console = hal::micromod::v1::console(hal::buffer<64>);

  hal::print(console, "Waiting for CAN messages...\n");

  can.on_receive([&console](const hal::can::message_t& p_message) {
    hal::print<64>(console, "{ ");
    hal::print<64>(console, "id = %lu, ", p_message.id);
    hal::print<64>(console, "length = %lu, ", p_message.length);
    hal::print(console, "payload = { ");
    for (const auto& data : std::span<const hal::byte>(p_message.payload)
                              .first(p_message.length)) {
      hal::print<8>(console, "0x%02X, ", data);
    }
    hal::print<64>(console, "}\n");
  });

  while (true) {
    continue;
  }
}
