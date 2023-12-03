#include "INDINF.h"
#include "EasyCAT.h"
#include <SPI.h>


EasyCAT EASYCAT;

const int sharpPin = A0; // Der Sensor ist am analogen Pin A0 angeschlossen
float voltage;
float distance;



unsigned long PreviousMillis = 0;

void setup()
{
  Serial.begin(9600);

  Serial.print("\nEasyCAT - Generic EtherCAT slave\n");


  if (EASYCAT.Init() == true)
  {
    Serial.print("initialized");
  }
  else
  {
    Serial.print("initialization failed");
    pinMode(13, OUTPUT);
    while (1)
    {
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
    }
  }

  PreviousMillis = millis();
}

void loop()
{
  EASYCAT.MainTask();

  int sensorValue = analogRead(sharpPin);
  voltage = sensorValue * (5.0 / 1023.0);

  distance = 27.86 * pow(voltage, -1.15);

  Serial.print("Entfernung: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Fügen Sie die folgende Zeile hinzu, um die Variable distance in den EtherCAT-Datenpuffer zu schreiben.
  EASYCAT.BufferIn.Float[0] = distance;

  delay(100);
}
