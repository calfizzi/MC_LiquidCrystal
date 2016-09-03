# MC_LiquidCrystal
  MC_LiquidCrystal digital Liquid Crystal Display Library - Arduino Library
  Download and try the class MC_LiquidCrystal to manage any Liquid Crystal (16x2 or 20x4) display...

# MC_I2C_Simple Class
##   Constructors:
    MC_I2C_Simple (uint8_t SDA_PIN, uint8_t SCL_PIN)  You can set SDA SCL Pin 

##   Methods:
    void begin  ( uint8_t DeviceFisicalAddress);      Set Hardware Address
    
    void begin  ( uint8_t DeviceFisicalAddress, 
                  uint8_t SDA_PIN, uint8_t SCL_PIN);  Set Hardware Address and SCA/SCL Pins
                  
    int  write  ( uint8_t Data);                      Write a Byte via I2C using Hardware Address setted.
                                                      Return 1 if no error
                                                                      
    int  write  ( uint8_t address, uint8_t Data);     Write a Byte via I2C on an internal dispositive register  
                                                      address using Hardware Address setted.
                                                      if no error returns 1 
                                                                      
    int  write  ( uint8_t address, uint8_t *buffer,   Write a list of Bytes via I2C on an internal dispositive
                  uint8_t size);                      register address using Hardware Address setted. 
                                                      if no error returns number of bytes wrote 
                                                      
    int  read   ( uint8_t address, uint8_t *buffer,   Read a list of Bytes via I2C on an internal dispositive
                  uint8_t size);                      register address using Hardware Address setted.  
                                                      if no error returns number of bytes read

                                                      
# MC_LiquidCrystal_I2C Class
##   Constructors:
    MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr,         Standard Constructor if use wire library 
                            uint8_t lcd_cols,         lcd_Addr          => Hardware Address of Display 
                            uint8_t lcd_rows);        lcd_cols/lcd_rows => identify the size of the display 
                            
    MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr,         Standard Constructor if use MC_I2C_Simple library
                            uint8_t lcd_cols,         lcd_Addr          => Hardware Address of Display 
                            uint8_t lcd_rows,         lcd_cols/lcd_rows => identify the size of the display
                            uint8_t SDA_PIN = 4,      SDA_PIN           => you can use any pin of arduino
                            uint8_t SCL_PIN = 5);     SCL_PIN           => you can use any pin of arduino

##   Methods:
  void   begin              ( uint8_t cols, 
                              uint8_t rows, 
                              uint8_t charsize 
                              = LCD_5x8DOTS );
                              
  void   clear              ( void );
  
  void   home               ( void );
  
  void   noDisplay          ( void );
  
  void   display            ( void );
  
  void   noBlink            ( void );
  
  void   blink              ( void );
  
  void   noCursor           ( void );
  
  void   cursor             ( void );
  
  void   scrollDisplayLeft  ( void );
  
  void   scrollDisplayRight ( void );
  
  void   printLeft          ( void );
  
  void   printRight         ( void );
  
  void   leftToRight        ( void );
  
  void   rightToLeft        ( void );
  
  void   shiftIncrement     ( void );
  
  void   shiftDecrement     ( void );
  
  void   noBacklight        ( void );
  
  void   backlight          ( void );
  
  void   autoscroll         ( void );
  
  void   noAutoscroll       ( void ); 
  
  void   createChar         ( uint8_t location, 
                              uint8_t charmap[]);
  void   setCursor          ( uint8_t col, 
                              uint8_t row); 
  size_t write              ( uint8_t);
  void   command            ( uint8_t);
  void   init               ( void );

##   compatibility Methods aliases:
  void    blink_on              ( void );						    alias for blink()
  void    blink_off             ( void );       				alias for noBlink()
  void    cursor_on             ( void );      	 				alias for cursor()
  void    cursor_off            ( void );      					alias for noCursor()
  void    setBacklight          ( uint8_t new_val);			alias for backlight() and nobacklight()
  void    load_custom_character ( uint8_t char_num,     alias for createChar()
                                  uint8_t *rows);	      
  void    printstr              ( const char[]);
