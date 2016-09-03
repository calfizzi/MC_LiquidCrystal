/************************************************************************************************************************
  File        : MC_I2C_Simple.cpp
  File type   : Arduino Library
  Developed By: Mario Calfizzi
  Description : This is the core I2C library self made to manage I2C communication on Ani Pin of arduino.
*************************************************************************************************************************/

#include "MC_I2C_Simple.h"

#define DEBUG 0 



//#define IS_D(Pin) ((pin>=0  && pin<=7)?   true : false)
//#define IS_B(Pin) ((pin>=8  && pin<=13)?  true : false)
//#define IS_C(Pin) ((pin>=A0 && pin<=A7)?  true : false)
//#define GET_PIN_PORT(Pin) IS_D(Pin)? PORTD : IS_B(Pin)? PORTB : IS_C(Pin)? PORTC

#define SET_OUTPUT(MODE_PORT, BIT)            (MODE_PORT) |= BIT
#define SET_INPUT(MODE_PORT, OUT_PORT, BIT)   {(MODE_PORT) &= ~BIT; (OUT_PORT) &= ~BIT;}
#define SET_HIGH(OUT_PORT, BIT)               (OUT_PORT) |= BIT
#define SET_LOW(OUT_PORT, BIT)                (OUT_PORT) &= ~BIT
#define READ(IN_PORT, BIT)                    (((IN_PORT) & BIT)!=0)
#define DELAY                                 delayMicroseconds(1)
//#define DELAYR                                delayMicroseconds(100)
#define SET_SDA_OUT                           SET_OUTPUT  (*this->_ModePortSDA  , this->_BitSDA)
#define SET_SDA_IN                            SET_INPUT   (*this->_ModePortSDA  , *this->_OutPortSDA  , this->_BitSDA)
#define SET_SCL_OUT                           SET_OUTPUT  (*this->_ModePortSCL  , this->_BitSCL)
#define SET_SCL_IN                            SET_INPUT   (*this->_ModePortSCL  , *this->_OutPortSCL  , this->_BitSCL)
#define SET_SDA_HIGH                          SET_HIGH    (*this->_OutPortSDA   , this->_BitSDA)
#define SET_SDA_LOW                           SET_LOW     (*this->_OutPortSDA   , this->_BitSDA)
#define SET_SCL_HIGH                          SET_HIGH    (*this->_OutPortSCL   , this->_BitSCL)
#define SET_SCL_LOW                           SET_LOW     (*this->_OutPortSCL   , this->_BitSCL)
#define READ_SDA                              READ        (*this->_InPortSDA    , this->_BitSDA)
#define READ_SCL                              READ        (*this->_InPortSCL    , this->_BitSCL)

void MC_I2C_Simple::_start ( void )
{
  SET_SDA_OUT;

  SET_SDA_HIGH;
  //DELAY;
  SET_SCL_HIGH;
  DELAY;
  SET_SDA_LOW;
  DELAY;
  SET_SCL_LOW;
  DELAY;
}

void MC_I2C_Simple::_stop ( void )
{
  SET_SDA_OUT;

  SET_SDA_LOW;
  //DELAY;
  SET_SCL_HIGH;
  DELAY;
  SET_SDA_HIGH;
  DELAY;
}

bool  MC_I2C_Simple::_writeByte ( uint8_t byte )    
{                                                     
char x;                                               
uint8_t b=false;                                      
  SET_SDA_OUT;                                        
  for(x=8; x; x--)                                    
  {                                                   
    if(byte & 0x80)                                   
      SET_SDA_HIGH;                                   
    else                                              
      SET_SDA_LOW;                                    
    DELAY;                                            
    SET_SCL_HIGH;                                     
    byte <<= 1;                                       
    DELAY;
    SET_SCL_LOW;                                      
  }                                                   
  SET_SDA_HIGH;                                       
  //DELAY;                                              
  SET_SDA_IN;                                         
  DELAY;
  SET_SCL_HIGH;                                       
  b = !READ_SDA;          // possible ACK bit         
  DELAY;                                              
  SET_SCL_LOW;                                        
  //DELAY;                                              
  SET_SDA_LOW;                                        
  DELAY;                                              
  return b;                                           
}                                                     
                                                      
                                                      
                                                      
                                                      
int MC_I2C_Simple::_readByte ( uint8_t ACK  )                       
{
  
uint8_t  d=0;
uint8_t  bit;
int x;
  SET_SDA_HIGH; 
  SET_SDA_IN;
//digitalWrite(SDA,1);
//pinMode(SDA, INPUT);
  for( x = 0;  x < 8; x++) 
  {
    SET_SDA_HIGH; 
    SET_SCL_HIGH;
    d  = d << 1;
    //do {
    //  SCL = 1;
    //}
    //while(SCL_IN==0);    // wait for any SCL clock stretching
    DELAY;
    bit = READ_SDA;
    d |= bit;
    SET_SCL_LOW;
    DELAY;
    //Serial.print(bit);
  } 
  //Serial.println();
  SET_SDA_OUT;
  if(ACK) 
    SET_SDA_LOW;
  else 
    SET_SDA_HIGH;
  SET_SCL_HIGH;
  DELAY;             // send (N)ACK bit
  SET_SCL_LOW;
  DELAY;
  SET_SDA_HIGH;
  DELAY;
  return d;
}



