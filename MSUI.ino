#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define LED_PIN 2
#include <DNSServer.h>
#include <ICSC.h>
#include <WiFiManager.h>
#include <ESP32Ping.h>

// ========================================
// CONFIGURATION - Easy to change values
// ========================================
const char *DEVICE_ID = "prb51";
const char *API_KEY = "684se";
const char *API_BASE_URL = "https://sawo-prod-e25d63ad9b87.herokuapp.com/sauna";
// ========================================

const int FLASH_BUTTON_PIN = 0;

// Construct the full URL using the device ID
String urlString = String(API_BASE_URL) + "/" + String(DEVICE_ID) + "/state";
const char *url = urlString.c_str();

// Construct WiFi AP name with Device ID
String wifiAPName = "SAWO WiFi " + String(DEVICE_ID);

int temperature = 0;
int temperatureC = 0;
bool heaterOn = false;
bool lightsOn = false;
int session_data;
byte downbtn = LOW;
byte backtoyou = 0;
int actualTemperature_data;
int targetTemperature = 80;
byte powerStateOfBoard = 1;
HTTPClient http;
bool backtoyoutoo_data = false;
bool initialized = false;
bool lighttoyoutoo_data = false;
bool lightfromESP = false;
String payload = "{}";
unsigned long hours_data;
unsigned long minutes_data;
unsigned long seconds_data;
byte nareceive = 1;
int Temp_data;
int TempFah_data;
unsigned long Time_data;
unsigned long sessionTime_data;
byte prev_sessionTime_data = -1;
unsigned long sessionTime;
byte error1_data;
String temperatureScale = "C";
byte Tempscale_data;
unsigned long preivousMillisVersionData;
unsigned long receiveMillis;
byte advUser_data = 1;
byte power = 0;
boolean lighttoyou = false;

unsigned long lastHttpRequest = 0;
const unsigned long httpInterval = 1000;

// WiFi reconnection tracking
unsigned long wifiDisconnectedTime = 0;
const unsigned long wifiReconnectTimeout = 180000;  // 3 minutes in milliseconds
bool wifiWasConnected = false;

// Pre-allocated JSON document to avoid heap fragmentation
StaticJsonDocument<512> responseDoc;

// Internet connectivity detection variables
byte internetStatus = 1;  // 0 = No Internet, 1 = Internet OK
int consecutiveHttpFailures = 0;
unsigned long lastSuccessfulHttp = 0;
bool needsPingVerification = false;
bool internetCheckActive = true;  // Flag to pause/resume checking
const int maxHttpFailures = 4;    // Try server 4 times before pinging
const int pingCount = 2;          // Ping each host 2 times

// Ping verification timing (runs in loop on Core 1 instead of separate task)
unsigned long lastPingCheck = 0;
const unsigned long pingCheckInterval = 500;  // Check ping flag every 500ms

// LED blinking for no internet indicator (uses hardware timer interrupt)
hw_timer_t *ledTimer = NULL;
volatile bool ledBlinkEnabled = false;  // Controls whether the timer toggles the LED
volatile bool timerLedState = false;
byte buttonOnPressedInterface_data;
byte light_data;
byte nowifi;
byte nonetwork;
int maxTemp = 110;  // Maximum temperature limit for this sauna (°C) - change this to adjust the cap

// Hardware timer ISR - toggles LED every 150ms when blinking is enabled
void IRAM_ATTR onLedTimerISR() {
  if (ledBlinkEnabled) {
    timerLedState = !timerLedState;
    digitalWrite(LED_PIN, timerLedState);
  }
}

