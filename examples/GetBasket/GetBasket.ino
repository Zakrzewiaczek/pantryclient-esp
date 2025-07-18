/*
 * Example: GetBasket
 * Demonstrates how to read the contents of a basket.
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

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");

    // Get basket contents
    Serial.println("Reading basket '");
    JsonDocument basketDoc;
    if (client.getBasket(BASKET_NAME, basketDoc))
    {
        Serial.println("Basket contents:");
        printJson(basketDoc);
    }
    else
    {
        Serial.println("Failed to read basket. Does it exist?");
    }
}

void loop()
{
    // Nothing to do here
}