MC_I2C_Simple::MC_I2C_Simple ( uint8_t SDA_PIN, uint8_t SCL_PIN )
{
this->begin(0,SDA_PIN, SCL_PIN);
}

void MC_I2C_Simple::begin ( uint8_t DeviceFisicalAddress)
{
  this->_HW_Address = DeviceFisicalAddress<<1;
}

void MC_I2C_Simple::begin ( uint8_t DeviceFisicalAddress,  uint8_t SDA_PIN, uint8_t SCL_PIN)
{
  //volatile uint8_t *SCLMode;
  this->_BitSDA       = (uint8_t )  digitalPinToBitMask ( SDA_PIN );
  this->_OutPortSDA   = (uint8_t *) portOutputRegister  ( digitalPinToPort(SDA_PIN) );
  this->_InPortSDA    = (uint8_t *) portInputRegister   ( digitalPinToPort(SDA_PIN) );
  this->_ModePortSDA  = (uint8_t *) portModeRegister    ( digitalPinToPort(SDA_PIN) );
  this->_BitSCL       = (uint8_t)   digitalPinToBitMask ( SCL_PIN );
  this->_OutPortSCL   = (uint8_t *) portOutputRegister  ( digitalPinToPort(SCL_PIN) );
  this->_InPortSCL    = (uint8_t *) portInputRegister   ( digitalPinToPort(SCL_PIN) );
  this->_ModePortSCL  = (uint8_t *) portModeRegister    ( digitalPinToPort(SCL_PIN) );
  //SCLMode             = (uint8_t *) portModeRegister    ( digitalPinToPort(SCL_PIN) );
  SET_SCL_OUT;
  SET_SDA_OUT;
  //SET_OUTPUT (*this->_ModePortSCL,this->_BitSCL); 
  //SET_OUTPUT (*this->_ModePortSDA,this->_BitSDA);
  this->_HW_Address = DeviceFisicalAddress<<1;
}



int MC_I2C_Simple::write ( uint8_t address, uint8_t *buffer, uint8_t size)
{
#if DEBUG
  Serial.println("-- write start --");
#endif
  bool    ret = true;
  uint8_t i   = 0;
  this->_start();
#if DEBUG
  Serial.println("Start HW");
#endif
  ret = this->_writeByte(this->_HW_Address);
#if DEBUG
  Serial.print("Write Address: ");
  Serial.println(this->_HW_Address, HEX);
#endif
  if (ret) ret = this->_writeByte(address);
  if (ret) 
  {
    for (i=0; i<size; i++)
    {
      if (ret) 
      {
#if DEBUG
        Serial.print("Write Data ( ");
        Serial.print(i);
        Serial.print(" )= ");
        Serial.print(buffer[i],HEX);
#endif
        ret = this->_writeByte(buffer[i]);
#if DEBUG
        Serial.print(" --> ");
        Serial.print(ret? "OK":"ERR");
        Serial.println();
#endif
      }
      else
        break;
    }
  }
  this->_stop();
#if DEBUG
  Serial.println("-- write end--");
#endif
  return i;
}


int MC_I2C_Simple::write ( uint8_t Data)
{
#if DEBUG
    Serial.println("-- write --");
#endif
  bool    ret = true;
  this->_start();
  ret = this->_writeByte(this->_HW_Address);
#if DEBUG
  Serial.print("Write Address: ");
  Serial.println(this->_HW_Address, HEX);
#endif
#if DEBUG
    Serial.print("Write Data = ");
    Serial.print(Data,HEX);
#endif
  if (ret) ret = this->_writeByte(Data);
#if DEBUG
    Serial.print(" --> ");
    Serial.print(ret? "OK":"ERR");
    Serial.println();
#endif
  if (ret) 
    return 1;
  else
    return 0;
}


int MC_I2C_Simple::write ( uint8_t address, uint8_t Data)
{
  return this->write(address, &Data, 1);
}


int MC_I2C_Simple::read ( uint8_t address, uint8_t *buffer, uint8_t size)
{
#if DEBUG
  Serial.println("-- read start --");
#endif
  bool    ret = true;
  uint8_t i   = 0;
  this->_start();
#if DEBUG
  Serial.println("Start HW");
#endif
  ret = this->_writeByte(this->_HW_Address);
  if (ret) 
  {
#if DEBUG
    Serial.println("Write Address");
#endif
    ret = this->_writeByte(address);
  }

  if (ret) 
  {
    this->_start();
#if DEBUG
  Serial.println("Write HW For Reading");
#endif
    ret = this->_writeByte(this->_HW_Address | 1);
  }
  if (ret)
  {
#if DEBUG
  Serial.println("Reading Data");
#endif
    for (i=0; i<size; i++)
    {
      if (i<size-1) 
        buffer[i] = this->_readByte(1); 
      else
        buffer[i] = this->_readByte(0); 
    }
  }
#if DEBUG
  Serial.println("End");
#endif
  this->_stop();
#if DEBUG
  Serial.println("Stop");
  Serial.println("-- read end --");
#endif

  if(ret) return i;
  else
    return -1;
}