// ========================================
// WiFi Test Function - Called during setup
// Listens for WIFI_TEST command via serial
// Format: WIFI_TEST:<ssid>:<password>
// Tests WiFi connectivity and reports RSSI
// Does NOT affect saved WiFiManager credentials
// ========================================
void checkForWiFiTest() {
  // Flush any garbage in the serial RX buffer from bootloader/reset
  delay(200);
  while (Serial.available()) {
    Serial.read();
  }

  // PHASE 1: Quick check for wake-up signal (1000ms total boot delay for customers)
  Serial.println("[WIFI_TEST] Quick check for test command...");

  unsigned long quickCheckStart = millis();
  const unsigned long quickCheckTimeout = 1000;  // 1000ms + 200ms flush = 1200ms total delay
  String serialBuffer = "";
  bool testModeRequested = false;

  while (millis() - quickCheckStart < quickCheckTimeout) {
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        serialBuffer.trim();
        // Look for wake-up command
        if (serialBuffer.startsWith("WIFI_TEST_START")) {
          testModeRequested = true;
          Serial.println("[WIFI_TEST] Test mode activated!");
          break;
        }
        serialBuffer = "";
      } else {
        if (c >= 32 && c <= 126) {  // Only accept printable ASCII
          serialBuffer += c;
        }
      }
    }
    if (testModeRequested) break;
    delay(10);
  }

  // If no test requested, exit fast (only 1200ms total delay for customers)
  if (!testModeRequested) {
    Serial.println("[WIFI_TEST] No test requested, continuing normal boot (1200ms delay)");
    return;
  }

  // PHASE 2: Full WiFi test mode (only runs if wake-up received during provisioning)
  Serial.println("[WIFI_TEST] Listening for WiFi credentials (10 seconds)...");

  unsigned long startTime = millis();
  const unsigned long listenTimeout = 10000;
  serialBuffer = "";

  while (millis() - startTime < listenTimeout) {
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        serialBuffer.trim();
        if (serialBuffer.startsWith("WIFI_TEST:")) {
          // Parse SSID and password from command
          String params = serialBuffer.substring(10);
          int separatorIdx = params.indexOf(':');

          String testSSID = "";
          String testPassword = "";

          if (separatorIdx > 0) {
            testSSID = params.substring(0, separatorIdx);
            testPassword = params.substring(separatorIdx + 1);
          } else {
            testSSID = params;
          }

          Serial.println("[WIFI_TEST] Command received!");
          Serial.print("[WIFI_TEST] Test SSID: ");
          Serial.println(testSSID);

          // Attempt WiFi connection for testing
          Serial.println("[WIFI_TEST] Connecting to test network...");

          // Set WiFi to station mode for testing
          WiFi.mode(WIFI_STA);
          WiFi.begin(testSSID.c_str(), testPassword.c_str());

          unsigned long connectStart = millis();
          const unsigned long connectTimeout = 15000;

          while (WiFi.status() != WL_CONNECTED && millis() - connectStart < connectTimeout) {
            delay(500);
            // Serial.print(".");
          }
          // Serial.println();

          if (WiFi.status() == WL_CONNECTED) {
            int rssi = WiFi.RSSI();
            String ssid = WiFi.SSID();
            String ip = WiFi.localIP().toString();

            Serial.println("[WIFI_TEST] CONNECTED");
            Serial.print("[WIFI_TEST] SSID: ");
            Serial.println(ssid);
            Serial.print("[WIFI_TEST] RSSI: ");
            Serial.print(rssi);
            Serial.println(" dBm");
            Serial.print("[WIFI_TEST] IP: ");
            Serial.println(ip);
            Serial.println("[WIFI_TEST] COMPLETE");

            // Properly disconnect test WiFi WITHOUT affecting saved credentials
            WiFi.disconnect(true, false);  // disconnect=true, eraseap=false
            delay(500);
          } else {
            Serial.println("[WIFI_TEST] FAILED");
            Serial.println("[WIFI_TEST] Could not connect to test network");
            Serial.println("[WIFI_TEST] COMPLETE");

            // Disconnect failed connection attempt
            WiFi.disconnect(true, false);  // disconnect=true, eraseap=false
            delay(500);
          }

          return;
        }
        serialBuffer = "";
      } else {
        if (c >= 32 && c <= 126) {  // Only accept printable ASCII
          serialBuffer += c;
        }
      }
    }
    delay(50);
  }

  Serial.println("[WIFI_TEST] Timeout - No credentials received");
}

