#include <DHT.h>
DHT dht2(2,DHT11);

void setup()  
{  
	Serial.begin(115200);
	dht2.begin();
}  
void loop()  
{  
	Serial.print("Temperature: ");  
	Serial.print((dht2.readTemperature()));
	Serial.print("*C");
	Serial.print("\tHumidity:");
	Serial.print((dht2.readHumidity()));
	Serial.print("%\n");
	delay(1000);  
}  