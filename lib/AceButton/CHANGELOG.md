# Changelog

* Unreleased
* 1.4.2 (2020-02-03)
    * Fix compiler warnings.
    * Fix broken automated tests.
* 1.4.1 (2020-01-20)
    * Implement generalized `EncodedButtonConfig` which can handle
      `M=2^N-1` buttons using `N` pins using an optimization that makes
      only `N` calls to `digitalRead()` instead of `M * N` calls. Add
      `examples/Encoded16To4Buttons` example; rename `examples/EncodedButtons`
      to `examples/Encoded8To3Buttons`.
* 1.4 (2020-01-12)
    * Add better explanation and examples of multiple buttons to the README.md.
    * Add `Encoded8To3ButtonConfig` and ` Encoded4To2ButtonConfig` classes to
      support [BinaryEncoding](docs/binary_encoding/). Verified to work using
      diodes or a 74LS148 chip. Inspired by [Issue
      #32](https://github.com/bxparks/AceButton/issues/32).
* 1.3.5 (2019-08-11)
    * Verify library works on SAMD21 (Arduino Zero compatible) boards.
    * Reenable examples/CapacitiveButton on ESP8266 and ESP32.
      Looks like the development branch of the
      [CapacitiveSensor](https://github.com/PaulStoffregen/CapacitiveSensor)
      library added support for ESP32 in Dec 2018 but has not been released.
* 1.3.4 (2019-07-06)
    * Update compile-time checks for `HIGH` and `LOW` for compatibility with
      new megaAVR (e.g. Nano Every) boards which use enums instead of `#define`
      macros. Change value of `kButtonStatusUnknown` to 127 to avoid conflict
      with `PinStatus` enums.
    * Remove `ACE_BUTTON_INLINE` macros, was not doing anything.
    * Add `examples/ArrayButtons` to show how to define and initialize an array
      of AceButton instances.
    * Fix fqbn of ESP8266 after updating to ESP8266/Arduino Core 2.5.0.
* 1.3.3 (2019-03-10)
    * Add blurb about using `pinMode()` and button wiring configurations in
      README.md based on feedback from
      [Issue #19](https://github.com/bxparks/AceButton/issues/19).
    * Add `AceButton::isPressedRaw()` to determine the state of the button upon
      booting the device.
      (See [Issue #21](https://github.com/bxparks/AceButton/issues/21))
* 1.3.2 (2018-12-30)
    * Year-end maintenance release. No functional change.
    * Fix minor spelling and grammar mistakes in README.md.
    * Remove `virtual` when using `override` per C++ core style guide.
    * Update auniter.ini for compatibility with latest ESP32 and Sparkfun cores.
* 1.3.1 (2018-09-30)
    * Fix botched release on GitHub. Same as v1.3.
* 1.3 (2018-09-30)
    * Merge `AdjustableButtonConfig` into `ButtonConfig` and deprecated
      `AdjustableButtonConfig`. See
      [Issue #13](https://github.com/bxparks/AceButton/issues/13) for
      benchmarks which show that the theoretical increase of static RAM
      consumption does not often happen in practice because of compiler
      optimization.
    * Reduce default value of `getDebounceDelay()` from 50 ms to 20 ms
      to improve perceived responsiveness of buttons when they are rapidly
      pressed on and off. See
      [Issue #14](https://github.com/bxparks/AceButton/issues/14)
      for details.
    * Update `tests/auniter.ini` and `Jenkinsfile` for compatibility with
      AUniter v1.7. Add `CapacitiveSensor` to the exclude list for
      `env:esp8266` and `env:esp32` because it doesn't compile under those
      environments.
    * Remove leading zero in `ACE_BUTTON_VERSION` because that I forgot that it
      means an octal number.
* 1.2 (2018-08-14)
    * Add `AceButton(ButtonConfig*)` constructor to support constructor
      dependency injection. Recommended over `setButtonConfig()`.
      Should be 100% backwards compatible.
    * Add examples/CapacitiveSwitch program to demonstrate integration
      with CapacitiveSensor library to support capacitive switches.
    * Add continuous integration using AUniter/Jenkins.
* 1.1.1 (2018-06-21)
    * Fix compiler warnings about unused parameters in eventHandler callback.
    * Move AutoBenchmark results into AutoBenchmark/README.md.
    * Update various links in AceButton/README.md.
    * No functional or API change.
* 1.1.0 (2018-05-03)
    * Change to MIT License.
    * Add instrumentation of AceButton.check() using TimingStats to measure
      performance. (Fixes #9)
    * Add `examples/AutoBenchmark` sketch to auto-generate benchmarks for
      various microcontrollers.
    * Verify that library and examples compile, and the tests pass for ESP32.
    * Add a third method for distinguishing Clicked from DoubleClicked using
      both techniques described in 1.0.6.
* 1.0.6 (2018-03-25)
    * Add `kFeatureSuppressClickBeforeDoubleClick` flag to suppress
      Clicked event before a DoubleClicked event, at the cost of slower
      response time of the Clicked event. Added 2 more examples to demonstrate 2
      methods to distinguish between a Clicked and DoubleClicked.
    * Publish [doxygen docs](https://bxparks.github.io/AceButton/html/)
      on GitHub Pages.
* 1.0.5 (2018-03-17)
    * Migrate unit tests to [AUnit](https://github.com/bxparks/AUnit).
    * Fix various typos in README.md.
* 1.0.4 (2018-03-07)
    * Support ESP8266.
        * Split `loop()` in `Stopwatch.ino` into inner and outer loops, to
          allow `loop()` to return periodically.
        * Perform manual testing, since ArduinoUnit does not work on ESP8266.
    * Optimize `check()` so that `checkOrphanedClick()` is called only when
      needed.
    * README.md: add  benchmark numbers for ESP8266, fix typos.
    * Fix various compiler warnings about unused variables.
* 1.0.3 (2018-02-13)
    * Make library work on Teensy LC and 3.2.
        * Fix `elapsedTime` expression that breaks on 32-bit processors
          (whose `int` is 4 bytes instead of 2).
* 1.0.2 (2018-02-07)
    * Add documentation and unit tests for `AdjustableButtonConfig`.
    * Reduce `orphanClickDelay` to 1X `getDoubleClickDelay()` instead of 10X.
* 1.0.1 (2018-02-03)
    * Fix typo in 'library.properties'.
* 1.0.0 (2018-02-03)
    * Initial public release.
