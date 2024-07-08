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

#pragma once

#include <array>

#include <libhal/adc.hpp>
#include <libhal/can.hpp>
#include <libhal/dac.hpp>
#include <libhal/i2c.hpp>
#include <libhal/initializers.hpp>
#include <libhal/input_pin.hpp>
#include <libhal/interrupt_pin.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/pwm.hpp>
#include <libhal/serial.hpp>
#include <libhal/spi.hpp>
#include <libhal/steady_clock.hpp>
#include <libhal/timer.hpp>

namespace hal::micromod::v1 {
// =============================================================================
// CORE
// =============================================================================

/**
 * @brief Initialize the system
 *
 * Should be the first API called at the start of main. Typically sets up .data
 * and .bss, heap sections if applicable, interrupt service routine handler and
 * anything else necessary for code to function on the MCU.
 *
 */
void initialize_platform();

/**
 * @brief steady clock to measures the cycles the processor has been up.
 *
 * @return hal::steady_clock& - system uptime steady clock.
 */
[[nodiscard]] hal::steady_clock& uptime_clock();

/**
 * @brief Get core system timer driver
 *
 * Usually used as the system timer for the RTOS
 *
 * @return hal::timer& - reference to the timer
 */
[[nodiscard]] hal::timer& system_timer();

/**
 * @brief Enter power savings mode for your processor
 *
 * Generally needs an interrupt to wake up the device from sleep
 */
void enter_power_saving_mode();

/**
 * @brief Console serial interface
 *
 * The console does not have to implement an actual serial communication
 * protocol like, uart or rs232. It can be implemented with anything such as
 * usb, i2c, spi, usb or something different. It just needs to follow the
 * hal::serial interface for writing, reading bytes from the console.
 *
 * @param p_receive_buffer - The size of the receive buffer for the serial port.
 * Note that subsequent calls to the function will ignore this parameter, thus
 * the first call will set the receive buffer size. Ensure that the lifetime of
 * the buffer is equal to or exceeds the lifetime of the console serial port.
 * @return hal::serial& - serial interface to the console
 */
[[nodiscard]] hal::serial& console(std::span<hal::byte> p_receive_buffer);

/**
 * @brief Retrieve a serial console with a statically allocated receive buffer
 *
 * This helper functions creates a statically allocated buffer based on the
 * buffer parameter passed. The lifetime of this buffer will exist for the
 * duration of the application.
 *
 * USAGE:
 *
 *      auto& console = hal::micromod::v1::console(hal::buffer<128>);
 *
 * Ensure that your application only calls this function once. The console only
 * gets constructed once for the duration of the application, meaning it can
 * only set its internal buffer once. Each call to console will return the
 * already constructed object. Subsequent calls to this function with differing
 * values will create unique receive buffers that go unused. This is a compile
 * time memory leak, because those statically allocated buffers will be
 * inaccessible.
 *
 * If you need to retrieve the console again after the first call, call the
 * console function like so:
 *
 *      auto& console = hal::micromod::v1::console({});  // empty span
 *
 * @param p_receive_buffer_size - target size of the console receive buffer
 * @return hal::serial& - serial interface to the console
 */
[[nodiscard]] inline hal::serial& console(
  hal::buffer_param auto p_receive_buffer_size)
{
  static_assert(p_receive_buffer_size() > 0,
                "Console receive buffer must be greater than 0.");
  static std::array<hal::byte, p_receive_buffer_size()> receive_buffer{};
  return console(receive_buffer);
}

/**
 * @brief Resets the micro-controller, restarting the program in the process.
 *
 * If the application is executed as a program or process on operating system
 * then this function should exit() with the code TBD which will alert the
 * spawner process to rerun the command.
 *
 * This function must not return.
 */
[[noreturn]] void reset();

// =============================================================================
// ON CHIP DEVICES
// =============================================================================

/**
 * @brief Driver for the board LED output pin
 *
 * If this output pin level is called with TRUE, the LED must be ON.
 * If this output pin level is called with FALSE, the LED must be OFF.
 *
 * @return hal::output_pin& - Statically allocated output pin driver connected
 * to the LED.
 */
[[nodiscard]] hal::output_pin& led();

// =============================================================================
// ANALOG
// =============================================================================

/**
 * @brief Driver for adc pin 0
 *
 * @return hal::adc& - Statically allocated analog pin driver.
 */
[[nodiscard]] hal::adc& a0();

/**
 * @brief Driver for adc pin 1
 *
 * @return hal::adc& - Statically allocated analog pin driver.
 */
[[nodiscard]] hal::adc& a1();

/**
 * @brief Driver for battery analog signal which is 1/3rd of the VIN voltage
 *
 * @return hal::adc& - Statically allocated battery analog pin driver.
 */
[[nodiscard]] hal::adc& battery();

/**
 * @brief Driver for dac pin 0
 *
 * @return hal::dac& - Statically allocated dac pin driver.
 */
[[nodiscard]] hal::dac& d0();

/**
 * @brief Driver for dac pin 1
 *
 * @return hal::dac& - Statically allocated dac pin driver.
 */
[[nodiscard]] hal::dac& d1();

/**
 * @brief Driver for pwm pin 0
 *
 * @return hal::pwm& - Statically allocated pwm pin driver.
 */
[[nodiscard]] hal::pwm& pwm0();

/**
 * @brief Driver for pwm pin 1
 *
 * @return hal::pwm& - Statically allocated pwm pin driver.
 */
[[nodiscard]] hal::pwm& pwm1();

// =============================================================================
// Serial Communication
// =============================================================================

/**
 * @brief Driver for the main i2c bus
 *
 * @return hal::i2c& - Statically allocated i2c driver.
 */
[[nodiscard]] hal::i2c& i2c();

/**
 * @brief Driver for i2c interrupt pin
 *
 * NOTE: that this pin can be used as an interrupt pin for both or either i2c
 * buss.
 *
 * @return hal::interrupt_pin& - Statically allocated interrupt pin driver.
 */
[[nodiscard]] hal::interrupt_pin& i2c_interrupt_pin();

/**
 * @brief Driver for the alternative i2c bus 1
 *
 * @return hal::i2c& - Statically allocated i2c driver.
 */
[[nodiscard]] hal::i2c& i2c1();

/**
 * @brief Driver for the main spi bus
 *
 * NOTE: in future iterations of this API, there will exist an sdio port used
 * for talking to SD cards. This port is shared with the future sdio port. Take
 * care to not use this along with the sdio port in the same application as they
 * will conflict with each other resulting in undefined behavior.
 *
 * @return hal::spi&
 */
[[nodiscard]] hal::spi& spi();

/**
 * @brief Driver for spi interrupt pin
 *
 * NOTE: that this pin can be used as an interrupt pin one or both spi ports.
 *
 * @return hal::interrupt_pin& - interrupt pin for spi activity
 */
[[nodiscard]] hal::interrupt_pin& spi_interrupt_pin();

/**
 * @brief Driver for the alternative spi port 1
 *
 * @return hal::spi& - spi port 1
 */
[[nodiscard]] hal::spi& spi1();

/**
 * @brief Driver for uart 1 port
 *
 * @param p_receive_buffer - The size of the receive buffer for the serial port.
 * Note that subsequent calls to the function will ignore this parameter, thus
 * the first call will set the receive buffer size. Ensure that the lifetime of
 * the buffer is equal to or exceeds the lifetime of the uart port.
 * @return hal::serial& - uart port 1
 */
[[nodiscard]] hal::serial& uart1(std::span<hal::byte> p_receive_buffer);

/**
 * @brief Driver for uart 0 port
 *
 * @param p_receive_buffer - The size of the receive buffer for the serial port.
 * Note that subsequent calls to the function will ignore this parameter, thus
 * the first call will set the receive buffer size. Ensure that the lifetime of
 * the buffer is equal to or exceeds the lifetime of the uart port.
 * @return hal::serial& - uart port 2
 */
[[nodiscard]] hal::serial& uart2(std::span<hal::byte> p_receive_buffer);

/**
 * @brief can bus driver
 *
 * @return hal::can& - can driver
 */
[[nodiscard]] hal::can& can();

// =============================================================================
// DIGITAL
// =============================================================================

[[nodiscard]] hal::output_pin& output_g0();
[[nodiscard]] hal::output_pin& output_g1();
[[nodiscard]] hal::output_pin& output_g2();
[[nodiscard]] hal::output_pin& output_g3();
[[nodiscard]] hal::output_pin& output_g4();
[[nodiscard]] hal::output_pin& output_g5();
[[nodiscard]] hal::output_pin& output_g6();
[[nodiscard]] hal::output_pin& output_g7();
[[nodiscard]] hal::output_pin& output_g8();
[[nodiscard]] hal::output_pin& output_g9();
[[nodiscard]] hal::output_pin& output_g10();

[[nodiscard]] hal::input_pin& input_g0();
[[nodiscard]] hal::input_pin& input_g1();
[[nodiscard]] hal::input_pin& input_g2();
[[nodiscard]] hal::input_pin& input_g3();
[[nodiscard]] hal::input_pin& input_g4();
[[nodiscard]] hal::input_pin& input_g5();
[[nodiscard]] hal::input_pin& input_g6();
[[nodiscard]] hal::input_pin& input_g7();
[[nodiscard]] hal::input_pin& input_g8();
[[nodiscard]] hal::input_pin& input_g9();
[[nodiscard]] hal::input_pin& input_g10();

[[nodiscard]] hal::interrupt_pin& interrupt_g0();
[[nodiscard]] hal::interrupt_pin& interrupt_g1();
[[nodiscard]] hal::interrupt_pin& interrupt_g2();
[[nodiscard]] hal::interrupt_pin& interrupt_g3();
[[nodiscard]] hal::interrupt_pin& interrupt_g4();
[[nodiscard]] hal::interrupt_pin& interrupt_g5();
[[nodiscard]] hal::interrupt_pin& interrupt_g6();
[[nodiscard]] hal::interrupt_pin& interrupt_g7();
[[nodiscard]] hal::interrupt_pin& interrupt_g8();
[[nodiscard]] hal::interrupt_pin& interrupt_g9();
[[nodiscard]] hal::interrupt_pin& interrupt_g10();
}  // namespace hal::micromod::v1
