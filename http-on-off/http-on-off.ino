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

/*
 * append ".local" or whatever your search domain is to access the web interface
 */
const char* host = "garage1";

/*
 * Easiest way to adjust the style is load web page in Mobile Safari, connect to your Mac
 * with cable, and then Develop > iPhone > garageX.local from Safari. Tweak styles from there. 
 */
const String buttonStyle = "-webkit-appearance: none; border-radius: 0; width: 100%; height: 30%; font-size: 72px; color: white; background-color: #08c;";
const String controls = "<form method=\"post\"><button type=\"submit\" style=\"" + buttonStyle + "\">Toggle</button></form>";

const int relayPin = D1;

ESP8266WebServer server(80);

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

  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", controls);
  });

  server.on("/", HTTP_POST, [](){
    turn_on();
    delay(1000);
    turn_off();
    server.sendHeader("Location", "/", true);
    server.send (302, "text/plain", "");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

