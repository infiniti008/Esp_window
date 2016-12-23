#include "Motor.h"
#include "Page.h"
//#include "Handle.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int current_pos = 0;

Motor motor(D2, D5, D6, D1);

//String home_page;

unsigned long time_run = 0;
String to_do;

char *ssid_ap = "ESPapoint"; // ssid to access point
char *password_con = "19111990"; // password to ssid_con
byte n = 0; // counter time
byte tim = 20; //time to wait connection to ssid_con
byte wifi_stat=2; //0 - ap, 1 - client



ESP8266WebServer server(80);

void setup() {
  // Start Serial
  Serial.begin(115200);

  Serial.println("\nESP Window-controll Server\n");

  // Connect to your WiFi network
  wi_setup();
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


//Function connection to wifi
void wi_setup(){
  // Constant
  n = 0;

  // Connect to your WiFi network
  WiFi.mode(WIFI_STA);
  String myHostname = "foo";
  WiFi.hostname(myHostname);
  WiFi.begin(ssid_con, password_con);
  Serial.print("Connecting to ");
  Serial.print(ssid_con);

  // Wait for successful connection to ssid_con
  while (WiFi.status() != WL_CONNECTED && n < tim) {
    delay(500);
    Serial.print(".");
    n=n+1;
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println();
    Serial.print("ESP IP Adress: ");
    Serial.println(WiFi.localIP());
    wifi_stat = 1;
    start_server();
  }
  Serial.println();

  // Set up access point
  if(n == tim){
    wifi_stat = 0;
    delay(1000);
    Serial.println("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid_ap);
    Serial.print("SSID to connect - ");
    Serial.println(ssid_ap);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    start_server();
  }
}



void start_server(){

    //Page - home
    server.on("/", Handle_home);
    server.on("/open_window", Handle_open_window);
    server.on("/close_window", Handle_close_window);
    server.on("/open_to", Handle_open_to);
    server.on("/timer", Handle_timer);
    server.on("/plan", Handle_plan);

    // Page - config
    server.on("/config", [](){
      server.send(200, "text/html", "<!DOCTYPE html>\
        <html>\
          <head>\
          <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
            <meta charset=\"utf-8\">\
            <title></title>\
          </head>\
          <body>\
            <form id=\"conf\" action=\"/set_configuration\" method=\"get\">\
              <input type=\"text\" name=\"ssid\" placeholder=\"SSID\" form=\"conf\"><br><br>\
              <input type=\"text\" name=\"pass\" placeholder=\"Password\" form=\"conf\"><br><br>\
              <input type=\"text\" name=\"time\" placeholder=\"Time to wait\" form=\"conf\"><br><br>\
              <input type=\"submit\" value=\"Set\" form=\"conf\">\
            </form>\
          </body>\
        </html>");
      });

    //Action - setup new configuration
    server.on("/set_configuration", set_ssid);

    //Start server
    server.begin();
    Serial.println("HTTP server started");
  }

// Router


//Function to change wifi config
void set_ssid(){
  if(server.arg("ssid") != ""){
    server.arg("ssid").toCharArray(ssid_con, server.arg("ssid").length() + 1);
  }
  if(server.arg("pass") != ""){
    server.arg("pass").toCharArray(password_con, server.arg("pass").length() + 1);
  }
  if(server.arg("time") != ""){
    tim = server.arg("time").toInt();
  }
  server.send(200, "text/html", " We get your configuration");
  //stop WiFi
  server.stop();
  delay(200);
  WiFi.disconnect();
  delay(200);
  WiFi.mode(WIFI_OFF);
  delay(200);

  //Restart connection
  wi_setup();
}


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
