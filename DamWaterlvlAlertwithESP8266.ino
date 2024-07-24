#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const int trigPin1 = 13;
const int echoPin1 = 15;
#define redled 12
#define grnled 14
unsigned long ch_no = 2604200;//Replace with Thingspeak Channel number
const char * write_api = "URPTAF31GLC8S2CG";//Replace with Thingspeak write API
char auth[] = "mwa0000034478770";
char ssid[] = "Galvin’s iPhone";
char pass[] = "GalvinBenson";
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;
WiFiClient  client;
long duration1;
int distance1;
void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(redled, OUTPUT);
  pinMode(grnled, OUTPUT);
  digitalWrite(redled, LOW);
  digitalWrite(grnled, LOW);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  startMillis = millis();  //initial start time
}
void loop()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.print(distance1);
  Serial.println(" cm");
  if (distance1 <= 10)
  {
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
  }
  else
  {
    digitalWrite(14, HIGH);
    digitalWrite(12, LOW);
  }
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    ThingSpeak.setField(1, distance1);
    ThingSpeak.writeFields(ch_no, write_api);
    startMillis = currentMillis;
  }
}