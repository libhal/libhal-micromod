# libhal-micromod

[![✅ Checks](https://github.com/libhal/libhal-micromod/actions/workflows/ci.yml/badge.svg)](https://github.com/libhal/libhal-micromod/actions/workflows/ci.yml)
[![GitHub stars](https://img.shields.io/github/stars/libhal/libhal-micromod.svg)](https://github.com/libhal/libhal-micromod/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/libhal/libhal-micromod.svg)](https://github.com/libhal/libhal-micromod/network)
[![GitHub issues](https://img.shields.io/github/issues/libhal/libhal-micromod.svg)](https://github.com/libhal/libhal-micromod/issues)

A board library for the Sparkfun MicroMod pinout and board protocol that is
compatible with libhal.

## 📚 Software APIs & Usage

To learn about the available drivers and APIs see the
[API Reference](https://libhal.github.io/latest/api/)
documentation page or look at the headers in the
[`include/libhal-micromod`](https://github.com/libhal/libhal-micromod/tree/main/include/libhal-micromod)
directory.

## 🧰 Getting Started with libhal

Checkout the
[🚀 Getting Started](https://libhal.github.io/getting_started/)
instructions.

## 🛠️ Install MicroMod Profiles

In order to build applications using the MicroMod library, you need the MicroMod
profiles. To install them onto your system run:

```bash
conan config install -sf conan/profiles/v1 -tf profiles https://github.com/libhal/libhal-micromod.git
```

If you haven't already, install the ARM GCC profiles as well:

```bash
conan config install -tf profiles -sf conan/profiles/v1 https://github.com/libhal/arm-gnu-toolchain.git
```

> [!INFO]
> To see what profiles are currently supported by this package, simply look
> through the `conan/profiles/v1` directory.

## 🏗️ Building the demos

Run the following command to build the applications in the `demos/` directory:

### Building for the lpc4078 v5 micromod

```bash
conan build demos -pr mod-lpc40-v5 -pr arm-gcc-12.3
```

### Building for the stm32f103 micromod

For V4:

```bash
conan build demos -pr mod-stm32f1-v4 -pr arm-gcc-12.3
```

For V5:

```bash
conan build demos -pr mod-stm32f1-v5 -pr arm-gcc-12.3
```

## 💾 Flashing the MicroMod demos

The final build files will be in the
`libhal-micromod/demos/build/micromod/<insert_profile_name>/Release`.
The usual rules for a libhal build directory exists here. For every `.cpp`
source file in the applications directory, there will be a `.elf.bin` file in
the build directory. Use the following flashing commands for the micromod
processors. Replace `/dev/tty.usbserial-1102` with the appropriate serial
device.

### Flashing lpc4078 v5 MicroMod via USB to serial

```bash
nxpprog --device /dev/tty.usbserial-1102 --control --cpu lpc4078 --binary demos/build/micromod/mod-lpc40-v5/blinker.elf.bin
```

### Flashing stm32f103 v4 MicroMod via USB to serial

For V4:

```bash
stm32loader -p /dev/tty.usbserial-1102 -e -w -v demos/build/micromod/mod-stm32f1-v4/blinker.elf.bin
```

For V5:

```bash
stm32loader -p /dev/tty.usbserial-1102 -e -w -v demos/build/micromod/mod-stm32f1-v5/blinker.elf.bin
```

### Flashing using PyOCD over JTAG/SWD

`PyOCD` is a debugging interface for programming and also debugging ARM Cortex M
processor devices over JTAG and SWD.

This will require a JTAG or SWD debugger. The recommended debugger for the
LPC40 series of devices is the STLink v2 (cheap variants can be found on
Amazon).

See [PyOCD Installation Page](https://pyocd.io/docs/installing) for installation
details.

For reference the flashing command is:

```bash
pyocd flash --target lpc4088 demos/build/lpc4078/MinSizeRel/blinker.elf.bin
pyocd flash --target stm32f103rc demos/build/stm32f103c8/MinSizeRel/blinker.elf.bin
```

> [!NOTE]
> that the targets for your exact part may not exist in `pyocd`. Because of
> this, it means that the bounds of the memory may not fit your device. It is up
> to you to make sure you do not flash a binary larger than what can fit on your
> device.

## 📦 Adding `libhal-micromod` to your project

This section assumes you are using the
[`libhal-starter`](https://github.com/libhal/libhal-starter)
project.

Make sure to add the following options and default options to your app's
`ConanFile` class:

```python
    options = {"platform": ["ANY"]}
    default_options = {"platform": "unspecified"}
```

Add the following to your `requirements()` method:

```python
    def requirements(self):
        self.requires("libhal-micromod/[^1.0.0]")
```

The version number can be changed to whatever is appropriate for your
application. If you don't know what version to use, consider using the
[🚀 latest release](https://github.com/libhal/libhal-util/releases/latest).

The CMake from the starter project will already be ready to support the new
platform library. No change needed.

## 🌟 Package Semantic Versioning Explained

In libhal, different libraries have different requirements and expectations for
how their libraries will be used and how to interpret changes in the semantic
version of a library.

If you are not familiar with [SEMVER](https://semver.org/) you can click the
link to learn more.

### 💥 Major changes

The major number will increment in the event of:

1. An API break
2. A behavior change

We define an API break as an intentional change to the public interface, found
within the `include/` directory, that removes or changes an API in such a way
that code that previously built would no longer be capable of building.

We define a "behavior change" as an intentional change to the documentation of
a public API that would change the API's behavior such that previous and later
versions of the same API would do observably different things.

The usage of the term "intentional" means that the break or behavior change was
expected and accepted for a release. If an API break occurs on accident when it
wasn't previously desired, then such a change should be rolled back and an
alternative non-API breaking solution should be found.

You can depend on the major number to provide API and behavioral
stability for your application. If you upgrade to a new major numbered version
of libhal, your code and applications may or may not continue to work as
expected or compile. Because of this, we try our best to not update the
major number.

### 🚀 Minor changes

The minor number will increment if a new interface, API, or type is introduced
into the public interface.

### 🐞 Patch Changes

The patch number will increment if:

1. Bug fixes that align code to the behavior of an API, improves performance
   or improves code size efficiency.
2. Any changes occur within the `/include/libhal-micromod/experimental`
   directory.
3. An ABI break

For now, you cannot expect ABI or API stability with anything in the
`/include/libhal-micromod/experimental` directory.

ABI breaks with board libraries used directly in applications do cause no issue
and thus are allowed to be patch changes.

## 🏁 Startup & Initialization

Startup is managed by the runtime of the underlying platform library used for a
board. For example, all ARM Cortex M processors use the
[`libhal-arm-mcu`](https://github.com/libhal/libhal-arm-mcu) platform package. Go to those libraries to understand how initialization works for them.

System initialization should include the following for the platform:

1. Sets the main stack registers
2. Write the `.data` section from read-only memory
3. Set the `.bss` section to all zeros
4. Enable FPUs or Coprocessor if present for the core architecture
5. Calls all globally constructed C++ objects
6. Calls `main()`

On top of this, there is the `initialize_platform()` function which should be
called once, and only once, before using any MicroMod APIs. This will:

1. Perform any initialization not capture in the above list
2. Set the clock rate of the system to its maximum.
3. Enable anything necessary to allow other APIs in `micromod.hpp` to work

## ⏳ Object Lifetimes

Many of the MicroMod APIs returns a reference to a libhal interface. To those
that return a reference to a libhal interface are statically allocated and last
the duration of the program after the first call to the API.

> [!NOTE]
> Potentially in the future, we may make a breaking change to return something
> along the lines of a `std::shared_ptr`, `std::unique_ptr`,
> `std::polymorphic`, or something else that manages the lifetime of the
> resource returned from the APIs.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.
