#include <Servo.h>  // Include the Servo library

Servo myServo;           // Create a Servo object

int rainSensorPin = A0;   // Pin connected to the rain sensor
int threshold = 500;      // Adjust this threshold based on your sensor's rain detection values
int servoPin = 9;         // Connect the signal wire of the servo to pin 9
bool clothStandInside = false;  // Track if the cloth stand is inside the shelter

void setup() {
  myServo.attach(servoPin);    // Attach the servo motor to pin 9
  Serial.begin(9600);          // Initialize serial communication for debugging
  pinMode(rainSensorPin, INPUT);
  myServo.write(0);            // Initial position (cloth stand outside the shelter)
}

void loop() {
  int sensorValue = analogRead(rainSensorPin); // Read the value from the rain sensor
  Serial.println(sensorValue);

  if (sensorValue > threshold && !clothStandInside) {  // If rain is detected and cloth stand is outside
    myServo.write(90);           // Move servo to bring cloth stand inside the shelter
    clothStandInside = true;     // Update position to inside shelter
    Serial.println("Rain detected - moving cloth stand inside shelter.");
  } 
  else if (sensorValue <= threshold && clothStandInside) {  // If no rain and cloth stand is inside
    myServo.write(0);            // Move servo to bring cloth stand outside the shelter
    clothStandInside = false;    // Update position to outside shelter
    Serial.println("No rain - moving cloth stand outside shelter.");
  }

  delay(1000);                   // Delay for stability
}
