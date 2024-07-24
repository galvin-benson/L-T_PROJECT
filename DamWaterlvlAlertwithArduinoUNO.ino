int inches = 0;
int cm = 0;
int dist = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Measuring the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(9, 10);
  inches = (cm / 2.54);
  if (cm < 15) {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  }
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");
  delay(10);
}