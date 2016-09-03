/*
 Name:		HelloWorld.ino
 Created:	8/29/2016 2:37:07 PM
 Author:	monkey
*/
//#include <wire.h>
#include <MC_LiquidCrystal_I2C.h>
#include <MC_LiquidCrystal/MC_I2C_Simple.h>

#define LCD20x4  0

#if     LCD20x4  
#define  LCD_ROWS 4
#define  LCD_COLS 20
#else
#define  LCD_ROWS 2
#define  LCD_COLS 16
#endif

#define LCT_SDA A4
#define LCT_SCL 13


#ifdef TwoWire_h 
  MC_LiquidCrystal_I2C lcd (0x3F, 16, 2);
#else
    MC_LiquidCrystal_I2C lcd (0x3F, LCD_COLS, LCD_ROWS, LCT_SDA, LCT_SCL);
#endif

// the setup function runs once when you press reset or power the board
void _Scrool(char*str)
{
  lcd.autoscroll();
  for (size_t i=0; i<strlen(str); i++)
  {
    lcd.print(str[i]);
    delay (200);
  }
}


uint8_t Char1[8][8] = 
{
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    B00000000,
    B00000110,
    B00000111,
    B00000111,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  {
    B00000000,
    B00000110,
    B00000111,
    B00000111,
    B00000111,
    B00000111,
    B00000110,
    B00000000
  },
  {
    B00000000,
    B00000110,
    B00000111,
    B00000111,
    B00011111,
    B00011111,
    B00001110,
    B00000000
  },
  {
    B00000000,
    B00001110,
    B00011111,
    B00011111,
    B00011111,
    B00011111,
    B00001110,
    B00000000
  },
  {
    B00000000,
    B00001100,
    B00011100,
    B00011100,
    B00011111,
    B00011111,
    B00001110,
    B00000000
  },
  {
    B00000000,
    B00001100,
    B00011100,
    B00011100,
    B00011100,
    B00011100,
    B00001100,
    B00000000
  },
  {
    B00000000,
    B00001100,
    B00011100,
    B00011100,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
};

void setup() {
  //Serial.begin(115200);
  lcd.init();
  lcd.clear();
  lcd.home();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello Guy!!!");
  lcd.setCursor(0, 1);
  lcd.print("Arduino Is Here!");
#if LCD20x4
  lcd.setCursor(0, 2);
  lcd.print("--------------------");
  lcd.setCursor(0, 3);
  lcd.print("Starting.....");
#endif
  delay (1000);
  for (int i=0; i<LCD_COLS; i++)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  for (int i=0; i<LCD_COLS; i++)
  {
    lcd.scrollDisplayRight();
    delay(200);
  }
  delay (1000);
  lcd.rightToLeft();
}

void loop() 
{
  static uint8_t count = 0;
  static uint32_t   ms = millis();
  if (millis()-ms>150)
  {
    count = count % 8;
    lcd.createChar(0,Char1[count]);
    lcd.setCursor(15, 0);
    lcd.print((char)0 );
    count++;
    ms = millis();
  }
}
