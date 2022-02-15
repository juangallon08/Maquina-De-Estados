/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1938
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above or later
        MPLAB             :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc.h"
#include <stdint.h>


void SYSTEM_Initialize(void)
{

    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    WDT_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; SPLLEN disabled; IRCF 16MHz_HF; 
    OSCCON = 0x78;
    // TUN 0; 
    OSCTUNE = 0x00;
    // SBOREN disabled; 
    BORCON = 0x00;
}

void WDT_Initialize(void)
{
    // WDTPS 1:65536; SWDTEN OFF; 
    WDTCON = 0x16;
}
//funcion para la maquina de estados 
typedef enum {
    ABRIENDO,
    CERRANDO,
    PARADO,
   
}Estados_t;

void updata_MEF (void){
    static Estados_t Estado = ABRIENDO; 
    int tiempoA = 0;
    int tiempoC = 0;
    int C = 0;
    int R = 10;
    int R2 = 10;
    int R3 = 10;
    int A = 0;
    
    switch (Estado){
        case ABRIENDO:
            if(PORTAbits.RA0 == 0){
               for(int i=0;i<=R;i+=1 ){
                   PORTBbits.RB0 = 1;
                   if(PORTAbits.RA2 == 0){
                      PORTBbits.RB0 = 0;
                      PORTBbits.RB1 = 1; 
                      __delay_ms(800); 
                       R = tiempoA;
                       A = 1;
               } else { tiempoA+=1;}
                  __delay_ms(600); 
                }
               PORTBbits.RB1 = 0;
               PORTBbits.RB0 = 0;
               __delay_ms(100); 
               if (A == 1){
                   Estado = PARADO;
                   }
               else { Estado = CERRANDO;} 
            }
            break;       
                
        case CERRANDO: 
            if(PORTAbits.RA3 == 0){
               for(int i=0;i<=R2;i+=1 ){
                   PORTBbits.RB2 = 1;
                   __delay_ms(600);
                   if(PORTAbits.RA2 == 0){ // paroo en la rutina cerrando
                      PORTBbits.RB2 = 0;
                      PORTBbits.RB1 = 1; 
                      __delay_ms(600);
                      R2 = tiempoC;
                      C = 1;
                     }
                   else { tiempoC+=1;}
                   __delay_ms(60); }
               
                PORTBbits.RB1 = 0;
                PORTBbits.RB2 = 0;
               __delay_ms(100); 
               if (C == 1 )
                  {Estado = PARADO;}
               else 
               {Estado = ABRIENDO;}}
            break;  
        case PARADO:
            if(PORTAbits.RA3 == 0){
               Estado = CERRANDO;
                }
            if(PORTAbits.RA0 == 0){
               Estado = ABRIENDO;
                }
            break;
                
            
        }
    
}
    




/**
 End of File
*/
