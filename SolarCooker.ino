#include <Servo.h>

// Define servo pin
const int servoPin = 9;

// Define LDR pins
const int ldr1Pin = A0;
const int ldr2Pin = A1;
const int ldr3Pin = A2;

// Create servo object
Servo myservo;

// Define variables
int ldr1Val, ldr2Val, ldr3Val;
int referenceLDR, minLDR;
int position = 90; // Initial position of the servo (0-180 degrees)

void setup() {
  // Attach servo to pin
  myservo.attach(servoPin);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read LDR values
  ldr1Val = analogRead(ldr1Pin);
  ldr2Val = analogRead(ldr2Pin);
  ldr3Val = analogRead(ldr3Pin);

  // Find the LDR with the minimum reading (assuming higher light value means brighter)
  referenceLDR = max(ldr1Val, max(ldr2Val, ldr3Val));
  minLDR = min(ldr1Val, min(ldr2Val, ldr3Val));

  // Print readings for debugging purposes
  Serial.print("LDR 1: ");
  Serial.print(ldr1Val);
  Serial.print(", LDR 2: ");
  Serial.print(ldr2Val);
  Serial.print(", LDR 3: ");
  Serial.println(ldr3Val);

  // Check if the reference LDR is not the minimum (indicating the sun is not directly above it)
  if (referenceLDR != minLDR) {
    // Calculate the difference between the reference LDR and the minimum LDR
    int difference = referenceLDR - minLDR;

    // Adjust servo position based on the difference
    if (difference > 50) { // Adjust threshold value as needed
      position++; // Move servo clockwise
    } else if (difference < -50) {
      position--; // Move servo counter-clockwise
    }

    // Constrain servo position within range (0-180 degrees)
    position = constrain(position, 0, 180);

    // Move the servo to the new position
    myservo.write(position);
  }

  // Delay between readings
  delay(500);
}
