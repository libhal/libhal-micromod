# libhal-micromod

[![✅ Checks](https://github.com/libhal/libhal-micromod/actions/workflows/ci.yml/badge.svg)](https://github.com/libhal/libhal-micromod/actions/workflows/ci.yml)
[![GitHub stars](https://img.shields.io/github/stars/libhal/libhal-micromod.svg)](https://github.com/libhal/libhal-micromod/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/libhal/libhal-micromod.svg)](https://github.com/libhal/libhal-micromod/network)
[![GitHub issues](https://img.shields.io/github/issues/libhal/libhal-micromod.svg)](https://github.com/libhal/libhal-micromod/issues)

libhal compatible device library for the micromod device.

## 🛠️ Install MicroMod Profiles

In order to build applications using the micromod library, you need the micromod
profiles. To install them onto your system run:

```bash
conan config install -sf conan/profiles/v1 -tf profiles https://github.com/libhal/libhal-micromod.git
```

If you haven't already, install the ARM GCC profiles as well:

```bash
conan config install -tf profiles -sf conan/profiles/v1 https://github.com/libhal/arm-gnu-toolchain.git
```

## 🏗️ Building the demos

Run the following command to build the applications in the `demos/` directory:

### Building for the lpc4078 v5 micromod

```bash
conan build demos -pr mod-lpc40-v5 -pr arm-gcc-12.3
```

### Building for the stm32f103 v4 micromod

```bash
conan build demos -pr mod-stm32f1-v4 -pr arm-gcc-12.3
```

## 💾 Flashing the MicroMod demos

The final build files will be in the `libhal-micromod/demos/build/micromod/<insert_profile_name>/Release`.
The usual rules for a libhal build directory exists here. For every `.cpp`
source file in the applications directory, there will be a `.elf.bin` file in
the build directory. Use the following flashing commands for the micromod
processors. Replace `/dev/tty.usbserial-1102` with the appropriate serial
device.

### Flashing lpc4078 v5 micromod

```bash
nxpprog --device /dev/tty.usbserial-1102 --control --cpu lpc4078 --binary demos/build/micromod/mod-lpc40-v5/blinker.elf.bin
```

### Flashing stm32f103 v4 micromod

```bash
stm32loader -p /dev/tty.usbserial-1102 -e -w -v demos/build/micromod/mod-stm32f1-v4/blinker.elf.bin
```

### Flashing stm32f103 v5 micromod

```bash
stm32loader -p /dev/tty.usbserial-1102 -e -w -v demos/build/micromod/mod-stm32f1-v5/blinker.elf.bin
```

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.
