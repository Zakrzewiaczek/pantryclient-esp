/*
 * Example: GetPantryDetails
 * Demonstrates how to retrieve details about your Pantry, including a list of baskets.
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

void printJson(const JsonDocument &doc)
{
    String output;
    serializeJsonPretty(doc, output);
    Serial.println(output);
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(100);
    }
    Serial.println();

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");

    // Get Pantry details
    Serial.println("Getting Pantry details...");
    JsonDocument pantryDetails;
    if (client.getPantryDetails(pantryDetails))
    {
        Serial.println("Pantry details:");
        printJson(pantryDetails);
    }
    else
    {
        Serial.println("Failed to get Pantry details.");
    }
}

void loop()
{
    // Nothing to do here
}
