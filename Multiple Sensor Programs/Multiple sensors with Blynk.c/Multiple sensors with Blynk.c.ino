// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLv--PvCdt"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "WjaF-SaocHEmQEtQCBezzQe-RVE68MbI"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

// Pin Definitions
#define ECG_SENSOR_PIN	A0
#define MQ2_SENSOR_PIN	0
#define DHT11_SENSOR_PIN 2

// Include Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MQ2.h> // MQ2 Gas Sensor Library
#include <DHT.h> // DHT11 Sensor Library

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// define vars
long menuOption = 0L;
float LPG, CO, Smoke; // Variable values of lpg, CO-gas, and Smoke
float temperature, humidity;

MQ2 mq2(MQ2_SENSOR_PIN);
DHT dht2(2, DHT11);

BlynkTimer timer;

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncAll();
  // Blynk.syncVirtual(V0);
  // Blynk.syncVirtual(V1);
  // Blynk.syncVirtual(V2);
  // Blynk.syncVirtual(V3);
  // Blynk.syncVirtual(V4);
  // Blynk.syncVirtual(V5);
  // Change Web Link Button message to "Congratulations!"
  // Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  // Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  // Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, millis()/1000);
}

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    Serial.begin(115200);    
    Serial.println(F("\nPlease select a sensor:"));
    Serial.println(F("(1) Analog Heart Rate Monitor Sensor (ECG)"));
    Serial.println(F("(2) MQ-2 - Gas Sensor"));
    Serial.println(F("(3) DHT11 Sensor"));
    Serial.println(F("Please provide your input in Serial monitor message input field to test particular sensor!"));

    // Read data from serial monitor
    while (!Serial.available())
    {    
        menuOption = Serial.parseInt();
        if(menuOption == 1)
        {
          Serial.println(F("Now Testing Analog Heart Rate Monitor Sensor (ECG)"));
          pinMode(ECG_SENSOR_PIN,INPUT);
        } 
        else if(menuOption == 2)
        {
          Serial.println(F("Now Testing MQ-2 - Gas Sensor"));
          pinMode(MQ2_SENSOR_PIN,INPUT);
          mq2.begin(); // Instructions to start the MQ2 sensor
        } 
        else if(menuOption == 3)
        {
          Serial.println(F("Now Testing DHT11 Sensor"));
          pinMode(DHT11_SENSOR_PIN,INPUT);
          dht2.begin();
        }        
    }

     // Assign the pin as INPUT 
    Blynk.begin(auth, ssid, pass);
    
    // You can also specify server:
    //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

    // Setup a function to be called every second
    timer.setInterval(1000L, myTimerEvent);
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{       
    if(menuOption == 1)
    {
      float myecg = analogRead(ECG_SENSOR_PIN);
      Serial.println(myecg);
      Blynk.virtualWrite(V0, myecg);
    } 
    else if(menuOption == 2)
    {
      float* values = mq2.read(true); //if set to "false" will not appear on serial monitor
      LPG = mq2.readLPG();
      CO = mq2.readCO();
      Smoke = mq2.readSmoke();
      Serial.print("LPG: ");  
      Serial.print(LPG);
      Serial.print("ppm");
      Serial.print("\tCO:");
      Serial.print(CO);
      Serial.print("ppm");
      Serial.print("\tSmoke:");
      Serial.print(Smoke);
      Serial.print("ppm\n");
      Blynk.virtualWrite(V1, LPG);
      Blynk.virtualWrite(V2, CO);
      Blynk.virtualWrite(V3, Smoke);
    } 
    else if(menuOption == 3)
    {
      temperature = dht2.readTemperature();
      humidity = dht2.readHumidity();
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print("*C");
      Serial.print("\tHumidity:");
      Serial.print(humidity);
      Serial.print("%\n");
      Blynk.virtualWrite(V4, temperature);
      Blynk.virtualWrite(V5, humidity);
    }
    else {
        Serial.println("Invalid Input!"); 
    }
    Blynk.run();
    timer.run();
    delay(1000);
}