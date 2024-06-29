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
  hal::lpc40::maximum(crystal_frequency);
}

hal::steady_clock& uptime_clock()
{
  auto const cpu_frequency =
    hal::lpc40::get_frequency(hal::lpc40::peripheral::cpu);
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
  static hal::lpc40::uart driver(0, p_receive_buffer, {});
  return driver;
}

hal::output_pin& led()
{
  static hal::lpc40::output_pin driver(1, 10);
  return driver;
}

hal::adc& a0()
{
  static hal::lpc40::adc driver(hal::channel<5>);
  return driver;
}

hal::adc& a1()
{
  static hal::lpc40::adc driver(hal::channel<4>);
  return driver;
}

hal::adc& battery()
{
  static hal::lpc40::adc driver(hal::channel<2>);
  return driver;
}

#if 0
hal::dac& d0();
hal::dac& d1();
#endif

hal::pwm& pwm0()
{
  static hal::lpc40::pwm driver(1, 6);
  return driver;
}

hal::pwm& pwm1()
{
  static hal::lpc40::pwm driver(1, 5);
  return driver;
}

hal::i2c& i2c()
{
  static hal::lpc40::i2c driver(2);
  return driver;
}

hal::interrupt_pin& i2c_interrupt_pin()
{
  static hal::lpc40::interrupt_pin driver(2, 6);
  return driver;
}

hal::i2c& i2c1()
{
  static hal::lpc40::i2c driver(1);
  return driver;
}

#if 0
hal::spi& spi();
#endif

hal::output_pin& spi_cs()
{
  static hal::lpc40::output_pin driver(1, 8);
  return driver;
}

#if 0
hal::spi& spi1();
#endif

hal::output_pin& spi1_cs()
{
  static hal::lpc40::output_pin driver(0, 16);
  return driver;
}

hal::serial& uart1(std::span<hal::byte> p_buffer)
{
  static hal::lpc40::uart driver(1, p_buffer, {});
  return driver;
}

hal::serial& uart2(std::span<hal::byte> p_buffer)
{
  static hal::lpc40::uart driver(3, p_buffer, {});
  return driver;
}

hal::can& can()
{
  static hal::lpc40::can driver(2);
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

template<class gpio_t, std::uint8_t gpio_pin>
gpio_t& gpio()
{
  constexpr auto pin = get_pin_map<gpio_pin>();
  static gpio_t driver(pin.port, pin.pin);
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
