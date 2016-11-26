#include "Motor.h"
#include "Page.h"
//#include "Handle.h"
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int current_pos = 0;

Motor motor(D2, D5, D6, D1);

//String home_page;

unsigned long time_run = 0;
String to_do;
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
  server.on("/", Handle_home);
  server.on("/open_window", Handle_open_window);
  server.on("/close_window", Handle_close_window);
  server.on("/open_to", Handle_open_to);
  server.on("/timer", Handle_timer);
  server.on("/plan", Handle_plan); 
  
  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Listen for http requests
  server.handleClient();
  if (millis()/1000 == time_run){
    delay(1000);
    Serial.println("Before start by timer");
    run_timer();
  }
}

// Router

void Handle_home(){
  String page_home = Page_home();
  server.send(200, "text/html", page_home);
}

void Handle_open_window(){
  Serial.println("Window is opening");
  String to_home = To_home();
  String mes = "Окно открывается полностью";
  to_home.replace("{{Text}}", mes);
  server.send(200, "text/html", to_home);
  motor.RunForward(60-current_pos, 1);
  current_pos=60;
}

void Handle_close_window(){
  Serial.println("Window is closing");
  String to_home = To_home();
  String mes = "Окно закрывается полностью";
  to_home.replace("{{Text}}", mes);
  server.send(200, "text/html", to_home);
  motor.RunBack(current_pos, 1);
  current_pos=0;
}

void Handle_open_to(){
  int procent = server.arg("open_procent").toInt();
  int obor = current_pos - ((procent/5)*3);
  String to_home = To_home();
  String mes = "Окно открывается с ";
  mes += (current_pos/3)*5;
  mes += "% до ";
  mes += procent;
  mes += "%"; 
  if(obor == 0) mes = "Вы уже находитесь в указанной позиции";
  to_home.replace("{{Text}}", mes);
  server.send(200, "text/html", to_home);
//  Serial.println(mes);
  if(obor > 0) motor.RunBack(abs(obor), 1);
  else if(obor < 0) motor.RunForward(abs(obor), 1);
  current_pos = (procent/5)*3;
}

void Handle_timer(){
  Serial.println("We got your timer");
  String to_home = To_home();
  to_home.replace("{{Text}}", "Мы установили ваш таймер");
  server.send(200, "text/html", to_home);
  int timer = server.arg("time").toInt();
  time_run = millis()/1000 + timer*60;
  to_do = server.argName(1);
  Serial.println(millis()/1000);
  Serial.println(time_run);
}

void Handle_plan(){
  Serial.println("Window is closing");
  server.send(200, "text/html", "Window is closing");
}

void run_timer(){
  if (to_do == "timer_close"){
    Serial.println("closecloseclose");
    time_run = 0;
    to_do = "_";
    motor.RunBack(current_pos, 1);
    current_pos=0;
  }
  else if(to_do == "timer_open"){
    Serial.println("openopenopen");
    time_run = 0;
    to_do = "_";
    motor.RunForward(60-current_pos, 1);
    current_pos=60;
  }
}




