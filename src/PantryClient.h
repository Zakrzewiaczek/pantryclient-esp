
/**
 * @file PantryClient.h
 * @brief Arduino client for getpantry.cloud JSON API
 * @author Jakub Zakrzewski
 * @version 0.1.0
 * @date 2025-07-18
 * @copyright MIT License
 */
#ifndef PANTRY_CLIENT_H
#define PANTRY_CLIENT_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#if defined(ESP32)
#include <HTTPClient.h>
#elif defined(ESP8266)
#include <ESP8266HTTPClient.h>
#else
#error "This library only supports ESP32 and ESP8266."
#endif

class PantryClient
{
public:
    /**
     * @brief Constructs a PantryClient object.
     * @param pantryId Your unique Pantry ID from getpantry.cloud.
     */
    PantryClient(const String &pantryId);

    /**
     * @brief Retrieves the details of the entire Pantry (metadata and basket list).
     * @param doc JsonDocument to populate with Pantry details.
     * @return true on success, false on failure.
     */
    bool getPantryDetails(JsonDocument &doc);

    /**
     * @brief Updates Pantry metadata (e.g., name, description).
     * @param doc JsonDocument containing fields to update.
     * @return true on success, false on failure.
     */
    bool updatePantryDetails(const JsonDocument &doc);

    /**
     * @brief Retrieves the contents of a basket as a JsonDocument.
     * @param basketName The name of the basket to retrieve.
     * @param doc JsonDocument to populate with basket contents.
     * @return true on success, false on failure.
     */
    bool getBasket(const String &basketName, JsonDocument &doc);

    /**
     * @brief Retrieves the contents of a basket as a raw JSON string.
     * @param basketName The name of the basket to retrieve.
     * @param result String to store the JSON response.
     * @return true on success, false on failure.
     */
    bool getBasket(const String &basketName, String &result);

    /**
     * @brief Creates a new basket or completely replaces an existing one (uses POST).
     * @param basketName The name of the basket to create or replace.
     * @param doc JsonDocument containing the full data for the basket.
     * @return true on success, false on failure.
     */
    bool createOrReplaceBasket(const String &basketName, const JsonDocument &doc);

    /**
     * @brief Creates or replaces a basket using a raw JSON string as payload.
     * @param basketName The name of the basket.
     * @param jsonPayload Raw JSON string to send.
     * @return true on success, false on failure.
     */
    bool createOrReplaceBasket(const String &basketName, const String &jsonPayload);

    /**
     * @brief Updates an existing basket by merging data (uses PUT).
     * This performs a deep merge, overwriting existing keys or appending new ones.
     * @param basketName The name of the basket to update.
     * @param doc JsonDocument containing the keys/values to add or update.
     * @return true on success, false on failure.
     */
    bool updateBasket(const String &basketName, const JsonDocument &doc);

    /**
     * @brief Updates a basket using a raw JSON string as payload.
     * @param basketName The name of the basket.
     * @param jsonPayload Raw JSON string to send.
     * @return true on success, false on failure.
     */
    bool updateBasket(const String &basketName, const String &jsonPayload);

    /**
     * @brief Deletes a basket from your Pantry.
     * @param basketName The name of the basket to delete.
     * @return true on success, false on failure.
     */
    bool deleteBasket(const String &basketName);

private:
    static constexpr const char *BASE_URL = "https://getpantry.cloud/apiv1/pantry/";
    String _pantryId;
    HTTPClient _httpClient;
    WiFiClientSecure _client;
};

#endif // PANTRY_CLIENT_H