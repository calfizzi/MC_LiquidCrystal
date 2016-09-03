
/************************************************************************************************************************
  File        : MC_LiquidCrystal_I2C.h
  File type   : Arduino Library
  Developed By: Mario Calfizzi
  Description : This is the core of LiquidCrystal library to manage 16x2 and 20x4 LCD Displays for arduino
  Based On    : YWROBOT Version...
                +-----------------------------------------------------------------------------------------------+  
                | YWROBOT Original infos:                                                                       |
                | last updated on 21/12/2011                                                                    |
                | Tim Starling Fix the reset bug (Thanks Tim)                                                   |
                | wiki doc http://www.dfrobot.com/wiki/index.php?title=I2C/TWI_LCD1602_Module_(SKU:_DFR0063)    |
                | Support Forum: http://www.dfrobot.com/forum/                                                  |
                | Compatible with the Arduino IDE 1.0                                                           |
                | Library version:1.1                                                                           |
                +-----------------------------------------------------------------------------------------------+  
  
  Constructors:
    MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr,       Standard Constructor if use wire library 
                            uint8_t lcd_cols,       lcd_Addr          => Hardware Address of Display 
                            uint8_t lcd_rows);      lcd_cols/lcd_rows => identify the size of the display 
                                                    
    MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr,       Standard Constructor if use MC_I2C_Simple library
                            uint8_t lcd_cols,       lcd_Addr          => Hardware Address of Display 
                            uint8_t lcd_rows,       lcd_cols/lcd_rows => identify the size of the display
                            uint8_t SDA_PIN = 4,    SDA_PIN           => you can use any pin of arduino
                            uint8_t SCL_PIN = 5);   SCL_PIN           => you can use any pin of arduino

  Methods:
    void   begin              ( uint8_t cols,       Start the device.
                                uint8_t rows,       lcd_cols/lcd_rows => identify the size of the display
                                uint8_t charsize    charsize          => is the chirsize typology of the Display
                                = LCD_5x8DOTS );    
    void   clear              ( void );             Clear the display Screen
    void   home               ( void );             Move cursor to the top left side of the display 
    void   noDisplay          ( void );             Turn off the display
    void   display            ( void );             Turn on the display
    void   blink              ( void );             Turn on the Cursor Blinking
    void   noBlink            ( void );             Turn off the Cursor Blinking
    void   cursor             ( void );             Turn on the Cursor on the display
    void   noCursor           ( void );             Turn off the Cursor on the display
    void   scrollDisplayLeft  ( void );             Scroll the characters on the Display to left
    void   scrollDisplayRight ( void );             Scroll the characters on the Display to right
    void   printLeft          ( void );             Print the characters on the Display from left
    void   printRight         ( void );             Print the characters on the Display from right
    void   leftToRight        ( void );             
    void   rightToLeft        ( void );
    void   shiftIncrement     ( void );
    void   shiftDecrement     ( void );
    void   backlight          ( void );             Turn on the Back Light of the display
    void   noBacklight        ( void );             Turn off the Back Light of the display
    void   autoscroll         ( void );             Turn on the Auto Scroll of the display
    void   noAutoscroll       ( void );             Turn off the Auto Scroll of the display
    void   createChar         ( uint8_t location,   Define your own Character Set
                                uint8_t charmap[]); location => 0-7, charmap is 8 byte map
    void   setCursor          ( uint8_t col,        Set the cursor position
                                uint8_t row);        
    size_t write              ( uint8_t);           Directly write to the Display Memory
    void   command            ( uint8_t);           Directly send a specific command to the Display
    void   init               ( void );             Initialize the Display. 

  Compatibility Methods aliases:
    void    blink_on              ( void );             alias for blink()
    void    blink_off             ( void );             lias for noBlink()
    void    cursor_on             ( void );             lias for cursor()
    void    cursor_off            ( void );             lias for noCursor()
    void    setBacklight          ( uint8_t new_val);   lias for backlight() and nobacklight()
    void    load_custom_character ( uint8_t char_num,   alias for createChar()
                                    uint8_t *rows);	      
    void    printstr              ( const char[]);
*************************************************************************************************************************/


#pragma once
#ifndef MC_LiquidCrystal_I2C_h
#define MC_LiquidCrystal_I2C_h

#include <inttypes.h>
#include <Print.h>

#define USE_MC_I2C_Simple 1


#if USE_MC_I2C_Simple
  #include "MC_I2C_Simple.h"
#else
  #include <Wire.h>
#endif

// commands
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

// flags for function set
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

// flags for backlight control
#define LCD_BACKLIGHT           0x08
#define LCD_NOBACKLIGHT         0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

class MC_LiquidCrystal_I2C : public Print {
public:
#ifdef TwoWire_h
                  MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
#else
                  MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t SDA_PIN = 4, uint8_t SCL_PIN=5);
#endif
  void            begin                 ( uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
  void            clear                 ( void );
  void            home                  ( void );
  void            noDisplay             ( void );
  void            display               ( void );
  void            noBlink               ( void );
  void            blink                 ( void );
  void            noCursor              ( void );
  void            cursor                ( void );
  void            scrollDisplayLeft     ( void );
  void            scrollDisplayRight    ( void );
  void            printLeft             ( void );
  void            printRight            ( void );
  void            leftToRight           ( void );
  void            rightToLeft           ( void );
  void            shiftIncrement        ( void );
  void            shiftDecrement        ( void );
  void            noBacklight           ( void );
  void            backlight             ( void );
  void            autoscroll            ( void );
  void            noAutoscroll          ( void ); 
  void            createChar            ( uint8_t location, uint8_t charmap[]);
  void            setCursor             ( uint8_t col, uint8_t row); 
#if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t  write                 ( uint8_t);
#else
  virtual void    write                 ( uint8_t );
#endif
  void            command               ( uint8_t);
  void            init                  ( void );

  ////compatibility API function aliases
  void            blink_on              ( void );						                // alias for blink()
  void            blink_off             ( void );       					          // alias for noBlink()
  void            cursor_on             ( void );      	 					          // alias for cursor()
  void            cursor_off            ( void );      					            // alias for noCursor()
  void            setBacklight          ( uint8_t new_val);				          // alias for backlight() and nobacklight()
  void            load_custom_character ( uint8_t char_num, uint8_t *rows);	// alias for createChar()
  void            printstr              ( const char[]);

  ////Unsupported API functions (not implemented in this library)
  uint8_t         status                ( void );
  void            setContrast           ( uint8_t new_val);
  uint8_t         keypad                ( void );
  void            setDelay              ( int, int);
  void            on                    ( void );
  void            off                   ( void );
  uint8_t         init_bargraph         ( uint8_t graphtype);
  void            draw_horizontal_graph ( uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
  void            draw_vertical_graph   ( uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
	 

private:
  void            init_priv             ( void );
  void            send                  ( uint8_t, uint8_t);
  void            write4bits            ( uint8_t);
  void            expanderWrite         ( uint8_t);
  void            pulseEnable           ( uint8_t);
#ifdef MC_I2C_Simple_h
  MC_I2C_Simple   Wire;
  uint8_t         _SDA;
  uint8_t         _SCL;
#endif
  uint8_t         _Addr;
  uint8_t         _displayfunction;
  uint8_t         _displaycontrol;
  uint8_t         _displaymode;
  uint8_t         _numlines;
  uint8_t         _cols;
  uint8_t         _rows;
  uint8_t         _backlightval;
};

#endif
