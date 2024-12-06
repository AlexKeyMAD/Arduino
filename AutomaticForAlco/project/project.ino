#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  //порт датчика температуры (данные) D2
#define term_power 4    // порт датчика температуры (питание) D4

LiquidCrystal_I2C LCD(0x27,20,4); //порты дисплея SDA – A4, SCL – A5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temp(&oneWire);

void setup()
 {
  
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0,0);
  LCD.print("Hello, world!");
  delay(1000);

  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Temperature");

  //Serial.begin(9600);
  temp.begin();
  pinMode(term_power, OUTPUT);

  digitalWrite(term_power, HIGH);
  temp.requestTemperatures();
}

void loop() {
  
  temp.requestTemperatures();
  LCD.setCursor(12,0);

  float t = temp.getTempCByIndex(0);
  LCD.print(t);
  delay(1000);

}
