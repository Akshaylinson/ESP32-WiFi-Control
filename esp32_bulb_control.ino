#include <WiFi.h>

// Wi-Fi Access Point Credentials
const char *ssid = "ESP32_Hotspot";  
const char *password = "12345678";   

WiFiServer server(80); // Web server runs on port 80
const int relayPin = 5; // GPIO pin for relay

bool blinkState = false;
bool blinkMode = false;
unsigned long previousMillis = 0;
int blinkInterval = 500; // Default blink interval in milliseconds

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Bulb OFF initially

  // Start ESP32 in Access Point (AP) Mode
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP Mode Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP()); // Print ESP32 IP Address

  server.begin(); // Start web server
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming connections

  if (client) {
    Serial.println("Client Connected.");
    String request = client.readStringUntil('\r'); // Read request
    Serial.println(request);
    client.flush();

    // Control Relay
    if (request.indexOf("/ON") != -1) {
      digitalWrite(relayPin, HIGH);
      blinkMode = false;
    } 
    else if (request.indexOf("/OFF") != -1) {
      digitalWrite(relayPin, LOW);
      blinkMode = false;
    }
    else if (request.indexOf("/SETTIMER?time=") != -1) {
      int startIndex = request.indexOf("=") + 1;
      int endIndex = request.indexOf(" ", startIndex);
      String timeString = request.substring(startIndex, endIndex);
      int timeDelay = timeString.toInt() * 1000; // Convert seconds to milliseconds
      digitalWrite(relayPin, HIGH);
      delay(timeDelay);
      digitalWrite(relayPin, LOW);
    }
    else if (request.indexOf("/BLINK?interval=") != -1) {
      int startIndex = request.indexOf("=") + 1;
      int endIndex = request.indexOf(" ", startIndex);
      String intervalString = request.substring(startIndex, endIndex);
      blinkInterval = intervalString.toInt();
      blinkMode = true;
    }

    // Send Webpage Response with UI
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html><head><title>ESP32 Web Control</title>");
    client.println("<style>");
    client.println("body { text-align: center; font-family: Arial; margin: 50px; }");
    client.println(".button { padding: 15px 30px; font-size: 20px; margin: 10px; border: none; cursor: pointer; }");
    client.println(".on { background-color: green; color: white; }");
    client.println(".off { background-color: red; color: white; }");
    client.println(".blink { background-color: blue; color: white; }");
    client.println("</style></head><body>");
    client.println("<h1>ESP32 Web Server</h1>");
    client.println("<button class='button on' onclick='sendRequest(\"/ON\")'>Turn ON</button>");
    client.println("<button class='button off' onclick='sendRequest(\"/OFF\")'>Turn OFF</button>");
    client.println("<br><br>");
    client.println("<input type='number' id='timerInput' placeholder='Enter seconds' min='1'>");
    client.println("<button class='button' onclick='setTimer()'>Set Timer</button>");
    client.println("<br><br>");
    client.println("<input type='number' id='blinkInput' placeholder='Blink interval (ms)' min='100'>");
    client.println("<button class='button blink' onclick='setBlink()'>Blink</button>");
    client.println("<br><br>");
    client.println("<script>");
    client.println("function sendRequest(path) {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.open('GET', path, true);");
    client.println("  xhttp.send();");
    client.println("}");
    client.println("function setTimer() {");
    client.println("  var time = document.getElementById('timerInput').value;");
    client.println("  sendRequest('/SETTIMER?time=' + time);");
    client.println("}");
    client.println("function setBlink() {");
    client.println("  var interval = document.getElementById('blinkInput').value;");
    client.println("  sendRequest('/BLINK?interval=' + interval);");
    client.println("}");
    client.println("</script></body></html>");
    client.println();

    client.stop(); // Close connection
    Serial.println("Client Disconnected.");
  }

  // Blink Logic
  if (blinkMode) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      blinkState = !blinkState;
      digitalWrite(relayPin, blinkState ? HIGH : LOW);
    }
  }
}
