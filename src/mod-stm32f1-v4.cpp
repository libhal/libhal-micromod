#include <libhal-micromod/micromod.hpp>

#include <libhal-arm-mcu/dwt_counter.hpp>
#include <libhal-arm-mcu/interrupt.hpp>
#include <libhal-arm-mcu/startup.hpp>
#include <libhal-arm-mcu/stm32f1/can.hpp>
#include <libhal-arm-mcu/stm32f1/clock.hpp>
#include <libhal-arm-mcu/stm32f1/input_pin.hpp>
#include <libhal-arm-mcu/stm32f1/output_pin.hpp>
#include <libhal-arm-mcu/stm32f1/pin.hpp>
#include <libhal-arm-mcu/stm32f1/uart.hpp>
#include <libhal-arm-mcu/system_control.hpp>
#include <libhal-util/bit_bang_i2c.hpp>
#include <libhal-util/bit_bang_spi.hpp>
#include <libhal-util/enum.hpp>

namespace hal::micromod::v1 {

void initialize_platform()
{
  using namespace hal::literals;
  hal::stm32f1::maximum_speed_using_internal_oscillator();
}

hal::steady_clock& uptime_clock()
{
  static hal::cortex_m::dwt_counter steady_clock(
    hal::stm32f1::frequency(hal::stm32f1::peripheral::cpu));
  return steady_clock;
}

void reset()
{
  hal::cortex_m::reset();
  hal::halt();
}

hal::output_pin& led()
{
  static hal::stm32f1::output_pin driver('C', 13);
  return driver;
}

hal::serial& console(std::span<hal::byte> p_receive_buffer)
{
  static hal::stm32f1::uart driver(hal::runtime{}, 1, p_receive_buffer, {});
  return driver;
}

hal::can& can()
{
  static hal::stm32f1::can driver({}, hal::stm32f1::can_pins::pb9_pb8);
  return driver;
}

struct pin_map
{
  char port;
  std::uint8_t pin;
};

template<std::uint8_t gpio_pin>
constexpr pin_map get_pin_map()
{
  switch (gpio_pin) {
    case 0:
      return pin_map{ .port = 'A', .pin = 0 };
    case 1:
      return pin_map{ .port = 'A', .pin = 15 };
    case 2:
      return pin_map{ .port = 'B', .pin = 3 };
    case 3:
      return pin_map{ .port = 'B', .pin = 4 };
    case 4:
      return pin_map{ .port = 'B', .pin = 12 };
    case 5:
      return pin_map{ .port = 'B', .pin = 13 };
    case 6:
      return pin_map{ .port = 'B', .pin = 14 };
    case 7:
      return pin_map{ .port = 'B', .pin = 15 };
    case 8:
      return pin_map{ .port = 'C', .pin = 13 };
    default:
      // Will cause pin drivers to emit an error & crash if given a port above 8
      return pin_map{ .port = 'F', .pin = 0 };
  }
}

template<class gpio_t, std::uint8_t gpio_pin>
gpio_t& gpio()
{
  constexpr auto pin = get_pin_map<gpio_pin>();
  static gpio_t driver(pin.port, pin.pin);
  return driver;
}

hal::output_pin& output_g0()
{
  return gpio<hal::stm32f1::output_pin, 0>();
}
hal::output_pin& output_g1()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::output_pin, 1>();
}
hal::output_pin& output_g2()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::output_pin, 2>();
}
hal::output_pin& output_g3()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::output_pin, 3>();
}
hal::output_pin& output_g4()
{
  return gpio<hal::stm32f1::output_pin, 4>();
}
hal::output_pin& output_g5()
{
  return gpio<hal::stm32f1::output_pin, 5>();
}
hal::output_pin& output_g6()
{
  return gpio<hal::stm32f1::output_pin, 6>();
}
hal::output_pin& output_g7()
{
  return gpio<hal::stm32f1::output_pin, 7>();
}
hal::output_pin& output_g8()
{
  return gpio<hal::stm32f1::output_pin, 8>();
}

hal::input_pin& input_g0()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::input_pin, 0>();
}
hal::input_pin& input_g1()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::input_pin, 1>();
}
hal::input_pin& input_g2()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::input_pin, 2>();
}
hal::input_pin& input_g3()
{
  hal::stm32f1::release_jtag_pins();
  return gpio<hal::stm32f1::input_pin, 3>();
}
hal::input_pin& input_g4()
{
  return gpio<hal::stm32f1::input_pin, 4>();
}
hal::input_pin& input_g5()
{
  return gpio<hal::stm32f1::input_pin, 5>();
}
hal::input_pin& input_g6()
{
  return gpio<hal::stm32f1::input_pin, 6>();
}
hal::input_pin& input_g7()
{
  return gpio<hal::stm32f1::input_pin, 7>();
}
hal::input_pin& input_g8()
{
  return gpio<hal::stm32f1::input_pin, 8>();
}

hal::i2c& i2c()
{
  static hal::stm32f1::output_pin sda_output_pin('B', 7);
  static hal::stm32f1::output_pin scl_output_pin('B', 6);
  static hal::bit_bang_i2c bit_bang_i2c(
    hal::bit_bang_i2c::pins{
      .sda = &sda_output_pin,
      .scl = &scl_output_pin,
    },
    uptime_clock());

  return bit_bang_i2c;
}

hal::spi& spi()
{
  static hal::stm32f1::output_pin sck('A', 5);
  static hal::stm32f1::output_pin copi('A', 6);
  static hal::stm32f1::input_pin cipo('A', 7);
  static hal::bit_bang_spi bit_bang_spi(
    hal::bit_bang_spi::pins{
      .sck = &sck,
      .copi = &copi,
      .cipo = &cipo,
    },
    uptime_clock());

  return bit_bang_spi;
}

