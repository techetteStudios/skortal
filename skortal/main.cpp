#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1 6
#define PIN2 7
#define PIN3 8
#define PIN4 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip_a = Adafruit_NeoPixel(60, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_b = Adafruit_NeoPixel(60, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_c = Adafruit_NeoPixel(60, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_d = Adafruit_NeoPixel(60, PIN4, NEO_GRB + NEO_KHZ800);

//Only need to declare colors for one strip, can be used for all strips
uint32_t l1_color = strip_a.Color(200, 200, 0); // Yellow
uint32_t l2_color = strip_a.Color(200, 90, 10); // Light Orange
uint32_t l3_color = strip_a.Color(255, 100, 0); // Orange
uint32_t l4_color = strip_a.Color(255, 0, 0); // Red
uint32_t l5_color = strip_a.Color(255, 0, 100); // Magenta
uint32_t l6_color = strip_a.Color(200, 0, 150); // Pink
uint32_t l7_color = strip_a.Color(210, 0, 100); // Light Purple
uint32_t l8_color = strip_a.Color(100, 0, 255); // Purple
uint32_t enl_color = strip_a.Color(0, 255, 0); // Green
uint32_t res_color = strip_a.Color(0, 0, 55); // Blue
uint32_t neu_color = strip_a.Color(255, 0, 0); // Red
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
    strip_a.begin();
    strip_a.show(); // Initialize all pixels to 'off'
    strip_b.begin();
    strip_b.show(); // Initialize all pixels to 'off'
    strip_c.begin();
    strip_c.show(); // Initialize all pixels to 'off'
    strip_d.begin();
    strip_d.show(); // Initialize all pixels to 'off'
}

void loop() {
    colorWipe(l1_color, 10); // Yellow
    colorWipe(l2_color, 10); // Light Orange
    colorWipe(l3_color, 10); // Orange
    colorWipe(l4_color, 10); // Red
    colorWipe(l5_color, 10); // Magenta
    colorWipe(l6_color, 10); // Pink
    colorWipe(l7_color, 10); // Light Purple
    colorWipe(l8_color, 10); // Purple
    colorWipe(enl_color, 10); // Green
    colorWipe(res_color, 10); // Blue
    colorWipe(neu_color, 10); // Red
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip_a.numPixels(); i++) {
        strip_a.setPixelColor(i, c);
        strip_b.setPixelColor(i, c);
        strip_c.setPixelColor(i, c);
        strip_d.setPixelColor(i, c);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        delay(wait);
    }

}