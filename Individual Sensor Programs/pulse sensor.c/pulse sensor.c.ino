void setup()
{
  // Debug console
  Serial.begin(115200);
}

void loop()
{
  float h = analogRead(A0);
  if (isnan(h))
  {
    Serial.println("Failed to read from Pulse Sensor!");
    return;
  }
  Serial.print("Heart Rate: ");
  Serial.println(h/1023*100);
  delay(1000);
}