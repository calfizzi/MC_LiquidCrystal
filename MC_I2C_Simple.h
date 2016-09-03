
/************************************************************************************************************************
  File        : MC_I2C_Simple.h
  File type   : Arduino Library
  Developed By: Mario Calfizzi
  Description : This is the core I2C library self made to manage I2C communication on Ani Pin of arduino.
                
  Constructors:
    MC_I2C_Simple (uint8_t SDA_PIN, uint8_t SCL_PIN)  You can set SDA SCL Pin 
  Methods:
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
                                                      
*************************************************************************************************************************/
#pragma once
#ifndef MC_I2C_Simple_h
#define MC_I2C_Simple_h
#include <Arduino.h>
#include <pins_arduino.h>


class MC_I2C_Simple
{
private:
  uint8_t * _OutPortSDA;
  uint8_t * _InPortSDA;
  uint8_t * _ModePortSDA;
  uint8_t   _BitSDA;
  uint8_t * _OutPortSCL;
  uint8_t * _InPortSCL;
  uint8_t * _ModePortSCL;
  uint8_t   _BitSCL;
  uint8_t   _HW_Address;
  void      _start();
  void      _stop();
  bool      _writeByte  ( uint8_t byte );
  int       _readByte   ( uint8_t ACK  ); // negative is error else the low side is the Byte
public: 
  // constructor
  MC_I2C_Simple  ( uint8_t SDA_PIN = A4, uint8_t SCL_PIN = A5);
  // Set Hardware Address
  void    begin  ( uint8_t DeviceFisicalAddress);
  // Set Hardware Address and SCA/SCL Pins
  void    begin  ( uint8_t DeviceFisicalAddress, uint8_t SDA_PIN, uint8_t SCL_PIN);
  // Write a Byte via I2C using Hardware Address setted.
  // Return 1 if no error
  int     write  ( uint8_t Data);
  // Write a Byte via I2C on an internal dispositive register address using Hardware Address setted.
  // if no error returns 1 
  int     write  ( uint8_t address, uint8_t Data);
  // Write a list of Bytes via I2C on an internal dispositive register address using Hardware Address setted.
  // if no error returns number of bytes wrote 
  int     write  ( uint8_t address, uint8_t *buffer, uint8_t size);
  // Read a list of Bytes via I2C on an internal dispositive register address using Hardware Address setted.
  // if no error returns number of bytes read
  int     read   ( uint8_t address, uint8_t *buffer, uint8_t size);
};

#endif