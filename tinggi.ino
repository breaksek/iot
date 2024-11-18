#include <HCSR04.h>

#define TRIGGER_PIN 15
#define ECHO_PIN 13

int LED_RED = 23;
int LED_GREEN = 22;

UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);

#include <ESP8266WiFi.h>

String ClientRequests;
String myresultat;
WiFiServer server(80);
WiFiClient client;

IPAddress staticIP414_111(192,168,155,117);
IPAddress gateway414_111(192,168,155,1);
IPAddress subnet414_111(255,255,255,0);

String ReadIncomingRequests(){
  while(client.available()) {
    ClientRequests = (client.readStringUntil('\r'));
    if ((ClientRequests.indexOf("HTTP/1.1")>0)&&(ClientRequests.indexOf("/favicon.ico")<0)){
      myresultat = ClientRequests;
    }
  }
  return myresultat;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  ClientRequests = "";
  WiFi.disconnect();
  delay(300);
  Serial.println("START");

  WiFi.begin("another","hah apah");

  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(3000);
    Serial.println("..");
  }
  Serial.println("Connected");
  WiFi.config(staticIP414_111, gateway414_111, subnet414_111);
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);

  unsigned int jarak = distanceSensor.measureDistanceCm();

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  int tinggiSensor = 200;
  int tinggiBadan = tinggiSensor - jarak;

  Serial.print("Tinggi Badan: ");
  Serial.print(tinggiBadan);
  Serial.println(" cm");

  if (tinggiBadan < 175){
    Serial.print("Keterangan: ");
    Serial.print("TIDAK LULUS");
    Serial.println();
    Serial.println();
    digitalWrite(LED_RED, HIGH);
    delay(100);
  }else{
    Serial.print("Keterangan: ");
    Serial.print("LULUS");
    Serial.println();
    Serial.println();
    digitalWrite(LED_GREEN, HIGH);
    delay(100);
  }

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  delay(50);

  client = server.available();
  ClientRequests = (ReadIncomingRequests());
  ClientRequests.remove(0, 5);
  ClientRequests.remove(ClientRequests.length()-9,9);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println(jarak);
  client.stop();
  delay(100);
  client.flush();
}
