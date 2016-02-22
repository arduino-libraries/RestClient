/* HueBlink example for HTTPClient library

   Uses HTTPClient library to control Philips Hue
   For more on Hue developer API see http://developer.meethue.com

  To control a light, the Hue expects a HTTP PUT request to:

  http://hue.hub.address/api/hueUserName/lights/lightNumber/state

  The body of the PUT request looks like this:
  {"on": true} or {"on":false}

  This example  shows how to concatenate Strings to assemble the
  PUT request and the body of the request.

  note: WiFi SSID and password are stored in config.h file.
  If it is not present, add a new tab, call it "config.h"
  and add the following variables:
  char ssid[] = "ssid";     //  your network SSID (name)
  char pass[] = "password"; // your network password

   modified 22 Feb 2016
   by Tom Igoe (tigoe) to match new API
*/

#include <SPI.h>
#include <WiFi101.h>
#include <HTTPClient.h>
#include "config.h"

int status = WL_IDLE_STATUS;      // the Wifi radio's status
char hueHubIP[] = "192.168.0.3";  // IP address of the HUE bridge
String hueUserName = "huebridgeusername"; // hue bridge username

// make a wifi instance and a HTTPClient instance:
WiFiClient wifi;
HTTPClient client = HTTPClient(wifi, hueHubIP);


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect.

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network IP = ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void loop() {
  sendRequest(3, "on", "true");   // turn light on
  delay(2000);                    // wait 2 seconds
  sendRequest(3, "on", "false");  // turn light off
  delay(2000);                    // wait 2 seconds
}

void sendRequest(int light, String cmd, String value) {
  // make a String for the HTTP request path:
  String request = "/api/" + hueUserName;
  request += "/lights/";
  request += light;
  request += "/state/";

  // make a string for the JSON command:
  String hueCmd = "{\"" + cmd;
  hueCmd += "\":";
  hueCmd += value;
  hueCmd += "}";
  // see what you assembled to send:
  Serial.print("PUT request to server: ");
  Serial.println(request);
  Serial.print("JSON command to server: ");

  // make the PUT request to the hub:
  int statusCode = client.put(request, hueCmd);
  Serial.println(hueCmd);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Server response: ");
  Serial.println(client.readResponse());
  Serial.println();
}