// Ping verification - called from loop() when needed (runs on Core 1)
void doPingVerification() {
  if (!(internetCheckActive && needsPingVerification && WiFi.status() == WL_CONNECTED)) {
    return;
  }

  needsPingVerification = false;

  // Serial.println("[PING] Starting internet verification...");

  // Try Google DNS (8.8.8.8) - ping 2 times
  // Serial.print("[PING] Pinging 8.8.8.8 ");
  // Serial.print(pingCount);
  // Serial.print(" times... ");
  bool hasInternet = Ping.ping(IPAddress(8, 8, 8, 8), pingCount);
  // Serial.println(hasInternet ? "SUCCESS" : "FAILED");

  // If failed, try Cloudflare (1.1.1.1) - ping 2 times
  if (!hasInternet) {
    // Serial.print("[PING] Pinging 1.1.1.1 ");
    // Serial.print(pingCount);
    // Serial.print(" times... ");
    hasInternet = Ping.ping(IPAddress(1, 1, 1, 1), pingCount);
    // Serial.println(hasInternet ? "SUCCESS" : "FAILED");
  }

  // Update the byte variable and send via ICSC only if status changed
  if (!hasInternet && internetStatus != 0) {
    internetStatus = 0;           // Set byte to 0 (No Internet)
    internetCheckActive = false;  // STOP checking until internet returns
    // Serial.println("[INTERNET] Status changed: NO INTERNET");
    // Serial.println("[INTERNET] *** CHECKING PAUSED - Will resume when HTTP succeeds ***");
    // Serial.println("[LED] Blue LED will now BLINK (no internet)");
    // Serial.println("[ICSC] Sending internet status: 0 (No Internet)");

  } else if (hasInternet && internetStatus != 1) {
    internetStatus = 1;           // Set byte to 1 (Internet OK)
    consecutiveHttpFailures = 0;  // Reset failure counter when internet returns
    // Serial.println("[INTERNET] Status changed: INTERNET OK");
    // Serial.println("[INTERNET] Checking will continue normally");
    // Serial.println("[LED] Blue LED will now be SOLID (internet OK)");
    // Serial.println("[ICSC] Sending internet status: 1 (Internet OK)");
  }

  Serial.print("[INTERNET] Final status: ");
  Serial.println(internetStatus == 1 ? "CONNECTED" : "DISCONNECTED");
}

// Update internet status based on HTTP success/failure
void updateInternetStatus(bool httpSuccess) {

  // -------------------------------------------------
  // CASE 1: WiFi NOT connected
  // -------------------------------------------------
  if (WiFi.status() != WL_CONNECTED) {

    if (internetStatus != 0) {
      internetStatus = 0;           // Force internet OFF
      internetCheckActive = false;  // Stop checking until WiFi returns
    }

    consecutiveHttpFailures = 0;
    needsPingVerification = false;
    return;  // Nothing else to evaluate
  }

  // -------------------------------------------------
  // CASE 2: HTTP SUCCESS (Internet confirmed working)
  // -------------------------------------------------
  if (httpSuccess) {

    if (internetStatus != 1) {
      internetStatus = 1;          // Internet OK
      internetCheckActive = true;  // Resume monitoring
    }

    consecutiveHttpFailures = 0;
    lastSuccessfulHttp = millis();
    return;
  }

  // -------------------------------------------------
  // CASE 3: HTTP FAILED (WiFi connected)
  // -------------------------------------------------
  if (internetCheckActive) {

    consecutiveHttpFailures++;

    if (consecutiveHttpFailures >= maxHttpFailures) {
      needsPingVerification = true;  // Trigger ping check
      consecutiveHttpFailures = 0;
    }
  }

  // If checking paused, do nothing
}

