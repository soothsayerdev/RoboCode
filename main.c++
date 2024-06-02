#include <Servo.h>

Servo motor;
int servoPin = 9; 

int trigPin = 10; 
int echoPin = 11; 
int buzzerPin = 8; 

void setup() {
  motor.attach(servoPin);
  pinMode(trigPin, OUTPUT); // Define pin TRIG has OUTPUT, because it sending a sinal
  pinMode(echoPin, INPUT); // Define pin ECHO has INPUT, because it receive the sinal, making it have a reaction
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  long duration, distance;

  // Send one pulse to TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Receive the pulse to the ECHO calculate the duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  if (distance < 20) { // If a obstacle has near (20 cm example)
    stopRobot(); // Stop the Robot
    sendSinal(); // Buzzer's sound
    Serial.println("Object has been detected, stoping robot."); // Message of debug
  } else {
    moveRobot(); // Move the Robot
    Serial.println("Nothing object has been detected, moving robot."); // Menssage of debug
  }
  delay(100); // Small delay to ensure stability
}

void moveRobot() {
  motor.write(90); // Move the servo (avance)
}

void stopRobot() {
  motor.write(0); // Move the servo to the position 0 (stoped)
}

void sendSinal() {
  tone(buzzerPin, 1000); // Emits a sound of 1000hz
  delay(1000); // Maintain sound 1 second
  noTone(buzzerPin); // Stop the sound
}
