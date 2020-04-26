/*
 * A program that prints out the time (min/avg/max) taken by the
 * AceButton::check() method.
 */

#include <AceButton.h>
#include "ProfilingButtonConfig.h"
using namespace ace_button;

#if defined(ESP32) && !defined(SERIAL_PORT_MONITOR)
#define SERIAL_PORT_MONITOR Serial
#endif

// The pin number attached to the button.
const int BUTTON_PIN = 2;

ProfilingButtonConfig buttonConfig;

// One button wired using the ProfilingButtonConfig.
AceButton button(&buttonConfig);

const unsigned long STATS_PRINT_INTERVAL = 2000;
TimingStats stats;

const uint8_t LOOP_MODE_START = 0;
const uint8_t LOOP_MODE_IDLE = 1;
const uint8_t LOOP_MODE_PRESS_RELEASE = 2;
const uint8_t LOOP_MODE_CLICK = 3;
const uint8_t LOOP_MODE_DOUBLE_CLICK = 4;
const uint8_t LOOP_MODE_LONG_PRESS = 5;
const uint8_t LOOP_MODE_END = 6;
uint8_t loopMode;
uint8_t loopEventType;

void handleEvent(AceButton*, uint8_t, uint8_t);

void setup() {
  delay(1000); // some microcontrollers reboot twice
  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // wait until ready - Leonardo/Micro
  SERIAL_PORT_MONITOR.println(F("setup(): begin"));

  // Print sizeof various classes
  SERIAL_PORT_MONITOR.print(F("sizeof(AceButton): "));
  SERIAL_PORT_MONITOR.println(sizeof(AceButton));

  SERIAL_PORT_MONITOR.print(F("sizeof(ButtonConfig): "));
  SERIAL_PORT_MONITOR.println(sizeof(ButtonConfig));

  SERIAL_PORT_MONITOR.print(F("sizeof(Encoded4To2ButtonConfig): "));
  SERIAL_PORT_MONITOR.println(sizeof(Encoded4To2ButtonConfig));

  SERIAL_PORT_MONITOR.print(F("sizeof(Encoded8To3ButtonConfig): "));
  SERIAL_PORT_MONITOR.println(sizeof(Encoded8To3ButtonConfig));

  SERIAL_PORT_MONITOR.print(F("sizeof(EncodedButtonConfig): "));
  SERIAL_PORT_MONITOR.println(sizeof(EncodedButtonConfig));

  // Button uses the built-in pull up register.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button.init(BUTTON_PIN);

  // Configure the ButtonConfig with the event handler, and enable all higher
  // level events.
  buttonConfig.setEventHandler(handleEvent);
  buttonConfig.setFeature(ButtonConfig::kFeatureClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig.setFeature(ButtonConfig::kFeatureRepeatPress);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAll);
  buttonConfig.setTimingStats(&stats);

  loopMode = LOOP_MODE_START;
  loopEventType = AceButton::kEventPressed;

  SERIAL_PORT_MONITOR.println(F("setup(): end"));
}

void loop() {
  delay(1); // Decrease sampling frequency to about 1000 Hz
  button.check();

  switch (loopMode) {
    case LOOP_MODE_START:
      loopStart();
      break;
    case LOOP_MODE_IDLE:
      loopIdle();
      break;
    case LOOP_MODE_PRESS_RELEASE:
      loopPressRelease();
      break;
    case LOOP_MODE_CLICK:
      loopClick();
      break;
    case LOOP_MODE_DOUBLE_CLICK:
      loopDoubleClick();
      break;
    case LOOP_MODE_LONG_PRESS:
      loopLongPress();
      break;
    case LOOP_MODE_END:
      loopEnd();
      break;
  }
}

void loopStart() {
  static unsigned long start = millis();

  // Wait one iteration for things to cool down.
  if (millis() - start > STATS_PRINT_INTERVAL) {
    SERIAL_PORT_MONITOR.println(
        F("------------------------+-------------+---------+"));
    SERIAL_PORT_MONITOR.println(
        F("button event            | min/avg/max | samples |"));
    SERIAL_PORT_MONITOR.println(
        F("------------------------+-------------+---------+"));
    nextMode();
  }
}

