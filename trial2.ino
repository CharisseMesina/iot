#include <ESP8266WiFi.h>
 
const char* ssid = "wifi point";
const char* password = "elison t";
WiFiServer server(80);

byte sensorPin[] = {14, 12, 13};
const byte sensors = 3;
int level = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  for (int i = 0; i < sensors; i++) {
    pinMode(sensorPin[i], INPUT);
  }

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  level = 0;

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  for (int i = 0; i < sensors; i++) {
    if (digitalRead(sensorPin[i]) == LOW) {
      level = sensors - i;
    } else {

    }
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one


switch (level)

  {

    case 1:

      client.print("AVERAGE");

      break;

    case 2:

     client.print("LOW");

      break;

    case 3:

      client.print("HIGH");

      break;

    default:

      client.print("NO WATER");

      break;

  }

  delay(50);

}

 /* if (level == 1) {
    client.print("HIGH");
  } 
  if (level == 2) {
    client.print("AVERAGE");
  }
  if (level == 3) {
    client.print("LOW");
  }else{
    client.print("NO WATER DETECTED");
  }*/



