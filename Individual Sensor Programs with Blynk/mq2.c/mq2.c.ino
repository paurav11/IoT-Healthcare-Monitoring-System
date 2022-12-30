// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLv--PvCdt"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "WjaF-SaocHEmQEtQCBezzQe-RVE68MbI"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <MQ2.h> // MQ2 Gas Sensor Library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

int pinAout = A0; // pin A0 of NodeMcu is connected to pin A0 of MQ-2
float LPG, CO, Smoke; // Variable values of lpg, CO-gas, and Smoke
  
MQ2 mq2(pinAout); //Declare pin A0 connected to A0 pin Arduino

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncAll();
  // Blynk.syncVirtual(V0);
  // Blynk.syncVirtual(V1);
  // Blynk.syncVirtual(V2);
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
  Blynk.virtualWrite(V3, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  mq2.begin(); // Instructions to start the MQ2 sensor
  pinMode(pinAout,INPUT); //Declare pin A0 as input
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  float* values= mq2.read(true); //if set to "false" will not appear on serial monitor
    
  LPG = mq2.readLPG();
  CO = mq2.readCO();
  Smoke = mq2.readSmoke();
  Blynk.virtualWrite(V0, LPG);
  Blynk.virtualWrite(V1, CO);
  Blynk.virtualWrite(V2, Smoke);
  Blynk.run();
  timer.run();
  delay(1000);
}
