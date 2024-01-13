#include <Adafruit_NeoPixel.h>

#define PIN 2    // Input-Pin which my WS2812B-Strip is connected to
#define NUMPIXELS 29 // Count of LEDs on your strip
#define PIR_PIN 13  // PIR-Sensor-Pin

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool devMode = true; // determines wheter the strip waits for 
int delayval = 50; // delay in ms between color switch of the single LEDs

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  pixels.begin(); // Initialize NeoPixel-Library
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
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      }
      pixels.show();
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
        pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
        pixels.show();
        delay(delayval);
    }
  }
  
}
