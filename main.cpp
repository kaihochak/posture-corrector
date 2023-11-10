// this constant won't change. It's the pin number of the sensor's output:
const int pingPin = 7;
const int buzzerPin = 10;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT); 
  
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  
  // trigger the buzzer when the distance is over 20cm
  if (cm > 200) {
    Serial.print("ass is buzzing: \n");
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    delay(1000);                   // Wait for 1 second
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
    delay(1000);                   // Wait for 1 second
  } else {
    Serial.print("not buzzing: \n");
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
    delay(1000);                   // Wait for 1 second
  }
  	
  // printing distance
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}