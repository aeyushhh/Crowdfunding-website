#define BLYNK_TEMPLATE_ID "TMPL3RZy_erlP"
#define BLYNK_TEMPLATE_NAME "Smart Agriculture Monitoring"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <Simpletimer.h>
#include <DHT.h>

char auth[] = "nhYE8ZF5dT1auyr8qSJhDX5lB8cQu4Zr"; // Authentication code sent by Blynk
char ssid[] = "Eyan";                            // WiFi SSID
char pass[] = "43994388";                        // WiFi Password

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

#define sensorPin D3
int sensorState = 0;
int lastState = 0;
int sensor = 0;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h); // V5 is for Humidity
  Blynk.virtualWrite(V6, t); // V6 is for Temperature
}

void sendTemps()
{
  sensor = analogRead(A0);
  Blynk.virtualWrite(V1, sensor);
  delay(1000);
}

// void checkSoilMoisture()
// {
//   sensorState = digitalRead(sensorPin);
//   Serial.println(sensorState);

//   if (sensorState == 1 && lastState == 0)
//   {
//     Serial.println("Needs water, send notification");
//     Blynk.notify("Water your plants");
//     lastState = 1;
//     delay(1000); // Send notification delay
//   }
//   else if (sensorState == 1 && lastState == 1)
//   {
//     Serial.println("Has not been watered yet");
//     delay(1000);
//   }
//   else
//   {
//     Serial.println("Does not need water");
//     lastState = 0;
//     delay(1000);
//   }
// }



void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(sensorPin, INPUT);
  dht.begin();

  timer.setInterval(1000L, sendSensor);
  timer.setInterval(2000L, sendTemps);
}

void loop()
{
  Blynk.run();
  timer.run();
  // checkSoilMoisture();
  delay(100);
}