hal::output_pin& spi_chip_select()
{
  static hal::stm32f1::output_pin chip_select_pin('A', 4);
  return chip_select_pin;
}

// =============================================================================
//
// CAN BUS
//
// =============================================================================

namespace {
auto& get_can_peripheral()
{
  using namespace std::chrono_literals;
  static hal::stm32f1::can_peripheral_manager can(
    100_kHz, uptime_clock(), 1ms, hal::stm32f1::can_pins::pb9_pb8);
  return can;
}

template<hal::u8 set_number>
auto& get_identifier_filter_set()
{
  static auto filter_set = get_can_peripheral().acquire_identifier_filter();
  return filter_set;
}

template<hal::u8 set_number>
auto& get_identifier_mask_set()
{
  static auto filter_set = get_can_peripheral().acquire_mask_filter();
  return filter_set;
}

template<hal::u8 set_number>
auto& get_extended_identifier_filter_set()
{
  static auto filter_set =
    get_can_peripheral().acquire_extended_identifier_filter();
  return filter_set;
}

template<hal::u8 mask_number>
auto& get_extended_mask()
{
  static auto filter = get_can_peripheral().acquire_extended_mask_filter();
  return filter;
}
}  // namespace

hal::can_transceiver& can_transceiver(std::span<can_message> p_receive_buffer)
{
  static auto transceiver =
    get_can_peripheral().acquire_transceiver(p_receive_buffer);
  return transceiver;
}

hal::can_bus_manager& can_bus_manager()
{
  static auto bus_manager = get_can_peripheral().acquire_bus_manager();
  return bus_manager;
}

hal::can_interrupt& can_interrupt()
{
  static auto interrupt = get_can_peripheral().acquire_interrupt();
  return interrupt;
}

hal::can_identifier_filter& can_identifier_filter0()
{
  return get_identifier_filter_set<0>().filter[0];
}
hal::can_identifier_filter& can_identifier_filter1()
{
  return get_identifier_filter_set<0>().filter[1];
}
hal::can_identifier_filter& can_identifier_filter2()
{
  return get_identifier_filter_set<0>().filter[2];
}
hal::can_identifier_filter& can_identifier_filter3()
{
  return get_identifier_filter_set<0>().filter[3];
}
hal::can_identifier_filter& can_identifier_filter4()
{
  return get_identifier_filter_set<1>().filter[0];
}
hal::can_identifier_filter& can_identifier_filter5()
{
  return get_identifier_filter_set<1>().filter[1];
}
hal::can_identifier_filter& can_identifier_filter6()
{
  return get_identifier_filter_set<1>().filter[2];
}
hal::can_identifier_filter& can_identifier_filter7()
{
  return get_identifier_filter_set<1>().filter[3];
}

hal::can_mask_filter& can_mask_filter0()
{
  return get_identifier_mask_set<0>().filter[0];
}
hal::can_mask_filter& can_mask_filter1()
{
  return get_identifier_mask_set<0>().filter[1];
}
hal::can_mask_filter& can_mask_filter2()
{
  return get_identifier_mask_set<1>().filter[0];
}
hal::can_mask_filter& can_mask_filter3()
{
  return get_identifier_mask_set<1>().filter[1];
}
hal::can_mask_filter& can_mask_filter4()
{
  return get_identifier_mask_set<2>().filter[0];
}
hal::can_mask_filter& can_mask_filter5()
{
  return get_identifier_mask_set<2>().filter[1];
}
hal::can_mask_filter& can_mask_filter6()
{
  return get_identifier_mask_set<3>().filter[0];
}
hal::can_mask_filter& can_mask_filter7()
{
  return get_identifier_mask_set<3>().filter[1];
}

hal::can_extended_identifier_filter& can_extended_identifier_filter0()
{
  return get_extended_identifier_filter_set<0>().filter[0];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter1()
{
  return get_extended_identifier_filter_set<0>().filter[1];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter2()
{
  return get_extended_identifier_filter_set<1>().filter[0];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter3()
{
  return get_extended_identifier_filter_set<1>().filter[1];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter4()
{
  return get_extended_identifier_filter_set<2>().filter[0];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter5()
{
  return get_extended_identifier_filter_set<2>().filter[1];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter6()
{
  return get_extended_identifier_filter_set<3>().filter[0];
}
hal::can_extended_identifier_filter& can_extended_identifier_filter7()
{
  return get_extended_identifier_filter_set<3>().filter[1];
}

hal::can_extended_mask_filter& can_extended_mask_filter0()
{
  return get_extended_mask<0>();
}
hal::can_extended_mask_filter& can_extended_mask_filter1()
{
  return get_extended_mask<1>();
}
hal::can_extended_mask_filter& can_extended_mask_filter2()
{
  return get_extended_mask<2>();
}
hal::can_extended_mask_filter& can_extended_mask_filter3()
{
  return get_extended_mask<3>();
}
hal::can_extended_mask_filter& can_extended_mask_filter4()
{
  return get_extended_mask<4>();
}
hal::can_extended_mask_filter& can_extended_mask_filter5()
{
  return get_extended_mask<5>();
}
hal::can_extended_mask_filter& can_extended_mask_filter6()
{
  return get_extended_mask<6>();
}
hal::can_extended_mask_filter& can_extended_mask_filter7()
{
  return get_extended_mask<7>();
}
}  // namespace hal::micromod::v1
