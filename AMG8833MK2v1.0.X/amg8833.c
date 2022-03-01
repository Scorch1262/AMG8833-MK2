#define FCY 16000000UL

#include "xc.h"
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/i2c1.h"
#include "amg8833.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif

#define AMG8833_ADDR            0x69  // 0x68

#define AMG88xx_PCTL            0x00
#define AMG88xx_RST             0x01
#define AMG88xx_FPSC            0x02
#define AMG88xx_INTC            0x03
#define AMG88xx_STAT            0x04
#define AMG88xx_SCLR            0x05
#define AMG88xx_AVE             0x07
#define AMG88xx_INTHL           0x08
#define AMG88xx_INTHH           0x09
#define AMG88xx_INTLL           0x0A
#define AMG88xx_INTLH           0x0B
#define AMG88xx_IHYSL           0x0C
#define AMG88xx_IHYSH           0x0D
#define AMG88xx_TTHL            0x0E
#define AMG88xx_TTHH            0x0F
#define AMG88xx_INT_OFFSET      0x10   //0x010 ???
#define T01L  0x80
#define T01H  0x81

// power_modes
#define AMG88xx_NORMAL_MODE     0x00
#define AMG88xx_SLEEP_MODE      0x01
#define AMG88xx_STAND_BY_60     0x20
#define AMG88xx_STAND_BY_10     0x21

// sw_resets
#define AMG88xx_FLAG_RESET      0x30
#define AMG88xx_INITIAL_RESET   0x3F

// frame_rates
#define AMG88xx_FPS_10          0x00
#define AMG88xx_FPS_1           0x01

// int_enables
#define AMG88xx_INT_DISABLED    0x00
#define AMG88xx_INT_ENABLED     0x01

// int_modes
#define AMG88xx_DIFFERENCE      0x00
#define AMG88xx_ABSOLUTE_VALUE  0x01

I2C1_MESSAGE_STATUS status;                                             // 

uint8_t Slave_Address;                                                  // definiert "Slave_Address" 

uint8_t  writeBuffer[3] = {0x00, 0x00, 0x00};                           // definiert "writeBuffer"
uint8_t  readBuffer[10] = {0x00, 0x00, 0x00};                           // definiert "readBuffer" 
uint16_t retryTimeOut1;                                                 // definiert "retryTimeOut1" 
uint16_t retryTimeOut2;                                                 // definiert "retryTimeOut2" 

float DataMatrix[8][8] = {                                              // definiert "DataMatrix"
    {0,0,0,0,0,0,0,0},                                                  // 1
    {0,0,0,0,0,0,0,0},                                                  // 2
    {0,0,0,0,0,0,0,0},                                                  // 3
    {0,0,0,0,0,0,0,0},                                                  // 4
    {0,0,0,0,0,0,0,0},                                                  // 5
    {0,0,0,0,0,0,0,0},                                                  // 6
    {0,0,0,0,0,0,0,0},                                                  // 7
    {0,0,0,0,0,0,0,0},                                                  // 8
};                                                                      //
float Temp_Data[64];                                                    // definiert "Temp_Data"

void AMG8833_Init(void) {                                               // "AMG8833_Init"
    Slave_Address = AMG8833_ADDR;                                       // schreibt "AMG8833_ADDR" in "Slave_Address"    
    
    // Set AMG88 sensor registers
                                                                        // Normal mode
    writeBuffer[0] = AMG88xx_PCTL;                                      // schreibt "AMG88xx_PCTL" in "writeBuffer[0]"
    writeBuffer[1] = 0x00;                                              // schreibt "0x00" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
                                                                        // Flag reset
    writeBuffer[0] = AMG88xx_RST;                                       // schreibt "AMG88xx_RST" in "writeBuffer[0]"
    writeBuffer[1] = 0x30;                                              // schreibt "0x30" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
                                                                        // Frame mode 10FPS
    writeBuffer[0] = AMG88xx_FPSC;                                      // schreibt "AMG88xx_FPSC" in "writeBuffer[0]"
    writeBuffer[1] = 0x00;                                              // schreibt "0x00" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    __delay_ms(100);                                                    // warte 100ms
  
                                                                        // INTHL
    writeBuffer[0] = AMG88xx_INTHL;                                     // schreibt "AMG88xx_INTHL" in "writeBuffer[0]"
    writeBuffer[1] = 0x30;                                              // schreibt "0x30" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
                                                                        // INTHH
    writeBuffer[0] = AMG88xx_INTHH;                                     // schreibt "AMG88xx_INTHH" in "writeBuffer[0]"
    writeBuffer[1] = 0x00;                                              // schreibt "0x00" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    
                                                                        // INTLL
    writeBuffer[0] = AMG88xx_INTLL;                                     // schreibt "AMG88xx_INTLL" in "writeBuffer[0]"
    writeBuffer[1] = 0x15;                                              // schreibt "0x15" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
                                                                        // INTLH
    writeBuffer[0] = AMG88xx_INTLH;                                     // schreibt "AMG88xx_INTLH" in "writeBuffer[0]"
    writeBuffer[1] = 0x00;                                              // schreibt "0x00" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    
                                                                        // IHYSL
    writeBuffer[0] = AMG88xx_IHYSL;                                     // schreibt "AMG88xx_IHYSL" in "writeBuffer[0]"
    writeBuffer[1] = 0x20;                                              // schreibt "0x20" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
                                                                        // IHYSH
    writeBuffer[0] = AMG88xx_IHYSH;                                     // schreibt "AMG88xx_IHYSH" in "writeBuffer[0]"
    writeBuffer[1] = 0x00;                                              // schreibt "0x00" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 

    __delay_ms(100);                                                    // warte 100ms
}                                                                       //

