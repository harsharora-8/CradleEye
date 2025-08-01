#include <DHT.h>

// Define pins
#define DHTPIN D3             // DHT11 Data pin connected to D3 (GPIO0)
#define PIRPIN D4             // PIR sensor OUT connected to D4 (GPIO2)
#define RAIN_SENSOR_PIN D0    // Rain sensor connected to D0 (GPIO16)
#define GAS_SENSOR_PIN D5     // Gas sensor connected to D5 (GPIO14)
#define MIC_PIN A0            // Microphone MAX4466 connected to A0

// Define DHT type
#define DHTTYPE DHT11         // DHT11 sensor type

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Set PIR pin as INPUT
  pinMode(PIRPIN, INPUT);
  
  // Set rain sensor pin as INPUT
  pinMode(RAIN_SENSOR_PIN, INPUT);
  
  // Set gas sensor pin as INPUT
  pinMode(GAS_SENSOR_PIN, INPUT);
  
  // Notify that the sensors are starting
  Serial.println("Sensors are starting...");
}

void loop() {
  // ------------------- DHT Sensor -------------------
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // Default in Celsius

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print the results to the Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }

  // ------------------- PIR Sensor -------------------
  // Read the PIR sensor input
  int pirState = digitalRead(PIRPIN);

  // If motion is detected
  if (pirState == HIGH) {
    Serial.println("Motion detected!");
  } else {
    Serial.println("No motion");
  }

  // ------------------- Rain Sensor -------------------
  // Read the digital value from the rain sensor
  int rainStatus = digitalRead(RAIN_SENSOR_PIN);

  // Check if rain is detected
  if (rainStatus == LOW) {  // Sensor sends LOW when rain is detected
    Serial.println("Rain detected!");
  } else {
    Serial.println("No rain.");
  }

  // ------------------- Microphone -------------------
  // Read the analog value from the microphone
  int soundLevel = analogRead(MIC_PIN);

  // Check if the sound level exceeds 700
  if (soundLevel > 700) {
    Serial.println("Baby is crying!");
  } else {
    Serial.println("No noise.");
  }

  // ------------------- Gas Sensor -------------------
  // Read the digital value from the gas sensor
  int gasStatus = digitalRead(GAS_SENSOR_PIN);

  // Check if gas is detected
  if (gasStatus == LOW) {
    Serial.println("Gas detected!");
  } else {
    Serial.println("No gas detected.");
  }

  // Wait before the next loop iteration
  delay(100);
}
