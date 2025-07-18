/*
 * Example: UpdatePantryDetails
 * Demonstrates how to update Pantry metadata (name, description).
 */

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <PantryClient.h>
#include <ArduinoJson.h>

const char *WIFI_SSID = "YOUR-WIFI-SSID";
const char *WIFI_PASSWORD = "YOUR-WIFI-PASSWORD";
const char *PANTRY_ID = "YOUR-PANTRY-ID";

PantryClient client(PANTRY_ID);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(100);
    }
    Serial.println();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");

    // Update Pantry details
    Serial.println("Updating Pantry details...");
    JsonDocument updateDoc;
    updateDoc["name"] = "My Updated Pantry";
    updateDoc["description"] = "This pantry was updated from ESP.";

    if (client.updatePantryDetails(updateDoc))
    {
        Serial.println("Pantry details updated successfully.");
    }
    else
    {
        Serial.println("Failed to update Pantry details.");
    }
}

void loop()
{
    // Nothing to do here
}
