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
uint32_t l2_color = strip_a.Color(170, 90, 10); // Light Orange
uint32_t l3_color = strip_a.Color(255, 40, 0); // Orange
uint32_t l4_color = strip_a.Color(255, 0, 0); // Red
uint32_t l5_color = strip_a.Color(255, 0, 40); // Magenta
uint32_t l6_color = strip_a.Color(200, 0, 150); // Pink
uint32_t l7_color = strip_a.Color(100, 0, 230); // Light Purple
uint32_t l8_color = strip_a.Color(30, 0, 255); // Purple
uint32_t enl_color = strip_a.Color(0, 255, 0); // Green
uint32_t res_color = strip_a.Color(0, 0, 55); // Blue
uint32_t neu_color = strip_a.Color(255, 0, 0); // Red
uint32_t off_color = strip_a.Color(0, 0, 0); // No Color

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

char faction = 'R';
uint32_t slot_1_color = strip_a.Color(255, 0, 0);
uint32_t slot_2_color = strip_a.Color(255, 0, 0);
uint32_t slot_3_color = strip_a.Color(255, 0, 0);
uint32_t slot_4_color = strip_a.Color(255, 0, 0);
uint32_t slot_5_color = strip_a.Color(255, 0, 0);
uint32_t slot_6_color = strip_a.Color(255, 0, 0);
uint32_t slot_7_color = strip_a.Color(255, 0, 0);
uint32_t slot_8_color = strip_a.Color(255, 0, 0);

//Resonator level (1=weakest, 8=strongest)
uint16_t slot_1_level = 8;
uint16_t slot_2_level = 7;
uint16_t slot_3_level = 6;
uint16_t slot_4_level = 5;
uint16_t slot_5_level = 4;
uint16_t slot_6_level = 3;
uint16_t slot_7_level = 2;
uint16_t slot_8_level = 1;

//Resonator Strength (1=weakest, 7=strongest)
uint16_t slot_1_power = 6;
uint16_t slot_2_power = 6;
uint16_t slot_3_power = 6;
uint16_t slot_4_power = 0;
uint16_t slot_5_power = 6;
uint16_t slot_6_power = 6;
uint16_t slot_7_power = 6;
uint16_t slot_8_power = 6;

String input = "";


void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // send an intro:
    Serial.println("\n\nString toInt():");
    Serial.println();

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
    while (Serial.available() > 0) {
        int inChar = Serial.read();

        if (inChar == '\n') {
            readInput();
            checkIfNeutral();
            setFaction();
            setLevel();
            delay(10000);
        }
        else
        {
            input += (char) inChar;
        }
    }
}

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip->numPixels(); i++) {
        strip->setPixelColor(i, c);
        strip->show();
        delay(wait);
    }
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
                strip->setPixelColor(i+q, c);    //turn every third pixel on
            }
            strip->show();

            delay(wait);

            for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
                strip->setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

//If portal is neutral, set all 1st light to red and do theater-chase red on rest
void readInput() {

    faction = (input[0])? input[0]:'N';

    //subtracting '0', uses ascii and converts string char to int char
     slot_1_level = (input[1])? input[1]-'0': 0;
     slot_2_level = (input[2])? input[2]-'0': 0;
     slot_3_level = (input[3])? input[3]-'0': 0;
     slot_4_level = (input[4])? input[4]-'0': 0;
     slot_5_level = (input[5])? input[5]-'0': 0;
     slot_6_level = (input[6])? input[6]-'0': 0;
     slot_7_level = (input[7])? input[7]-'0': 0;
     slot_8_level = (input[8])? input[8]-'0': 0;
     slot_1_power = (input[9])? input[9]-'0': 0;
     slot_2_power = (input[10])? input[10]-'0': 0;
     slot_3_power = (input[11])? input[11]-'0': 0;
     slot_4_power = (input[12])? input[12]-'0': 0;
     slot_5_power = (input[13])? input[13]-'0': 0;
     slot_6_power = (input[14])? input[14]-'0': 0;
     slot_7_power = (input[15])? input[15]-'0': 0;
     slot_8_power = (input[16])? input[16]-'0': 0;
    uint32_t final = slot_1_level + slot_2_level + slot_3_level + slot_4_level + slot_5_level + slot_6_level + slot_7_level + slot_8_level;
    uint32_t final2 = slot_1_power + slot_2_power + slot_3_power + slot_4_power + slot_5_power + slot_6_power + slot_7_power + slot_8_power;
    Serial.print("Data:");Serial.print(slot_1_level);Serial.print(" ");Serial.println(slot_2_level);Serial.print(" ");Serial.println(slot_3_level);Serial.print(" ");Serial.println(slot_4_level);Serial.print(" ");Serial.println(slot_5_level);Serial.print(" ");Serial.println(slot_6_level);Serial.print(" ");Serial.println(slot_7_level);Serial.print(" ");Serial.println(slot_8_level);
    Serial.print("Data:");Serial.print(slot_1_power);Serial.print(" ");Serial.println(slot_2_power);Serial.print(" ");Serial.println(slot_3_power);Serial.print(" ");Serial.println(slot_4_power);Serial.print(" ");Serial.println(slot_5_power);Serial.print(" ");Serial.println(slot_6_power);Serial.print(" ");Serial.println(slot_7_power);Serial.print(" ");Serial.println(slot_8_power);
    Serial.print("Value:");Serial.print(final);Serial.print(" ");Serial.println(final2);
    Serial.print("String: ");Serial.println(input);
    input = "";
}

