#include <Adafruit_NeoPixel.h>
#include <LowPower.h>

#define PINS1 2    // Input-Pin to which the first WS2812B-Strip is connected
#define PINS2 3    // Input-Pin to which the second WS2812B-Strip is connected
#define NUMPIXELS 22 // Count of LEDs on your strip
#define PIR_PIN 13  // PIR-Sensor-Pin

Adafruit_NeoPixel Strip1 = Adafruit_NeoPixel(NUMPIXELS, PINS1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Strip2 = Adafruit_NeoPixel(NUMPIXELS, PINS2, NEO_GRB + NEO_KHZ800);

bool devMode = false; // determines whether the strip waits for 
int delayval = 50;    // delay in ms between color switch of the single LEDs

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

volatile bool motionDetected = false;  // Flag to indicate motion detection

void setup() {
  Strip1.begin(); // Initialize the first LED Strip
  Strip2.begin(); // Initialize the second LED Strip
  pinMode(PIR_PIN, INPUT); // Set PIR-Sensor as input

  // Attach an interrupt to the PIR_PIN that sets the motionDetected flag
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), motionInterrupt, CHANGE);
}

void loop() {
  // Check for devMode
  if (devMode != true) {
    // Check the PIR-Sensor status
    if (motionDetected) {
      // If PIR-Sensor is active, turn on the LEDs and start the color change
      changeColor();
      motionDetected = false;  // Reset the flag after motion is detected
    } else {
      // If PIR-Sensor isn't active, go to sleep
      goToSleep();
    }
  } else {
    changeColor();
  }
}

void goToSleep() {
  // Turn off both LED Strips before sleeping
  for (int i = 0; i < NUMPIXELS; i++) {
    turnOff(i);
  }
  show();

  // Enter sleep mode
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
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

// Interrupt service routine for motion detection
void motionInterrupt() {
  motionDetected = true;
}
