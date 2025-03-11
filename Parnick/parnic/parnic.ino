
#include <GyverOLED.h>
#include <DHT.h>

GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

DHT dht(2, DHT22);
int dhtIt = 0;

float OutTemp;
float OutHum;

void setup() {
  // put your setup code here, to run once:
  oled.init();        // инициализация

  dht.begin();

  updateOutTempHum();

  updateDisplay();

  Serial.begin(9600);
  Serial.println(F("DHT test!"));
}

void loop() {
  
  dhtIt++;

  if (dhtIt >= 2000)
  {
    
    //updateOutTempHum();
    updateDisplay();
    
  }

}

void updateDisplay()
{
  oled.clear();       // очистка
  oled.setScale(1);   // масштаб текста (1..4)
  // прямоугольник 1
  oled.roundRect(0, 1, 24, 31, OLED_STROKE);
  //oled.setCursorXY(10, 8);
  //oled.print("1");
  float a0 = analogRead(0);
  a0 = round(100-a0*100/1023);
  oled.setCursorXY(4, 14);
  oled.print(int(a0));

  // прямоугольник 2
  oled.roundRect(26, 1, 50, 31, OLED_STROKE);
  oled.setCursorXY(36, 8);
  oled.print("2");

  // прямоугольник 3
  oled.roundRect(52, 1, 76, 31, OLED_STROKE);
  oled.setCursorXY(61, 8);
  oled.print("3");

  // прямоугольник 4
  oled.roundRect(78, 1, 102, 31, OLED_STROKE);
  oled.setCursorXY(86, 8);
  oled.print("4");

  // прямоугольник 5
  //oled.roundRect(104, 1, 127, 31, OLED_STROKE);
  oled.setCursorXY(105, 7);
  oled.print(OutTemp);
  oled.setCursorXY(105, 20);
  oled.print(OutHum);
}

void updateOutTempHum()
{
  float h = dht.readHumidity();  
  float t = dht.readTemperature();

  if (isnan(h)) OutHum = 0;
  else OutHum = h;

  if (isnan(t)) OutTemp = 0;
  else OutTemp = t;

  Serial.print(F("\nHumidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);

  delay(6000);
}