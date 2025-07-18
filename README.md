# PantryClient for ESP32 & ESP8266

[![Compatibility](https://img.shields.io/badge/Compatibility-ESP32%20%7C%20ESP8266-blue)](https://www.espressif.com/)

A simple Arduino client for the [getpantry.cloud](https://getpantry.cloud/) API, allowing you to store and retrieve JSON data from your ESP32 or ESP8266 projects.

## Features

- Create, replace, update, get, and delete baskets.
- Get and update Pantry details.
- Supports both ESP32 and ESP8266 platforms.
- Uses the efficient [ArduinoJson](https://arduinojson.org/) library for data handling.

## Dependencies

- **ArduinoJson** by Benoît Blanchon (version 7.x recommended)

## Security Note

For development and testing, this library uses insecure HTTPS connections by default (`setInsecure()`). For production use, it is recommended to use `setCACert()` with the Pantry root certificate for secure communication.

## Installation

### Arduino IDE

1. Download this library as a `.zip` file.
2. In the Arduino IDE, go to `Sketch` > `Include Library` > `Add .ZIP Library...`
3. Select the downloaded `.zip` file.
4. The IDE will also prompt you to install the `ArduinoJson` dependency if you don't have it.

### PlatformIO

Add the following to your `platformio.ini` file under the `lib_deps` section:

```ini
lib_deps =
  bblanchon/ArduinoJson
  ; Assuming your library is in the 'lib' folder
```

## API Reference

### Constructor

`PantryClient(const String &pantryId);`
Initializes the client with your unique Pantry ID.

### Methods

- `bool getPantryDetails(JsonDocument &doc);`
  - Retrieves the details of the entire Pantry.

- `bool updatePantryDetails(const JsonDocument &doc);`
  - Updates the details of the Pantry (e.g., name, description).

- `bool createOrReplaceBasket(const String &basketName, const JsonDocument &doc);`
  - Creates a new basket or completely replaces an existing one (uses `POST`).

- `bool updateBasket(const String &basketName, const JsonDocument &doc);`
  - Updates an existing basket by merging data (uses `PUT`).

- `bool getBasket(const String &basketName, JsonDocument &doc);`
  - Retrieves the full contents of a specific basket.

- `bool deleteBasket(const String &basketName);`
  - Deletes an entire basket.

All methods return `true` on success and `false` on failure. In case of failure, details are printed to the `Serial` monitor.

## Examples

Sample programs demonstrating all features of the PantryClient library can be found in the `/examples` folder. In the Arduino IDE, you can access them via the menu: **File > Sketchbook > PantryClient > ...**

Each example is focused on a single functionality and is well-commented to help you get started quickly.
