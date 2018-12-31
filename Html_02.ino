/*
 * Demonstrate using an http server and an HTML form to control a relay.
 * The http server runs on the ESP8266.
 *
 * Connect to "http://<IP address>"
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
  byte v1 = 197;
  byte v2 = 3;
  byte v3 = 7;
  byte v4 = 150;
  IPAddress ip(v1,v2,v3,v4);
  IPAddress gateway(197,3,7,1);
  IPAddress subnet(255,255,255,0);

// Fill in your WiFi router SSID and password
const char* ssid = "HI-LINK";
const char* password = "nalin1973";

ESP8266WebServer server(80);

const int relayPin = D1;

const char INDEX_HTML[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>ESP8266 Web Form Demo</title>"
"<style>"
"\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
"</style>"
"</head>"
"<body>"
"<h1>ESP8266 Relay Test Web Form</h1>"
"<FORM action=\"/\" method=\"post\">"
"<P>"
"Relay<br>"
"<INPUT type=\"text\" name=\"a1\" size=\"5\"<BR>"
"<INPUT type=\"text\" name=\"a2\" size=\"5\"<BR>"
"<INPUT type=\"text\" name=\"a3\" size=\"5\"<BR>"
"<INPUT type=\"text\" name=\"a4\" size=\"5\"<BR>"
"<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
"</P>"
"</FORM>"
"</body>"
"</html>";

void handleRoot()
{
  if (server.hasArg("a1")) {
    handleSubmit();
  }
  else {
    server.send(200, "text/html", INDEX_HTML);
  }
    if (server.hasArg("a2")) {
    handleSubmit();
  }
  else {
    server.send(200, "text/html", INDEX_HTML);
  }
    if (server.hasArg("a3")) {
    handleSubmit();
  }
  else {
    server.send(200, "text/html", INDEX_HTML);
  }
      if (server.hasArg("a4")) {
    handleSubmit();
  }
  else {
    server.send(200, "text/html", INDEX_HTML);
  }
}

void returnFail(String msg)
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void handleSubmit()
{
  String b1;
  int c1;
  /*-------------------------*/
  String b2;
  int c2;
  /*-------------------------*/
  String b3;
  int c3;
  /*-------------------------*/
  String b4;
  int c4;
  /*-------------------------*/
   v1 = c1 ;
   v2 = c2 ;
   v3 = c3 ;
   v4 = c4 ;
   
  //if (!server.hasArg("a1")) return returnFail("BAD ARGS");
  b1 = server.arg("a1");
  c1 = b1.toInt();
  /*----------------------------------------------------------------*/
    //if (!server.hasArg("a2")) return returnFail("BAD ARGS");
  b2 = server.arg("a2");
  c2 = b2.toInt();
  /*----------------------------------------------------------------*/
  //if (!server.hasArg("a3")) return returnFail("BAD ARGS");
  b3 = server.arg("a3");
  c3 = b3.toInt();
  /*----------------------------------------------------------------*/
    //if (!server.hasArg("a4")) return returnFail("BAD ARGS");
  b4 = server.arg("a4");
  c4 = b4.toInt();
   /*-------------------------*/
   v1 = c1 ;
   v2 = c2 ;
   v3 = c3 ;
   v4 = c4 ;

  /*----------------------------------------------------------------*/
  Serial.print(v1);
  Serial.print(",");
  Serial.print(v2);
  Serial.print(",");
  Serial.print(v3);
  Serial.print(",");
  Serial.println(v4);
  Serial.println("---------------");
  
    

  
  //Serial.println("turning on relay for " + b + " milliseconds");
 // toggleRelay(d);
  //Serial.println("done");
  
  IPAddress ip(v1,v2,v3,v4);
    WiFi.config(ip, gateway, subnet);
  
  Serial.println("done");
  server.send(200, "text/html", INDEX_HTML);
}

void returnOK()
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK\r\n");
}

void toggleRelay(int interval) {
  digitalWrite(BUILTIN_LED, LOW);  // turn on LED with voltage LOW
  digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH
  delay(interval);              // pause
  digitalWrite(relayPin, LOW);  // turn off relay with voltage LOW
  digitalWrite(BUILTIN_LED, HIGH);   // turn off LED with voltage HIGH
}
  
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void)
{
  pinMode(relayPin, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output
  digitalWrite(BUILTIN_LED, HIGH);   // turn off LED with voltage HIGH

  Serial.begin(115200);
  WiFi.config(ip, gateway, subnet);
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

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.print("Connect to http://");
  Serial.println(WiFi.localIP());
}

void loop(void)
{
  server.handleClient();
}