void loopEnd() {
  SERIAL_PORT_MONITOR.println(
      F("------------------------+-------------+---------+"));
  nextMode();
}

void loopIdle() {
  static unsigned long start = millis();

  if (millis() - start > STATS_PRINT_INTERVAL) {
    SERIAL_PORT_MONITOR.print(F("idle                    | "));
    printStats();
    SERIAL_PORT_MONITOR.println(F("    |"));
    nextMode();
  }
}

void loopPressRelease() {
  static unsigned long start = millis();

  unsigned long now = millis();
  unsigned long elapsed = now - start;
  if (100 <= elapsed && elapsed < 1000) buttonConfig.setButtonState(LOW);
  if (1000 <= elapsed) buttonConfig.setButtonState(HIGH);

  if (millis() - start > STATS_PRINT_INTERVAL) {
    if (loopEventType == AceButton::kEventReleased) {
      SERIAL_PORT_MONITOR.print(F("press/release           | "));
      printStats();
      SERIAL_PORT_MONITOR.println(F("    |"));
    }
    nextMode();
  }
}

void loopClick() {
  static unsigned long start = millis();

  unsigned long now = millis();
  unsigned long elapsed = now - start;
  if (100 <= elapsed && elapsed < 200) buttonConfig.setButtonState(LOW);
  if (200 <= elapsed) buttonConfig.setButtonState(HIGH);

  if (millis() - start > STATS_PRINT_INTERVAL) {
    if (loopEventType == AceButton::kEventClicked) {
      SERIAL_PORT_MONITOR.print(F("click                   | "));
      printStats();
      SERIAL_PORT_MONITOR.println(F("    |"));
    }
    nextMode();
  }
}

void loopDoubleClick() {
  static unsigned long start = millis();

  unsigned long now = millis();
  unsigned long elapsed = now - start;
  if (100 <= elapsed && elapsed < 200) buttonConfig.setButtonState(LOW);
  if (200 <= elapsed && elapsed < 300) buttonConfig.setButtonState(HIGH);
  if (300 <= elapsed && elapsed < 400) buttonConfig.setButtonState(LOW);
  if (400 <= elapsed) buttonConfig.setButtonState(HIGH);

  if (millis() - start > STATS_PRINT_INTERVAL) {
    if (loopEventType == AceButton::kEventDoubleClicked) {
      SERIAL_PORT_MONITOR.print(F("double click            | "));
      printStats();
      SERIAL_PORT_MONITOR.println(F("    |"));
    }
    nextMode();
  }
}

void loopLongPress() {
  static unsigned long start = millis();

  unsigned long now = millis();
  unsigned long elapsed = now - start;
  if (100 <= elapsed) buttonConfig.setButtonState(LOW);

  if (millis() - start > STATS_PRINT_INTERVAL) {
    if (loopEventType == AceButton::kEventRepeatPressed) {
      SERIAL_PORT_MONITOR.print(F("long press/repeat press | "));
      printStats();
      SERIAL_PORT_MONITOR.println(F("    |"));
    }
    nextMode();
  }
}

void nextMode() {
  stats.reset();
  buttonConfig.setButtonState(HIGH);
  loopMode++;
}

void printStats() {
  printInt(stats.getMin());
  SERIAL_PORT_MONITOR.print('/');
  printInt(stats.getAvg());
  SERIAL_PORT_MONITOR.print('/');
  printInt(stats.getMax());
  SERIAL_PORT_MONITOR.print(F(" | "));
  printInt(stats.getCount());
}

// print integer within 3 characters, padded on left with spaces
void printInt(uint16_t i) {
  if (i < 100) SERIAL_PORT_MONITOR.print(' ');
  if (i < 10) SERIAL_PORT_MONITOR.print(' ');
  SERIAL_PORT_MONITOR.print(i);
}

// An empty event handler.
void handleEvent(AceButton* /* button */, uint8_t eventType,
    uint8_t /* buttonState */) {
  loopEventType = eventType;
}
