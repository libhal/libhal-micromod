#include <libhal-micromod/micromod.hpp>

#include <libhal-armcortex/dwt_counter.hpp>
#include <libhal-armcortex/interrupt.hpp>
#include <libhal-armcortex/startup.hpp>
#include <libhal-armcortex/system_control.hpp>
#include <libhal-lpc40/adc.hpp>
#include <libhal-lpc40/can.hpp>
#include <libhal-lpc40/clock.hpp>
#include <libhal-lpc40/i2c.hpp>
#include <libhal-lpc40/input_pin.hpp>
#include <libhal-lpc40/interrupt_pin.hpp>
#include <libhal-lpc40/output_pin.hpp>
#include <libhal-lpc40/pwm.hpp>
#include <libhal-lpc40/uart.hpp>
#include <libhal-util/enum.hpp>

namespace hal::micromod::v1 {

void initialize_platform()
{
  using namespace hal::literals;
  constexpr hertz crystal_frequency = 10.0_MHz;

  hal::cortex_m::initialize_data_section();
  hal::cortex_m::initialize_floating_point_unit();
  hal::cortex_m::interrupt::initialize<hal::value(hal::lpc40::irq::max)>();
  hal::lpc40::clock::maximum(crystal_frequency);
}

hal::steady_clock& uptime_clock()
{
  auto& clock = hal::lpc40::clock::get();
  const auto cpu_frequency = clock.get_frequency(hal::lpc40::peripheral::cpu);
  static hal::cortex_m::dwt_counter steady_clock(cpu_frequency);
  return steady_clock;
}

void reset()
{
  hal::cortex_m::reset();
  hal::halt();
}

hal::serial& console(std::span<hal::byte> p_receive_buffer)
{
  static auto driver = hal::lpc40::uart::get(0, p_receive_buffer, {}).value();
  return driver;
}

hal::output_pin& led()
{
  static auto driver = hal::lpc40::output_pin::get(1, 10).value();
  return driver;
}

hal::adc& a0()
{
  static auto driver = hal::lpc40::adc::get(5).value();
  return driver;
}

hal::adc& a1()
{
  static auto driver = hal::lpc40::adc::get(4).value();
  return driver;
}

hal::adc& battery()
{
  static auto driver = hal::lpc40::adc::get(2).value();
  return driver;
}

#if 0
hal::dac& d0();
hal::dac& d1();
#endif

hal::pwm& pwm0()
{
  static auto driver = hal::lpc40::pwm::get(1, 6).value();
  return driver;
}

hal::pwm& pwm1()
{
  static auto driver = hal::lpc40::pwm::get(1, 5).value();
  return driver;
}

hal::i2c& i2c()
{
  static auto driver = hal::lpc40::i2c::get(2).value();
  return driver;
}

hal::interrupt_pin& i2c_interrupt_pin()
{
  static auto driver = hal::lpc40::interrupt_pin::get(2, 6).value();
  return driver;
}

hal::i2c& i2c1()
{
  static auto driver = hal::lpc40::i2c::get(1).value();
  return driver;
}

#if 0
hal::spi& spi();
#endif

hal::output_pin& spi_cs()
{
  static auto driver = hal::lpc40::output_pin::get(1, 8).value();
  return driver;
}

#if 0
hal::spi& spi1();
#endif

hal::output_pin& spi1_cs()
{
  static auto driver = hal::lpc40::output_pin::get(0, 16).value();
  return driver;
}

hal::serial& uart1(std::span<hal::byte> p_buffer)
{
  static auto driver = hal::lpc40::uart::get(1, p_buffer, {}).value();
  return driver;
}

hal::serial& uart2(std::span<hal::byte> p_buffer)
{
  static auto driver = hal::lpc40::uart::get(3, p_buffer, {}).value();
  return driver;
}

hal::can& can()
{
  static auto driver = hal::lpc40::can::get(2).value();
  return driver;
}

struct pin_map
{
  std::uint8_t port;
  std::uint8_t pin;
};

template<std::uint8_t gpio_pin>
constexpr pin_map get_pin_map()
{
  switch (gpio_pin) {
    case 0:
      return pin_map{ .port = 1, .pin = 15 };
    case 1:
      return pin_map{ .port = 1, .pin = 23 };
    case 2:
      return pin_map{ .port = 1, .pin = 22 };
    case 3:
      return pin_map{ .port = 1, .pin = 20 };
    case 4:
      return pin_map{ .port = 1, .pin = 19 };
    case 5:
      return pin_map{ .port = 1, .pin = 28 };
    case 6:
      return pin_map{ .port = 1, .pin = 25 };
    case 7:
      return pin_map{ .port = 1, .pin = 24 };
    case 8:
      return pin_map{ .port = 1, .pin = 29 };
    case 9:
      return pin_map{ .port = 1, .pin = 9 };
    case 10:
      return pin_map{ .port = 1, .pin = 10 };
    case 11:
      return pin_map{ .port = 2, .pin = 3 };
    default:
      // Will cause pin drivers to emit an error if given a port above 5
      return pin_map{ .port = 10, .pin = 0 };
  }
}

template<class pin_t, std::uint8_t gpio_pin>
pin_t& gpio()
{
  constexpr auto pin = get_pin_map<gpio_pin>();
  static auto driver = pin_t::get(pin.port, pin.pin).value();
  return driver;
}

hal::output_pin& output_g0()
{
  return gpio<hal::lpc40::output_pin, 0>();
}
hal::output_pin& output_g1()
{
  return gpio<hal::lpc40::output_pin, 1>();
}
hal::output_pin& output_g2()
{
  return gpio<hal::lpc40::output_pin, 2>();
}
hal::output_pin& output_g3()
{
  return gpio<hal::lpc40::output_pin, 3>();
}
hal::output_pin& output_g4()
{
  return gpio<hal::lpc40::output_pin, 4>();
}
hal::output_pin& output_g5()
{
  return gpio<hal::lpc40::output_pin, 5>();
}
hal::output_pin& output_g6()
{
  return gpio<hal::lpc40::output_pin, 6>();
}
hal::output_pin& output_g7()
{
  return gpio<hal::lpc40::output_pin, 7>();
}
hal::output_pin& output_g8()
{
  return gpio<hal::lpc40::output_pin, 8>();
}
hal::output_pin& output_g9()
{
  return gpio<hal::lpc40::output_pin, 9>();
}
hal::output_pin& output_g10()
{
  return gpio<hal::lpc40::output_pin, 10>();
}
hal::output_pin& output_g11()
{
  return gpio<hal::lpc40::output_pin, 11>();
}

hal::input_pin& input_g0()
{
  return gpio<hal::lpc40::input_pin, 0>();
}
hal::input_pin& input_g1()
{
  return gpio<hal::lpc40::input_pin, 1>();
}
hal::input_pin& input_g2()
{
  return gpio<hal::lpc40::input_pin, 2>();
}
hal::input_pin& input_g3()
{
  return gpio<hal::lpc40::input_pin, 3>();
}
hal::input_pin& input_g4()
{
  return gpio<hal::lpc40::input_pin, 4>();
}
hal::input_pin& input_g5()
{
  return gpio<hal::lpc40::input_pin, 5>();
}
hal::input_pin& input_g6()
{
  return gpio<hal::lpc40::input_pin, 6>();
}
hal::input_pin& input_g7()
{
  return gpio<hal::lpc40::input_pin, 7>();
}
hal::input_pin& input_g8()
{
  return gpio<hal::lpc40::input_pin, 8>();
}
hal::input_pin& input_g9()
{
  return gpio<hal::lpc40::input_pin, 9>();
}
hal::input_pin& input_g10()
{
  return gpio<hal::lpc40::input_pin, 10>();
}
hal::input_pin& input_g11()
{
  return gpio<hal::lpc40::input_pin, 11>();
}

hal::interrupt_pin& interrupt_g0()
{
  return gpio<hal::lpc40::interrupt_pin, 0>();
}
hal::interrupt_pin& interrupt_g1()
{
  return gpio<hal::lpc40::interrupt_pin, 1>();
}
hal::interrupt_pin& interrupt_g2()
{
  return gpio<hal::lpc40::interrupt_pin, 2>();
}
hal::interrupt_pin& interrupt_g3()
{
  return gpio<hal::lpc40::interrupt_pin, 3>();
}
hal::interrupt_pin& interrupt_g4()
{
  return gpio<hal::lpc40::interrupt_pin, 4>();
}
hal::interrupt_pin& interrupt_g5()
{
  return gpio<hal::lpc40::interrupt_pin, 5>();
}
hal::interrupt_pin& interrupt_g6()
{
  return gpio<hal::lpc40::interrupt_pin, 6>();
}
hal::interrupt_pin& interrupt_g7()
{
  return gpio<hal::lpc40::interrupt_pin, 7>();
}
hal::interrupt_pin& interrupt_g8()
{
  return gpio<hal::lpc40::interrupt_pin, 8>();
}
hal::interrupt_pin& interrupt_g9()
{
  return gpio<hal::lpc40::interrupt_pin, 9>();
}
hal::interrupt_pin& interrupt_g10()
{
  return gpio<hal::lpc40::interrupt_pin, 10>();
}
hal::interrupt_pin& interrupt_g11()
{
  return gpio<hal::lpc40::interrupt_pin, 11>();
}
}  // namespace hal::micromod::v1
