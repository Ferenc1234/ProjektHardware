#include <Arduino.h>
#include <jc_button.h>
#include <Bounce2.h>


const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Array of LED pins
const int controlLED = 13; // Control LED pin
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Number of LEDs
const int pot = A1; // Potentiometer pin
Bounce2::Button button = Bounce2::Button(); // INSTANTIATE A Bounce2::Button OBJECT



void setup() {
  for (int i = 0; i < 10; i++)
  {
    pinMode(ledPins[i], OUTPUT); 
  }
  Serial.begin(9600); // Initialize serial communication at 9600 bps
  button.attach ( 12 , INPUT_PULLUP ); // Attach the button to pin 7 with internal pull-up resistor
  button.interval( 5 );
  button.setPressedState( LOW ); // Set the pressed state to LOW
}

void fce1() {
  static unsigned int test = 0;
  if (millis() % 100 > 90){
    test++;
  }
  

}

void fce2() {
  static unsigned long lastMillis = 0; // Variable to store the last time the LED was toggled
}

void fce3() {
  static unsigned long lastMillis = 0; // Variable to store the last time the LED was toggled
}

void fce4() {
}


void loop() {
  static int mode = 0; // Variable to store the current LED index
  button.update(); // Update the button state
  
  if (button.pressed()) { // Check if the button is pressed
    Serial.println("button pressed"); // Print message to serial monitor
    mode++; // Increment the mode variable
  } 

  switch (mode) {
    case 0:
      Serial.println("1");
      fce1();
      break;
    case 1:
    Serial.println("2");

      break;
    case 2:
    Serial.println("3");

      break;
    case 3:
    Serial.println("4");

      break;
    case 4:
    Serial.println("reset");

      mode = 0; // Reset mode to 0 if it exceeds the number of cases
      break;
  }
}