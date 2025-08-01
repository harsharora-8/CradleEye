/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL3jUUTES1r"
#define BLYNK_TEMPLATE_NAME "Tiny Trekker"
#define BLYNK_AUTH_TOKEN "V3Hii3RKBu1y82GRJkjKqV1V7k5paQ0p"

// Your WiFi Credentials.
char ssid[] = "malik";      // Your Wi-Fi network name
char pass[] = "malik123";      // Your Wi-Fi password

// Include necessary libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Define sensor and pin configurations
#define MQ2_SENSOR A0    // Gas sensor pin
#define RAIN_SENSOR D1   // Rain sensor pin
#define PIR_SENSOR D4    // PIR motion sensor pin
#define DHTPIN D3        // DHT11 sensor pin
#define DHTTYPE DHT11    // DHT sensor type
#define FAN_PIN D6       // Fan control pin (connected to relay)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Blynk virtual pins for sensors and fan
#define VPIN_TEMPERATURE V0
#define VPIN_MICROPHONE V1
#define VPIN_HUMIDITY V2
#define VPIN_FAN_CONTROL V3

// Initialize variables
float temperature = 0.0;
float humidity = 0.0;
int soundLevel = 0;
bool isFanOn = false;
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// Fan control function (triggered from Blynk)
BLYNK_WRITE(VPIN_FAN_CONTROL) {
  int fanState = param.asInt();  // Get the value from the Blynk app (0 or 1)
  if (fanState == 1) {
    digitalWrite(FAN_PIN, HIGH);  // Turn on fan
    isFanOn = true;
  } else {
    digitalWrite(FAN_PIN, LOW);   // Turn off fan
    isFanOn = false;
  }
}

void checkBlynkStatus() {
  // Get all sensor data
  getSensorData();
  
  // Check connection status
  if (Blynk.connected()) {
    sendSensorData();
  } else {
    Serial.println("Blynk Not Connected");
  }
}

void getSensorData() {
  // Read DHT sensor (temperature & humidity)
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // Microphone sound detection (detects sound level)
  soundLevel = analogRead(A0);  // Adjust this based on microphone analog pin

  // Fan control based on temperature (can be extended as needed)
  if (temperature > 30 && !isFanOn) {
    digitalWrite(FAN_PIN, HIGH);  // Turn on fan if temperature exceeds 30°C
    isFanOn = true;
    Blynk.virtualWrite(VPIN_FAN_CONTROL, 1);  // Update the fan status in Blynk
  } else if (temperature <= 30 && isFanOn) {
    digitalWrite(FAN_PIN, LOW);   // Turn off fan if temperature is below 30°C
    isFanOn = false;
    Blynk.virtualWrite(VPIN_FAN_CONTROL, 0);  // Update the fan status in Blynk
  }
}

void sendSensorData() {
  // Send temperature and humidity data to Blynk
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature);  // Send temperature to V0
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity);        // Send humidity to V2
  Blynk.virtualWrite(VPIN_MICROPHONE, soundLevel);    // Send Sound Data to V1
  // Handle GAS_SENSOR event
  int gasStatus = analogRead(MQ2_SENSOR);
  if (gasStatus > 400) { // Customize the threshold based on gas sensor sensitivity
    Blynk.logEvent("gas_sensor", "Gas detected!");
    Serial.println("Gas detected!");
  } else {
    Serial.println("No gas detected");
  }
  
  // Handle RAIN_SENSOR event
  int rainStatus = digitalRead(RAIN_SENSOR);
  if (rainStatus == LOW) { // LOW means rain detected
    Blynk.logEvent("rain_sensor", "Baby Peed!");
    Serial.println("Baby Peed");
  } else {
    Serial.println("No Peed Detected");
  }

  // Handle PIR_SENSOR event (motion detection)
  int pirStatus = digitalRead(PIR_SENSOR);
  if (pirStatus == HIGH) {
    Blynk.logEvent("pir_sensor", "Slight Motion detected!");
    Serial.println("Slight Motion detected!");
  } else {
    Serial.println("No motion detected");
  }

  // Handle Baby Crying event (sound level)
  if (soundLevel > 700) {
    Blynk.logEvent("baby_crying", "Baby is crying!");
    Serial.println("Baby is crying!");
  } else {
    Serial.println("No baby crying");
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Sensor initialization
  pinMode(FAN_PIN, OUTPUT);
  pinMode(RAIN_SENSOR, INPUT);
  pinMode(PIR_SENSOR, INPUT);
  dht.begin();  // Start DHT sensor

  // Wi-Fi and Blynk setup
  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus);  // Call every 2 seconds
  Blynk.config(auth);
  delay(10000);
}

void loop() {
  Blynk.run();
  timer.run();
}