void AMG8833_GetData(void) {                                            // "AMG8833_GetData"
    Slave_Address = AMG8833_ADDR;                                       // schreibt "AMG8833_ADDR" in "Slave_Address"    
    int pointer = 0;                                                    // definiert "pointer"
    int n = 0;                                                          // definiert "n"
    int x;
    int y;
    int i;
    for(i=0; i<64; i++){                                                // solange "i" kleiner als 64 ist
        writeBuffer[0] = T01H + pointer;                                // schreibt "T01H + pointer" in "writeBuffer[0]"
        I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);   // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf 
        I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);     // liest von I2C1 in 1 Byte (readBuffer[0]) 
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf
        
        writeBuffer[0] = T01L + pointer;                                // schreibt "T01L + pointer" in "writeBuffer[0]"
        I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);   // schreibt 1 Byte (writeBuffer[0]) an I2C1                  
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf 
        I2C1_MasterRead(&readBuffer[1], 1, Slave_Address, &status);     // liest von I2C1 in 1 Byte (readBuffer[1]) 
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf
        
        pointer = pointer + 2;                                          // "pointer" + 2
        Temp_Data[i] = AMG8833_Wertdetekt();                            // "Temp_Data" gleich rueckgabe von "AMG8833_Wertdetekt"
        __delay_ms(1);                                                  // warte 1ms
    }                                                                   //
    for(x=0; x<8; x++){                                                 // solange "x" kleiner als 8 ist
        for(y=0; y<8; y++){                                             // solange "y" kleiner als 8 ist
            DataMatrix[x][y] = Temp_Data[n];                            // 
            n = n + 1;                                                  // n + 1
        }                                                               // 
    }                                                                   // 
}                                                                       // 

float AMG8833_Wertdetekt(void){                                         // "AMG8833_Wertdetekt"
    uint16_t tempData;                                                  // definiert "tempData"
    float    tempDataAnz;                                               // definiert "tempDataAnz"
    
    tempData = (readBuffer[0] << 8) + readBuffer[1];                    //       
    tempDataAnz = tempData;                                             // "tempDataAnz" gleich "tempData" 
    tempDataAnz = tempDataAnz * 0.25L;                                  // "tempDataAnz" * 0.25L
    return tempDataAnz;                                                 // gibt "tempDataAnz" zurück    
}                                                                       // 

void i2c1_message_pending_100(void){                                    // "i2c1_message_pending_100"
    retryTimeOut1 = 0;                                                  // setzt "retryTimeOut1" auf 0
    retryTimeOut2 = 0;                                                  // setzt "retryTimeOut2" auf 0
    while(status == I2C1_MESSAGE_PENDING){                              // solange "status" gleich "I2C1_MESSAGE_PENDING" ist
        if (retryTimeOut2 == 1000){                                      // wenn "retryTimeOut2" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut2++;                                            // "retryTimeOut2" +1
        }                                                               // 
    }
    while(status != I2C1_MESSAGE_FAIL){                                 // solange "status" nicht gleich "I2C1_MESSAGE_FAIL" ist
        if (retryTimeOut1 == 1000){                                      // wenn "retryTimeOut1" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut1++;                                            // "retryTimeOut1" +1
        }                                                               // 
    }                                                                   // 
}                                                                       // 