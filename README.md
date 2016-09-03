# MC_LiquidCrystal
  MC_LiquidCrystal digital Liquid Crystal Display Library - Arduino Library
  Download and try the class MC_LiquidCrystal to manage any Liquid Crystal (16x2 or 20x4) display...

# MC_LiquidCrystal_I2C Class
##   Constructors:
    MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr,       Standard Constructor if use wire library 
                            uint8_t lcd_cols,       lcd_Addr          => Hardware Address of Display 
                            uint8_t lcd_rows);      lcd_cols/lcd_rows => identify the size of the display 
                                                    
    MC_LiquidCrystal_I2C  ( uint8_t lcd_Addr,       Standard Constructor if use MC_I2C_Simple library
                            uint8_t lcd_cols,       lcd_Addr          => Hardware Address of Display 
                            uint8_t lcd_rows,       lcd_cols/lcd_rows => identify the size of the display
                            uint8_t SDA_PIN = 4,    SDA_PIN           => you can use any pin of arduino
                            uint8_t SCL_PIN = 5);   SCL_PIN           => you can use any pin of arduino
                                                    
##   Methods:                                       
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
                                
    void   setCursor          ( uint8_t col,        Set the curso Position
                                uint8_t row);        
                                
    size_t write              ( uint8_t);           Directly write to the Display Memory

    void   command            ( uint8_t);           Directly send a specific commant to the Display
    
    void   init               ( void );             Initialize the Display. 

##   compatibility Methods aliases:
    void    blink_on              ( void );             alias for blink()
    void    blink_off             ( void );             lias for noBlink()
    void    cursor_on             ( void );             lias for cursor()
    void    cursor_off            ( void );             lias for noCursor()
    void    setBacklight          ( uint8_t new_val);   lias for backlight() and nobacklight()
    void    load_custom_character ( uint8_t char_num,   alias for createChar()
                                    uint8_t *rows);	      
    void    printstr              ( const char[]);


    
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

                                                      