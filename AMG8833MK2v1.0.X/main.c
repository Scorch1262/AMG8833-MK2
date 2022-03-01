#define FCY 16000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
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

extern float DataMatrix[8][8];                                                  // definiert "DataMatrix" 
extern float Temp_Data[64];                                                     // definiert "Temp_Data"
    
/*
                         Main application
 */
int main(void){                                         // "main"
    SYSTEM_Initialize();                                // ruft "SYSTEM_Initialize" auf
    __delay_ms(500);                                    // warte 500ms
     AMG8833_Init();
    
    while (1){                                                      // Endlosschleife
        AMG8833_GetData();                                          // 
        /*
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[0],Temp_Data[1],Temp_Data[2],Temp_Data[3],Temp_Data[4],Temp_Data[5],Temp_Data[6],Temp_Data[7]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[8],Temp_Data[9],Temp_Data[10],Temp_Data[11],Temp_Data[12],Temp_Data[13],Temp_Data[14],Temp_Data[15]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[16],Temp_Data[17],Temp_Data[18],Temp_Data[19],Temp_Data[20],Temp_Data[21],Temp_Data[22],Temp_Data[23]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[24],Temp_Data[25],Temp_Data[26],Temp_Data[27],Temp_Data[28],Temp_Data[29],Temp_Data[30],Temp_Data[31]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[32],Temp_Data[33],Temp_Data[34],Temp_Data[35],Temp_Data[36],Temp_Data[37],Temp_Data[38],Temp_Data[39]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[40],Temp_Data[41],Temp_Data[42],Temp_Data[43],Temp_Data[44],Temp_Data[45],Temp_Data[46],Temp_Data[47]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[48],Temp_Data[49],Temp_Data[50],Temp_Data[51],Temp_Data[52],Temp_Data[53],Temp_Data[54],Temp_Data[55]);
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",Temp_Data[56],Temp_Data[57],Temp_Data[58],Temp_Data[59],Temp_Data[60],Temp_Data[61],Temp_Data[62],Temp_Data[63]);
        printf("\r\n");                                            // schreibt "Enter" an UART
        printf("\r\n");                                            // schreibt "Enter" an UART
        printf("\r\n");                                            // schreibt "Enter" an UART
        */
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[0][0],DataMatrix[0][1],DataMatrix[0][2],DataMatrix[0][3],DataMatrix[0][4],DataMatrix[0][5],DataMatrix[0][6],DataMatrix[0][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[1][0],DataMatrix[1][1],DataMatrix[1][2],DataMatrix[1][3],DataMatrix[1][4],DataMatrix[1][5],DataMatrix[1][6],DataMatrix[1][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[2][0],DataMatrix[2][1],DataMatrix[2][2],DataMatrix[2][3],DataMatrix[2][4],DataMatrix[2][5],DataMatrix[2][6],DataMatrix[2][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[3][0],DataMatrix[3][1],DataMatrix[3][2],DataMatrix[3][3],DataMatrix[3][4],DataMatrix[3][5],DataMatrix[3][6],DataMatrix[3][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[4][0],DataMatrix[4][1],DataMatrix[4][2],DataMatrix[4][3],DataMatrix[4][4],DataMatrix[4][5],DataMatrix[4][6],DataMatrix[4][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[5][0],DataMatrix[5][1],DataMatrix[5][2],DataMatrix[5][3],DataMatrix[5][4],DataMatrix[5][5],DataMatrix[5][6],DataMatrix[5][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[6][0],DataMatrix[6][1],DataMatrix[6][2],DataMatrix[6][3],DataMatrix[6][4],DataMatrix[6][5],DataMatrix[6][6],DataMatrix[6][7]);// schreibt "" an UART
        //printf("\r\n");                                            // schreibt "Enter" an UART
        printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f\r\n",DataMatrix[7][0],DataMatrix[7][1],DataMatrix[7][2],DataMatrix[7][3],DataMatrix[7][4],DataMatrix[7][5],DataMatrix[7][6],DataMatrix[7][7]);// schreibt "" an UART
        printf("\r\n");                                            // schreibt "Enter" an UART
        printf("\r\n");                                            // schreibt "Enter" an UART
        printf("\r\n");                                            // schreibt "Enter" an UART
        __delay_ms(1000);
    }                                                               // 
}                                                       // 
    
