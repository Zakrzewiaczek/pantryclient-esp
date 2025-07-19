// Uncomment the line below to enable debug logging for PantryClient.
// #define DEBUG

#include "PantryClient.h"

PantryClient::PantryClient(const String &pantryId)
    : _pantryId(pantryId)
{
    _client.setInsecure();
}

// --- Metody dla całego Pantry (bez zmian) ---
bool PantryClient::getPantryDetails(JsonDocument &doc)
{
    String url = String(BASE_URL) + _pantryId;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    int httpCode = _httpClient.GET();
    bool success = false;
    if (httpCode == HTTP_CODE_OK)
    {
        if (deserializeJson(doc, _httpClient.getStream()) == DeserializationError::Ok)
        {
            success = true;
        }
        else
        {
#ifdef DEBUG
            Serial.println(F("PantryClient Error: deserializeJson() failed."));
#endif
        }
    }
    else
    {
#ifdef DEBUG
        Serial.printf("PantryClient Error: GET PantryDetails failed, code: %d\n", httpCode);
#endif
    }
    _httpClient.end();
    return success;
}

bool PantryClient::updatePantryDetails(const JsonDocument &doc)
{
    String url = String(BASE_URL) + _pantryId;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    String payload;
    serializeJson(doc, payload);
    int httpCode = _httpClient.PUT(payload);
    if (httpCode != HTTP_CODE_OK)
    {
#ifdef DEBUG
        Serial.printf("PantryClient Error: PUT PantryDetails failed, code: %d\n", httpCode);
#endif
    }
    _httpClient.end();
    return (httpCode == HTTP_CODE_OK);
}

bool PantryClient::getBasket(const String &basketName, JsonDocument &doc)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    int httpCode = _httpClient.GET();
    bool success = false;
    if (httpCode == HTTP_CODE_OK)
    {
        if (deserializeJson(doc, _httpClient.getStream()) == DeserializationError::Ok)
        {
            success = true;
        }
        else
        {
#ifdef DEBUG
            Serial.println(F("PantryClient Error: deserializeJson() for getBasket failed."));
#endif
        }
    }
    else
    {
#ifdef DEBUG
        Serial.printf("PantryClient Error: GET basket failed, code: %d\n", httpCode);
#endif
    }
    _httpClient.end();
    return success;
}

bool PantryClient::getBasket(const String &basketName, String &result)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    int httpCode = _httpClient.GET();
    bool success = false;
    if (httpCode == HTTP_CODE_OK)
    {
        result = _httpClient.getString();
        success = true;
    }
    _httpClient.end();
    return success;
}

bool PantryClient::createOrReplaceBasket(const String &basketName, const JsonDocument &doc)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    String payload;
    serializeJson(doc, payload);
    return createOrReplaceBasket(basketName, payload);
}

bool PantryClient::createOrReplaceBasket(const String &basketName, const String &jsonPayload)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    int httpCode = _httpClient.POST(jsonPayload);
    if (httpCode != HTTP_CODE_OK)
    {
#ifdef DEBUG
        Serial.printf("PantryClient Error: POST (createOrReplace) failed, code: %d\n", httpCode);
        Serial.println("Server response: " + _httpClient.getString());
#endif
    }
    _httpClient.end();
    return (httpCode == HTTP_CODE_OK);
}

bool PantryClient::updateBasket(const String &basketName, const JsonDocument &doc)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    String payload;
    serializeJson(doc, payload);
    return updateBasket(basketName, payload);
}

bool PantryClient::updateBasket(const String &basketName, const String &jsonPayload)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    int httpCode = _httpClient.PUT(jsonPayload);
    if (httpCode != HTTP_CODE_OK)
    {
#ifdef DEBUG
        Serial.printf("PantryClient Error: PUT (update) failed, code: %d\n", httpCode);
        Serial.println("Server response: " + _httpClient.getString());
#endif
    }
    _httpClient.end();
    return (httpCode == HTTP_CODE_OK);
}

bool PantryClient::deleteBasket(const String &basketName)
{
    String url = String(BASE_URL) + _pantryId + "/basket/" + basketName;
    _httpClient.begin(_client, url);
    _httpClient.addHeader("Content-Type", "application/json");
    int httpCode = _httpClient.DELETE();
    if (httpCode != HTTP_CODE_OK)
    {
#ifdef DEBUG
        Serial.printf("PantryClient Error: DELETE failed, code: %d\n", httpCode);
        Serial.println("Server response: " + _httpClient.getString());
#endif
    }
    _httpClient.end();
    return (httpCode == HTTP_CODE_OK);
}
