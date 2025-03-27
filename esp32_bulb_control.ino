// ESP32 Web Server Code
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_AP";
const char* password = "12345678";

WebServer server(80);

String webpage = "<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"  <title>ESP32 Bulb Control</title>\n"
"  <style>\n"
"    body { font-family: Arial; text-align: center; }\n"
"    button { padding: 10px 20px; margin: 10px; font-size: 16px; }\n"
"  </style>\n"
"</head>\n"
"<body>\n"
"  <h1>ESP32 Bulb Control</h1>\n"
"  <button onclick=\"fetch('/ON')\">Turn ON</button>\n"
"  <button onclick=\"fetch('/OFF')\">Turn OFF</button>\n"
"  <button onclick=\"fetch('/BLINK')\">Blink</button>\n"
"  <button onclick=\"setTimer()\">Set Timer</button>\n"
"  <input type='number' id='timer' placeholder='Enter seconds'>\n"
"  <script>\n"
"    function setTimer() {\n"
"      let seconds = document.getElementById('timer').value;\n"
"      fetch('/TIMER?value=' + seconds);\n"
"    }\n"
"  </script>\n"
"</body>\n"
"</html>";

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleOn() {
  digitalWrite(2, HIGH);
  server.send(200, "text/plain", "Bulb ON");
}

void handleOff() {
  digitalWrite(2, LOW);
  server.send(200, "text/plain", "Bulb OFF");
}

void handleBlink() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
  server.send(200, "text/plain", "Blinking Done");
}

void handleTimer() {
  String value = server.arg("value");
  int seconds = value.toInt();
  digitalWrite(2, HIGH);
  delay(seconds * 1000);
  digitalWrite(2, LOW);
  server.send(200, "text/plain", "Bulb turned off after " + value + " seconds");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/ON", handleOn);
  server.on("/OFF", handleOff);
  server.on("/BLINK", handleBlink);
  server.on("/TIMER", handleTimer);
  server.begin();
  pinMode(2, OUTPUT);
}

void loop() {
  server.handleClient();
}
