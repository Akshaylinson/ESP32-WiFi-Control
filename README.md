**ESP32 WiFi-Controlled Smart Switch with Web and Mobile App
**
Project Overview:-
This project enables users to control an ESP32 relay switch through a web-based interface and a mobile app created using Kodular. The ESP32 operates in Access Point (AP) mode, allowing users to connect and send ON/OFF commands without requiring an internet connection.

Key Features:-
✅ ESP32 in AP Mode – No external WiFi required, works locally.
✅ Web-Based Control – Users can access from a browser to control the relay.
✅ Kodular Mobile App – A custom-built app with a Web Viewer to control the relay.
✅ Real-Time Status Monitoring – Displays whether the ESP32 is Connected or Not Connected.
✅ WhatsApp Support Integration – Users can contact software support via a WhatsApp link.
✅ Reload & Back Navigation – Easily reload the interface and switch between screens.
✅ Dark Mode Toggle (Planned Feature) – A user-friendly dark mode for better UI experience.

How It Works:-
The ESP32 creates a WiFi hotspot, and users connect their mobile or PC to it.
A simple web interface (HTML/CSS) is hosted on the ESP32 at web server.
Users can press ON/OFF buttons to control the relay module connected to ESP32.
The Kodular app has a Web Viewer that loads the same interface for mobile use.
A status label shows "Connected" if ESP32 responds, else "Not Connected".
A reload button refreshes the page, and a back button returns to the main screen.
Users can click the WhatsApp Support button to contact technical support.

Technology Used:-
ESP32 (Microcontroller, AP Mode, Web Server)
HTML, CSS (For Web UI)
Kodular (For Android app development)
MQTT/HTTP Requests (For communication with ESP32)

Future Enhancements
🔹 Dark Mode Toggle for better UI experience
🔹 Voice Control via Google Assistant
🔹 WiFi Mode to connect ESP32 to an existing router
🔹 Multiple Device Control from one interface
