#include <libhal-micromod/micromod.hpp>

#include <libhal-armcortex/dwt_counter.hpp>
#include <libhal-armcortex/interrupt.hpp>
#include <libhal-armcortex/startup.hpp>
#include <libhal-armcortex/system_control.hpp>
#include <libhal-stm32f1/clock.hpp>
#include <libhal-stm32f1/output_pin.hpp>
#include <libhal-util/enum.hpp>

namespace hal::micromod::v1 {

void initialize_platform()
{
  using namespace hal::literals;
  constexpr hertz crystal_frequency = 12.0_MHz;

  hal::cortex_m::initialize_data_section();
  hal::cortex_m::initialize_floating_point_unit();
  hal::cortex_m::interrupt::initialize<hal::value(hal::stm32f1::irq::max)>();
  // hal::stm32f1::configure_clocks();
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
  static auto driver = hal::stm32f1::output_pin::get('C', 13).value();
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
      return pin_map{ .port = 'B', .pin = 4 };
    case 1:
      return pin_map{ .port = 'B', .pin = 3 };
    case 2:
      return pin_map{ .port = 'A', .pin = 15 };
    case 3:
      return pin_map{ .port = 'C', .pin = 13 };
    default:
      // Will cause pin drivers to emit an error & crash if given a port above 3
      return pin_map{ .port = 'F', .pin = 0 };
  }
}

template<class pin_t, std::uint8_t gpio_pin>
pin_t& gpio()
{
  constexpr auto pin = get_pin_map<gpio_pin>();
  static auto driver = pin_t::get(pin.port, pin.pin).value();
  return driver;
}

namespace output {
hal::output_pin& g0()
{
  return gpio<hal::stm32f1::output_pin, 0>();
}
hal::output_pin& g1()
{
  return gpio<hal::stm32f1::output_pin, 1>();
}
hal::output_pin& g2()
{
  return gpio<hal::stm32f1::output_pin, 2>();
}
hal::output_pin& g3()
{
  return gpio<hal::stm32f1::output_pin, 3>();
}
}  // namespace output

#if 0
hal::serial& console(std::span<hal::byte> p_receive_buffer);
hal::output_pin& led();
hal::adc& a0();
hal::adc& a1();
hal::adc& battery();
hal::dac& d0();
hal::dac& d1();
hal::pwm& pwm0();
hal::pwm& pwm1();
hal::i2c& i2c();
hal::interrupt_pin& i2c_interrupt_pin();
hal::i2c& i2c1();
hal::spi& spi();
hal::output_pin& spi_cs();
hal::spi& spi1();
hal::output_pin& spi1_cs();
hal::serial& uart1(std::span<hal::byte> p_buffer);
hal::serial& uart2(std::span<hal::byte> p_buffer);
hal::can& can();
#endif
}  // namespace hal::micromod::v1
