#include <libhal/initializers.hpp>

namespace hal::micromod::rp::v1 {
constexpr auto g0 = hal::pin<0>;
constexpr auto g1 = hal::pin<1>;
constexpr auto g2 = hal::pin<2>;
constexpr auto g3 = hal::pin<3>;
constexpr auto g4 = hal::pin<4>;
constexpr auto g5 = hal::pin<5>;
constexpr auto g6 = hal::pin<6>;
constexpr auto g7 = hal::pin<7>;
constexpr auto g8 = hal::pin<8>;
constexpr auto g9 = hal::pin<9>;
constexpr auto g10 = hal::pin<10>;
constexpr auto g11 = hal::pin<11>;
constexpr auto uart_tx = hal::pin<12>;
constexpr auto uart_rx = hal::pin<13>;
constexpr auto uart_cts = hal::pin<14>;
constexpr auto uart_rts = hal::pin<15>;
constexpr auto i2c_sda = hal::pin<16>;
constexpr auto i2c_scl = hal::pin<17>;
constexpr auto i2c_int = hal::pin<18>;
constexpr auto d1 = hal::pin<19>;
constexpr auto uart1_tx = hal::pin<20>;
constexpr auto uart1_rx = hal::pin<21>;
constexpr auto d0 = hal::pin<22>;
constexpr auto can_tx = hal::pin<24>;
constexpr auto can_rx = hal::pin<25>;
constexpr auto i2c1_sda = hal::pin<26>;
constexpr auto i2c1_scl = hal::pin<27>;
constexpr auto vbus_det = hal::pin<36>;
constexpr auto pwm0 = hal::pin<31>;
constexpr auto pwm1 = hal::pin<32>;
constexpr auto spi_cs = hal::pin<33>;
constexpr auto spi_sck = hal::pin<34>;
constexpr auto spi_copi = hal::pin<35>;
constexpr auto spi_cipo = hal::pin<36>;

constexpr auto a0 = hal::pin<40>;
constexpr auto a1 = hal::pin<41>;

// SPI is not actually set to the correct pins on RP2350, but I expose them
// anyways to provide more analog inputs
constexpr auto spi1_sck = hal::pin<42>;
constexpr auto spi1_copi = hal::pin<43>;
constexpr auto spi1_cipo = hal::pin<44>;
constexpr auto spi1_dat = hal::pin<45>;
// This is the LED on top left corner
constexpr auto stat_led = hal::pin<46>;
}  // namespace hal::micromod::rp::v1