// Handle LED indicator based on WiFi and Internet status
// Controls whether the hardware timer blink is active, or sets LED solid ON/OFF
void updateLedIndicator() {
  if (WiFi.status() != WL_CONNECTED) {
    // No WiFi - LED OFF, stop blinking
    ledBlinkEnabled = false;
    digitalWrite(LED_PIN, LOW);
  } else if (internetStatus == 1) {
    // WiFi connected AND internet OK - LED SOLID ON, stop blinking
    ledBlinkEnabled = false;

    digitalWrite(LED_PIN, HIGH);
  } else {
    // WiFi connected BUT no internet - enable hardware timer blinking
    ledBlinkEnabled = true;
  }
}
// ========================================
// ICSC WIFI STATUS SEND
// ========================================
void E11() {
  static byte lastState = 255;
  byte state = (WiFi.status() == WL_CONNECTED) ? 1 : 0;

  if (state != lastState) {
    lastState = state;
    nowifi = state;
    ICSC.send(8, 'N', 1, (char *)&nowifi);
  }
}

// ========================================
// ICSC INTERNET STATUS SEND
// ========================================
void E12() {
  static byte lastState = 255;
  byte state = (internetStatus == 1) ? 1 : 0;

  if (state != lastState) {
    lastState = state;
    nonetwork = state;
    ICSC.send(8, 'j', 1, (char *)&nonetwork);
  }
}
void setup() {

  Serial.begin(115200);
  Serial.println("\n\n[BOOT] ESP32 Starting...");

  Serial.println("=================================");
  Serial.print("[CONFIG] DEVICE ID: ");
  Serial.println(DEVICE_ID);

  // Serial.print("[CONFIG] API KEY: ");
  // Serial.println(API_KEY);

  // Serial.print("[CONFIG] FULL API URL: ");
  // Serial.println(url);

  // Serial.print("[CONFIG] WiFi AP Name: ");
  // Serial.println(wifiAPName);
  Serial.println("=================================");

  // Check for WiFi test command from provisioning tool before WiFiManager starts
  // This allows testing WiFi hardware without affecting saved credentials

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(FLASH_BUTTON_PIN, INPUT_PULLUP);

  ledTimer = timerBegin(1000000);
  timerAttachInterrupt(ledTimer, &onLedTimerISR);
  timerAlarm(ledTimer, 150000, true, 0);

  checkForWiFiTest();

  WiFiManager wm;
  wm.setDebugOutput(false);
  wm.setConnectTimeout(30);
  wm.setConfigPortalTimeout(0);
  wm.setBreakAfterConfig(true);

  if (!wm.autoConnect(wifiAPName.c_str())) {
    delay(3000);
    ESP.restart();
  }



  // Serial.println("[WIFI] Connected successfully!");
  // Serial.print("[WIFI] IP Address: ");
  // Serial.println(WiFi.localIP());
  // Serial.print("[WIFI] SSID: ");
  // Serial.println(WiFi.SSID());

  wifiWasConnected = true;  // Mark that we've had a successful connection
  delay(500);

  Serial.println("[ICSC] Initializing ICSC communication...");
  ICSC.begin(9, 57600, 19);
  ICSC.process();
  ICSC.registerCommand('w', &buttonOnPressedInterface);
  ICSC.registerCommand('x2', &actualTemperature1);
  ICSC.registerCommand('Q', &backtoyoutoo);
  ICSC.registerCommand('LUI', &lighttoyoutoo);
  ICSC.registerCommand('tt', &Temp);
  ICSC.registerCommand('H', &hours);
  ICSC.registerCommand('M', &minutes);
  ICSC.registerCommand('S', &seconds);
  ICSC.registerCommand('E', &error1);
  ICSC.registerCommand('l', &light);
  // ICSC.send(5, 'A', 1, (char *)&advUser_data);  //remove for flicker issue

  // Serial.println("[ICSC] Commands registered");

  // Serial.print("[INTERNET] Smart monitoring: Server retries=");
  // Serial.print(maxHttpFailures);
  // Serial.print(", Pings per host=");
  // Serial.println(pingCount);
  // Serial.println("[INTERNET] Checking pauses when no internet, resumes when connection restored");
  // Serial.println("[LED] Indicator: OFF=No WiFi, SOLID=Internet OK, BLINKING=No Internet");

  // Serial.println("[BOOT] Setup complete - Starting main loop\n");
}

