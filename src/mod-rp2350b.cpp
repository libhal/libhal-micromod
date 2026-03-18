#include "libhal-micromod/micromod.hpp"
#include "libhal-micromod/rp/rp2350b_pins.hpp"

// Unclear if anything should actually be implemented, for now
// just leave stems in case I do feel like implementing. Currently
// we don't use libhal-micromod anyways
namespace hal::micromod::v1 {

void initialize_platform()
{
}

[[nodiscard]] hal::steady_clock& uptime_clock();
void enter_power_saving_mode();

[[nodiscard]] hal::serial& console(std::span<hal::byte>);

[[noreturn]] void reset();

[[nodiscard]] hal::output_pin& led();

[[nodiscard]] hal::adc& a0();
[[nodiscard]] hal::adc& a1();

[[nodiscard]] hal::adc& battery();

[[nodiscard]] hal::pwm& pwm0();

[[nodiscard]] hal::pwm& pwm1();

[[nodiscard]] hal::i2c& i2c();
[[nodiscard]] hal::interrupt_pin& i2c_interrupt_pin();
[[nodiscard]] hal::i2c& i2c1();
[[nodiscard]] hal::spi& spi();

[[nodiscard]] hal::output_pin& spi_chip_select();

[[nodiscard]] hal::spi& spi1();
[[nodiscard]] hal::serial& uart1(std::span<hal::byte> p_receive_buffer);

[[nodiscard]] hal::serial& uart2(std::span<hal::byte> p_receive_buffer);

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
