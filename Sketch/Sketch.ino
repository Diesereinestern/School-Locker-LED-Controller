#include <Adafruit_NeoPixel.h>

#define PINS1 2    // Input-Pin which my first WS2812B-Strip is connected to
#define PINS2 3    // Input-Pin which my second WS2812B-Strip is connected to
#define NUMPIXELS 22 // Count of LEDs on your strip
#define PIR_PIN 13  // PIR-Sensor-Pin

Adafruit_NeoPixel Strip1 = Adafruit_NeoPixel(NUMPIXELS, PINS1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Strip2 = Adafruit_NeoPixel(NUMPIXELS, PINS2, NEO_GRB + NEO_KHZ800);

bool devMode = false; // determines wheter the strip waits for 
int delayval = 50; // delay in ms between color switch of the single LEDs

int redColor = 0;
int greenColor = 0;
int blueColor = 0;
 
void setup() {
  Strip1.begin(); // Initialize the first LED Strip
  Strip2.begin(); // Initialize the second LED Strip
  pinMode(PIR_PIN, INPUT); // Set PIR-Sensor as input
}

void loop() {
  // Check for devMode
  if(devMode != true) {
    // Check the PIR-Sensors status
    if (digitalRead(PIR_PIN) == HIGH) {
      // If PIR-Sensor is active, turn on the LEDs and start the color change
      changeColor();
    
    } else {
      // If PIR-Sensor isn't active, shut off all LEDs
      for (int i = 0; i < NUMPIXELS; i++) {
        // Turn off all LEDs
        turnOff(i);
      }
      // Update LEDs to turn them off
      show();
    }
  } else {
    changeColor();
  }
}

// Chooses random value for colors
void setColor() {
  redColor = random(0, 256);
  greenColor = random(0, 256);
  blueColor = random(0, 256);
}

// The process of changing the LEDs color in a wave
void changeColor() {
  for (int i = 0; i <= 25; i++) {
    setColor();
    for (int i = 0; i < NUMPIXELS; i++) {
        Strip1.setPixelColor(i, Strip1.Color(redColor, greenColor, blueColor));
        Strip2.setPixelColor(i, Strip2.Color(redColor, greenColor, blueColor));
        // Show colors
        show();
        delay(delayval);
    }
  } 
}

// Turns off both LED Strips
void turnOff(int i) {
  Strip1.setPixelColor(i, Strip1.Color(0, 0, 0));
  Strip2.setPixelColor(i, Strip2.Color(0, 0, 0));
}

// Updates the strip's state
void show() {
  Strip1.show();
  Strip2.show();
}