void loop() {
  // Always process ICSC first - critical for component communication
  ICSC.process();
  E11();
  E12();
  handleWiFiReconnect();
  // Update LED indicator based on WiFi and internet status
  updateLedIndicator();

  // Run ping verification if needed (non-blocking check, only pings when flagged)
  if (needsPingVerification && millis() - lastPingCheck >= pingCheckInterval) {
    lastPingCheck = millis();
    doPingVerification();
  }
  if (digitalRead(FLASH_BUTTON_PIN) == LOW) {
    delay(2000);  // Debounce
    if (digitalRead(FLASH_BUTTON_PIN) == LOW) {
      nowifi = 0;
      ICSC.send(8, 'N', 1, (char *)&nowifi);
      WiFiManager wifiManager;
      digitalWrite(LED_PIN, LOW);
      wifiManager.resetSettings();
      delay(100);  // small delay to allow E11() to finish
      ESP.restart();
    }
  }

  // Only make HTTP requests at intervals to avoid overwhelming the server
  if (millis() - lastHttpRequest < httpInterval) {
    return;
  }
  lastHttpRequest = millis();
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    wifiWasConnected = true;
    wifiDisconnectedTime = 0;  // Reset disconnect timer
  }



  if (hours_data != prev_sessionTime_data) {
    prev_sessionTime_data = sessionTime;
    sessionTime = hours_data;
  }



  if (light_data == 1) {
    lightsOn = true;
  } else lightsOn = false;
  heaterOn = backtoyoutoo_data;
  lightsOn = lighttoyoutoo_data;
  temperature = actualTemperature_data;
  targetTemperature = Temp_data;
  StaticJsonDocument<256> doc;
  doc["id"] = DEVICE_ID;
  doc["temperature"] = temperature;
  doc["sessionTime"] = sessionTime;
  doc["heaterOn"] = heaterOn;
  doc["lightsOn"] = lightsOn;
  doc["temperatureScale"] = temperatureScale;
  doc["targetTemperature"] = targetTemperature;
  doc["apiKey"] = API_KEY;
  doc["maxTemp"] = maxTemp;
  JsonArray errors = doc.createNestedArray("errors");
  if (error1_data > 0 && error1_data <= 10) {
    errors.add("E" + String(error1_data));
    doc["heaterOn"] = false;
    backtoyoutoo_data = false;
  }

  String payload;
  serializeJson(doc, payload);

  // Begin HTTP connection fresh each time
  // Serial.println("[HTTP] Sending PUT request to server...");
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("API-Key", API_KEY);
  http.setTimeout(5000);

  int httpResponseCode = http.PUT(payload.c_str());
  // Serial.print("[HTTP] Response code: ");
  // Serial.println(httpResponseCode);

  if (httpResponseCode == 200) {
    updateInternetStatus(true);

    String response = http.getString();

    responseDoc.clear();
    DeserializationError error = deserializeJson(responseDoc, response);
    if (error) return;

    JsonObject commandsObj = responseDoc["commands"];

    if (!commandsObj.isNull()) {

      if (commandsObj.containsKey("setSessionTime")) {
        sessionTime = commandsObj["setSessionTime"].as<int>();
        ICSC.send(8, 'ct', sizeof(sessionTime), (char *)&sessionTime);
        hours_data = sessionTime;
      }

      if (commandsObj.containsKey("setTemperature")) {
        targetTemperature = commandsObj["setTemperature"].as<int>();
        // Safety limit: cap at maxTemp
        if (targetTemperature > maxTemp) {
          targetTemperature = maxTemp;
        }
        if (targetTemperature < 30) {
          targetTemperature = 30;
        }
        ICSC.send(8, 'TT', sizeof(targetTemperature), (char *)&targetTemperature);
      }

      if (commandsObj.containsKey("setHeater")) {
        heaterOn = commandsObj["setHeater"].as<bool>();
        buttonFunction();
      }

      if (commandsObj.containsKey("setLights")) {
        lightsOn = commandsObj["setLights"].as<bool>();
        lightFunction();
      }
    }

  } else {
    updateInternetStatus(false);
  }

  http.end();
}

