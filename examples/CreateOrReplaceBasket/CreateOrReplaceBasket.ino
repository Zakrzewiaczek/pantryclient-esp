/*
 * Example: CreateOrReplaceBasket
 * Demonstrates how to create a new basket or completely replace an existing one.
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
const char *BASKET_NAME = "testBasket";

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

    // Create or replace a basket
    Serial.println("Creating or replacing basket '");
    JsonDocument basketDoc;
    basketDoc["sensor"] = "humidity";
    basketDoc["value"] = 55.2;
    basketDoc["unit"] = "%";

    if (client.createOrReplaceBasket(BASKET_NAME, basketDoc))
    {
        Serial.println("Basket created or replaced successfully.");
    }
    else
    {
        Serial.println("Failed to create or replace basket.");
    }
}

void loop()
{
    // Nothing to do here
}