//If portal is neutral, set all 1st light to red and do theater-chase red on rest
void checkIfNeutral() {
    if(faction == 'N')
    {
        colorWipe(&strip_a, neu_color, 10);
        colorWipe(&strip_b, neu_color, 10);
        colorWipe(&strip_c, neu_color, 10);
        colorWipe(&strip_d, neu_color, 10);
        theaterChase(&strip_a, off_color, 10);
        theaterChase(&strip_b, off_color, 10);
        theaterChase(&strip_c, off_color, 10);
        theaterChase(&strip_d, off_color, 10);
        theaterChase(&strip_a, neu_color, 20);
        theaterChase(&strip_b, neu_color, 20);
        theaterChase(&strip_c, neu_color, 20);
        theaterChase(&strip_d, neu_color, 20);

    }
}

// Set Designated Faction Indicator Light
void setFaction() {
    if(faction == 'N')
    {
        // Portal is not owned, exit function
        return;
    }
    if(faction == 'E')
    {
        // Portal is ENL owned, 1st light is green
        setFirstLight(&strip_a, enl_color);
        setFirstLight(&strip_b, enl_color);
        setFirstLight(&strip_c, enl_color);
        setFirstLight(&strip_d, enl_color);
    }
    else if(faction == 'R')
    {
        // Portal is RES owned, 1st light is blue
        setFirstLight(&strip_a, res_color);
        setFirstLight(&strip_b, res_color);
        setFirstLight(&strip_c, res_color);
        setFirstLight(&strip_d, res_color);
    }
    strip_a.show();
    strip_b.show();
    strip_c.show();
    strip_d.show();
}
void setFirstLight(Adafruit_NeoPixel *strip, uint32_t c) {
    //TODO if empty slot, don't show lights
    strip->setPixelColor(0, c);
    strip->setPixelColor(15, c); // flipped due to orientation on skirt
}

//Set Resonator Level/Strength
void setLevel() {
    if(faction == 'N')
    {
        // Portal is not owned, exit function
        return;
    }

    clearAll();

    setStrip(&strip_a, slot_1_level, slot_1_power, slot_2_level, slot_2_power, 20);
    setStrip(&strip_b, slot_3_level, slot_3_power, slot_4_level, slot_4_power, 30);
    setStrip(&strip_c, slot_5_level, slot_5_power, slot_6_level, slot_6_power, 40);
    setStrip(&strip_d, slot_7_level, slot_7_power, slot_8_level, slot_8_power, 50);
}

void setStrip(Adafruit_NeoPixel *strip, uint16_t strip_1_lvl, uint16_t strip_1_pwr, uint16_t strip_2_lvl, uint16_t strip_2_pwr, uint8_t wait)
{
    //First slot of strip
    uint32_t level_color = determineColor(strip_1_lvl);
    uint32_t numOfLights = strip_1_pwr+1;
    for(uint16_t i=1; i<numOfLights; i++) {
        strip->setPixelColor(i, level_color);
        strip->show();
        delay(wait);
    }

    //Second slot of strip
    // flipped due to orientation on skirt
    level_color = determineColor(strip_2_lvl);
    numOfLights = 14-strip_2_pwr;
    for(uint16_t j=14; j>numOfLights; j--) {
        strip->setPixelColor(j, level_color);
        strip->show();
        delay(wait);
    }
}

uint32_t determineColor(uint16_t level){
    uint32_t color;
    switch (level) {
        case 1:
            color = l1_color;
            break;
        case 2:
            color = l2_color;
            break;
        case 3:
            color = l3_color;
            break;
        case 4:
            color = l4_color;
            break;
        case 5:
            color = l5_color;
            break;
        case 6:
            color = l6_color;
            break;
        case 7:
            color = l7_color;
            break;
        case 8:
            color = l8_color;
            break;
        default:
            // if nothing else matches, do the default
            color = neu_color;
            break;
    }
    return color;
}

void clearAll(){
    for(uint16_t i=1; i<7; i++) {
        strip_a.setPixelColor(i, off_color);
        strip_b.setPixelColor(i, off_color);
        strip_c.setPixelColor(i, off_color);
        strip_d.setPixelColor(i, off_color);
    }
    for(uint16_t j=14; j>7; j--) {
        strip_a.setPixelColor(j, off_color);
        strip_b.setPixelColor(j, off_color);
        strip_c.setPixelColor(j, off_color);
        strip_d.setPixelColor(j, off_color);
    }
}