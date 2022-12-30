// Include Libraries
#include <MQ2.h> // MQ2 Gas Sensor Library
#include <DHT.h> // DHT11 Sensor Library

// Pin Definitions
#define ECG_SENSOR_PIN	A0
#define MQ2_SENSOR_PIN	0
#define DHT11_SENSOR_PIN 2

// define vars
long menuOption = 0L;
float LPG, CO, Smoke; // Variable values of lpg, CO-gas, and Smoke
float temperature, humidity;

MQ2 mq2(MQ2_SENSOR_PIN);
DHT dht2(2, DHT11);

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
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{       
    if(menuOption == 1)
    {
      float myecg = analogRead(ECG_SENSOR_PIN);
      Serial.println(myecg);
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
    }
    else {
        Serial.println("Invalid Input!"); 
    }
    delay(1000);
}