void lightFunction() {
  lighttoyou = lightsOn;
  // Serial.print("[FUNCTION] Light control: ");
  // Serial.println(lighttoyou ? "ON" : "OFF");
  ICSC.send(8, 'E', 1, (char *)&lighttoyou);
}

void buttonFunction() {
  power = heaterOn ? 4 : 5;
  // Serial.print("[FUNCTION] Heater control: ");
  // Serial.println(heaterOn ? "ON (4)" : "OFF (5)");
  ICSC.send(5, 'W', 1, (char *)&power);
}

void hours(unsigned char src, char command, unsigned char len, char *data) {
  hours_data = *(unsigned long *)data;
  ICSC.send(9, 'H', 5, (char *)&hours_data);
}

void minutes(unsigned char src, char command, unsigned char len, char *data) {
  minutes_data = *data;
  // Serial.print("[ICSC] Received minutes: ");
  // Serial.println(minutes_data);
}
void seconds(unsigned char src, char command, unsigned char len, char *data) {
  seconds_data = *data;
  // Serial.print("[ICSC] Received seconds: ");
  // Serial.println(seconds_data);
}
void actualTemperature1(unsigned char src, char command, unsigned char len, char *data) {
  actualTemperature_data = *data;
}

void backtoyoutoo(unsigned char src, char command, unsigned char len, char *data) {
  backtoyoutoo_data = *(bool *)data;
  // Serial.print("[ICSC] Received heater state: ");
  // Serial.println(backtoyoutoo_data ? "ON" : "OFF");
}
void lighttoyoutoo(unsigned char src, char command, unsigned char len, char *data) {
  lighttoyoutoo_data = *data;
  // Serial.print("[ICSC] Received light state: ");
  // Serial.println(lighttoyoutoo_data ? "ON" : "OFF");
}
void Temp(unsigned char source, char command, unsigned char len, char *data) {
  Temp_data = *(int *)data;
  // Safety limit: cap at maxTemp
  if (Temp_data > maxTemp) {
    Temp_data = maxTemp;
  }
  if (Temp_data < 30) {
    Temp_data = 30;
  }
}
void error1(unsigned char src, char command, unsigned char len, char *data) {
  error1_data = *data;
  // Serial.print("[ICSC] Received error code: ");
  // Serial.println(error1_data);
}
void buttonOnPressedInterface(unsigned char source, char command, unsigned char length, char *data) {
  buttonOnPressedInterface_data = *(int *)data;
  if (buttonOnPressedInterface_data == 2)
    backtoyoutoo_data = true;
  else
    backtoyoutoo_data = false;
}
void light(unsigned char source, char command, unsigned char length, char *data) {
  light_data = *data;
}
void handleWiFiReconnect() {

  static unsigned long lastReconnect = 0;
  const unsigned long interval = 5000;

  if (WiFi.status() != WL_CONNECTED) {

    if (wifiDisconnectedTime == 0)
      wifiDisconnectedTime = millis();

    if (millis() - lastReconnect >= interval) {
      lastReconnect = millis();
      WiFi.reconnect();
    }

    if (wifiWasConnected && millis() - wifiDisconnectedTime >= wifiReconnectTimeout) {

      WiFiManager wm;
      wm.setConfigPortalTimeout(0);

      if (!wm.startConfigPortal(wifiAPName.c_str())) {
        delay(3000);
        ESP.restart();
      }

      wifiDisconnectedTime = 0;
      wifiWasConnected = true;
    }
  } else {
    wifiWasConnected = true;
    wifiDisconnectedTime = 0;
  }
}
