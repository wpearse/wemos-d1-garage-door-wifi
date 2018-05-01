/*
 * Code adapted from: https://github.com/wemos/D1_mini_Examples
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/*
 * TODO: figure out equivalent of .env file?
 */
const char* ssid = "";
const char* password = "";
const char* host = "garage2";

const String controls = "<a href=\"/on\">turn on</a> or <a href=\"/off\">turn off</a> or <a href=\"/toggle\">toggle</a>";

const int relayPin = D1;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "hello from esp8266!" + controls);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/html", message);
}

void turn_on() {
  digitalWrite(BUILTIN_LED, LOW); // low = on
  digitalWrite(relayPin, HIGH);
}

void turn_off() {
  digitalWrite(BUILTIN_LED, HIGH); // high = off
  digitalWrite(relayPin, LOW);
}

void setup(void){
  
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  digitalWrite(BUILTIN_LED, HIGH);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.print("Host: ");
  Serial.println(host);
  
  if (MDNS.begin(host)) {
    Serial.println("MDNS responder started");
    MDNS.addService("http", "tcp", 80);
  }

  server.on("/", handleRoot);

  server.on("/on", [](){
    turn_on();
    server.send(200, "text/html", controls);
  });

  server.on("/off", [](){
    turn_off();
    server.send(200, "text/html", controls);
  });

  server.on("/toggle", [](){
    turn_on();
    delay(1000);
    turn_off();
    server.send(200, "text/html", controls);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

