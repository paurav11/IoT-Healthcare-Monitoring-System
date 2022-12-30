#include <MQ2.h> // MQ2 Gas Sensor Library
  
int pinAout = A0; // pin A0 of NodeMcu is connected to pin A0 of MQ-2
float LPG, CO, Smoke; // Variable values of lpg, CO-gas, and Smoke
  
MQ2 mq2(pinAout); //Declare pin A0 connected to A0 pin Arduino
  
void setup(){
 
   Serial.begin(115200); // Baudrate to display data on serial monitor
   mq2.begin(); // Instructions to start the MQ2 sensor
   pinMode(pinAout,INPUT); //Declare pin A0 as input
}
  
void loop(){
	
   float* values= mq2.read(true); //if set to "false" will not appear on serial monitor
   
   LPG = mq2.readLPG();
   CO = mq2.readCO();
   Smoke = mq2.readSmoke();
   delay(1000);
}

