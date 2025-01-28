#include <LiquidCrystal_I2C.h>
#include <GyverNTC.h>

#define but_Up 8 //Кнопка вверх D8
#define but_Down 9 //Кнопка вверх D9

LiquidCrystal_I2C LCD(0x27,20,4); //порты дисплея SDA – A4, SCL – A5

GyverNTC ntc(A1, 9980, 3950, 25, 10000);

float tempMemory = 0;

void setup()
 {
  
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0,0);
  LCD.print("Hello, world!");
  delay(1000);

  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Temp:");

  pinMode(but_Up, INPUT_PULLUP);
  pinMode(but_Down, INPUT_PULLUP);

}

void loop() {
  
  LCD.setCursor(10,0);

  float t = ntc.getTemp();
  LCD.print(t);
  delay(1000);

  bool btUp = digitalRead(but_Up);

  if (!btUp)
  {    
    delay(150);
    Update_tempMemory(true, t);
  }

  bool btDw = digitalRead(but_Down);

  if (!btDw)
  {    
    delay(150);    
    Update_tempMemory(false, t);
  }

  CheckTemperature(t);
}

void Update_tempMemory(bool up, float t)
{
  if (tempMemory == 0) tempMemory = round(t * 10) / 10;

  if (up) tempMemory += 0.1;
  else tempMemory -= 0.1;

  LCD.setCursor(10,1);
  LCD.print(tempMemory);
}

void CheckTemperature(float t)
{
  if (tempMemory != 0 && tempMemory <= t)
  {
    LCD.setCursor(2,1);
    LCD.print("*");
  } else
  {
    LCD.setCursor(2,1);
    LCD.print(" ");
  }
}
