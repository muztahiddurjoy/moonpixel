// MoonPixel - moon lamp firmware
// Board: ESP32-C3 SuperMini   LEDs: WS2812 4-bit (2x2) panel
//
// Wiring:
//   Panel VCC  -> 5V (VBUS) pin on the SuperMini
//   Panel GND  -> GND
//   Panel DIN  -> GPIO 10 (through a 330 ohm resistor)
//
// Starter sketch: a slow, soft rainbow so you can check that every LED works.

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

constexpr uint8_t LED_PIN = 10;     // data pin to the WS2812 panel
constexpr uint8_t LED_COUNT = 4;    // 2x2 panel
constexpr uint8_t BRIGHTNESS = 80;  // 0-255; keep it modest, the panel gets warm

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();
  pixels.show();
  Serial.println("MoonPixel started");
}

void loop() {
  static uint16_t hue = 0;

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    // spread the 4 LEDs a little apart on the colour wheel
    uint16_t pixelHue = hue + (i * 65536UL / (LED_COUNT * 4));
    pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
  }
  pixels.show();

  hue += 64;
  delay(20);
}
