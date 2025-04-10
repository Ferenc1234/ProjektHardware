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
  button.attach ( 14 , INPUT_PULLUP ); // Attach the button to pin 7 with internal pull-up resistor
  button.interval( 5 );
  button.setPressedState( LOW ); // Set the pressed state to LOW
}

void fce1() {
  static unsigned long lastMillis = 0; // Variable to store the last time the LED was toggled
  for (int i = 0; i < 10;)
  {
    digitalWrite(ledPins[i], HIGH); // Turn on the LED
    if (lastMillis >= 100) {
      digitalWrite(ledPins[i], LOW); // Turn off the LED
      i++;
    }
  }
  
}

void fce2() {
  static unsigned long lastMillis = 0; // Variable to store the last time the LED was toggled
  for (int i = 10; i > 0;)
  {
    digitalWrite(ledPins[i], HIGH); // Turn on the LED
    if (lastMillis >= 100) {
      digitalWrite(ledPins[i], LOW); // Turn off the LED
      i--;
    }
  }
}

void fce3() {
  static unsigned long lastMillis = 0; // Variable to store the last time the LED was toggled
  const int blinkInterval = 100; // Interval for faster blinking in milliseconds
  static bool ledState = false; // Variable to store the LED state

  if (millis() - lastMillis >= blinkInterval) {
    ledState = !ledState; // Toggle the LED state
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(ledPins[i], ledState); // Set the LED state
    }
    lastMillis = millis(); // Update the lastMillis variable
  }
}

void fce4() {
  int potValue = analogRead(pot); // Range: 0 - 1023
  int numLedsOn = map(potValue, 0, 1023, 1, 10);

  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], i < numLedsOn ? HIGH : LOW);
  }
}


void loop() {
  static int mode = 0; // Variable to store the current LED index
  switch (mode) {
    case 0:
      fce1(); // Call the function to update the LEDs
      break;
    case 1:
      fce2(); // Call the function to blink the control LED
      break;
    case 2:
      fce3(); // Call the function to blink the control LED faster
      break;
    case 3:
      fce4(); // Call the function to turn off the control LED
      break;
    default:
      mode = 0; // Reset mode to 0 if it exceeds the number of cases
      break;
  }
  button.update(); // Update the button state
  if (button.pressed()) { // Check if the button is pressed
    Serial.println("button pressed"); // Print message to serial monitor
    mode++; // Increment the mode variable
  } 
  
}