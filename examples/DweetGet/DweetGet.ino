/*
  Dweet.io GET client for RestClient library
  Connects to dweet.io once every ten seconds,
  sends a GET request and a request body. Uses SSL

  Shows how to use Strings to assemble path. dweet.io expects:
  https://dweet.io/get/latest/dweet/for/thingName

For more on dweet.io, see https://dweet.io/play/

  note: WiFi SSID and password are stored in config.h file.
  If it is not present, add a new tab, call it "config.h"
  and add the following variables:
  char ssid[] = "ssid";     //  your network SSID (name)
  char pass[] = "password"; // your network password

  created 15 Feb 2016
  by Tom Igoe

  this example is in the public domain
*/
#include <RestClient.h>
#include <WiFi101.h>
#include "config.h"

char serverAddress[] = "dweet.io";  // server address
int port = 80;
String dweetName = "my-thing-name"; // use your own thing name here

WiFiClient wifi;
RestClient client = RestClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;
String response;
int statusCode = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);     // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  // assemble the path for the POST message:
  String path = "/get/latest/dweet/for/" + dweetName;

  // assemble the body of the POST message:
  int sensorValue = analogRead(A0);

  Serial.println("making GET request");
  client.setContentType("application/json");
  statusCode = client.get(path);
  response = client.readResponse();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait ten seconds\n");
  delay(10000);
}
