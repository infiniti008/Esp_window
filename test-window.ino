#include "Motor.h"
#include "Page.h"
#include "Handle.h"
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>


Motor motor(D2, D5, D6, D1);

//String home_page;

const char* ssid     = "slava_asus";
const char* password = "19111990";
ESP8266WebServer server(80);

void setup() {
  // Start Serial
  Serial.begin(9600);

  Serial.println("\nESP Window-controll Server\n");

  // Connect to your WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

// Handle http requests
  server.on("/", Handle_home_page);
  server.on("/on", fd);
  server.on("/get_time", Handle_get_time);
  
  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Listen for http requests
  server.handleClient();
}

// Router

void fd(){
  motor.RunForward(2, 1);
  server.send(200, "text/html", "ssdsdsdsd");
  }

void Handle_home(){
  String page_home = Page_home();
  server.send(200, "text/html", page_home);
  }


void Handle_get_time(){

//WiFiClient client = server.client();
String f = server.arg("time");
  Serial.println(f);
  String _page_home = Page_home();
server.send(200, "text/html", _page_home);

  }




