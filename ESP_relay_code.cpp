
#include <WiFi.h>
#include <WebServer.h>

const char* apSSID = "ESP32-Chat";
const char* apPassword = "1234";

WebServer server(80);

String lastMessage = "No messages yet";
String serialBuffer = "";

// Website
void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ESP32 Chat</title>
  </head>
  <body>
    <h1>ESP32 Chat</h1>

    <h3>Latest Message:</h3>
    <p id="message">Loading...</p>

    <form action="/send" method="GET">
      <input type="text" name="msg" placeholder="Type a message">
      <input type="submit" value="Send">
    </form>

    <script>
      setInterval(function() {
        fetch('/latest')
          .then(response => response.text())
          .then(message => {
            document.getElementById('message').textContent = message;
          });
      }, 500);
    </script>

  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

// Laptop website -> ESP32

void handleSend() {
  if (server.hasArg("msg")) {
    String websiteMessage = server.arg("msg");

    Serial2.println(websiteMessage);
  }

  server.sendHeader("Location", "/");
  server.send(303);
}

// ESP32 -> Website
void handleLatest() {
  server.send(200, "text/plain", lastMessage);
}

void setup() {
  Serial2.begin(9600, SERIAL_8N1, 12, 13);

  WiFi.mode(WIFI_AP);
  WiFi.setSleep(false);
  WiFi.softAP(apSSID, apPassword);

  Serial2.print("AP IP: ");
  Serial2.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.on("/latest", handleLatest);

  server.begin();
}

// Serial Monitor -> ESP32 -> Website
void loop() {

  server.handleClient();

  while (Serial2.available()) {

    char c = Serial2.read();

    if (c == '\n') {

      serialBuffer.trim();

      if (serialBuffer.length() > 0) {
        lastMessage = serialBuffer;
        serialBuffer = "";
      }

    } 
    else if (c != '\r') {
      serialBuffer += c;
    }
  }
}
