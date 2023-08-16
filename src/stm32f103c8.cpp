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
  [[maybe_unused]] constexpr hertz crystal_frequency = 12.0_MHz;

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

hal::output_pin& output_g0()
{
  return gpio<hal::stm32f1::output_pin, 0>();
}
hal::output_pin& output_g1()
{
  return gpio<hal::stm32f1::output_pin, 1>();
}
hal::output_pin& output_g2()
{
  return gpio<hal::stm32f1::output_pin, 2>();
}
hal::output_pin& output_g3()
{
  return gpio<hal::stm32f1::output_pin, 3>();
}
}  // namespace hal::micromod::v1
