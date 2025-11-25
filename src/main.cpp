#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "ESP32_Network";
const char* password = "12345678";

WiFiServer server(5000);

void setup() {
    Serial.begin(115200);
    //starting esp32 access point
    WiFi.softAP(ssid, password);
    Serial.println("Access Point Started");
    Serial.println("SSID: "), Serial.println(ssid);
    Serial.println("IP address: "), Serial.println(WiFi.softAPIP());

    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Client connected!");

        while (client.connected()) {          // Keep connection alive
            if (client.available()) {         // Check for new data
                String cmd = client.readStringUntil('\n');
                cmd.trim();
                Serial.print("Received command: "); 
                Serial.println(cmd);

                // Respond to client
                client.println("ESP32 received: " + cmd);

                // Handle robot commands
                if (cmd == "forward") Serial.println("Move robot forward");
                else if (cmd == "back") Serial.println("Move robot backward");
                else if (cmd == "left") Serial.println("Turn left");
                else if (cmd == "right") Serial.println("Turn right");
                else if (cmd == "stop") Serial.println("Stop motors");
            }

            delay(1);  // Small delay to avoid blocking CPU
        }

        client.stop();                     // Only stop after client disconnects
        Serial.println("Client disconnected");
    }
}
