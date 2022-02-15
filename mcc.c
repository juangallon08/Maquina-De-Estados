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
// define los casos 
typedef enum {
    ABRIENDO,
    CERRANDO,
    PARADO,
    SENSOR,        
   
}Estados_t;
// Funcion maquina de estados 
void updata_MEF (void){
    static Estados_t Estado = ABRIENDO; // se inicia el estado y se guarda 
    int tiempoA = 0;
    int tiempoC = 0;
    int C = 0;           // variables del programa 
    int R = 10;
    int R2 = 10;        
    int R3 = 10;
    int A = 0;
    int TA = 0;
    int TC = 0;    
    switch (Estado){
        case ABRIENDO:  // se prende un led en este caso el amarillon 
            if(PORTAbits.RA0 == 0){
               for(int i=0;i<=R;i+=1 ){ // cuenta del tiempo de encendido para detener en 10 segundos, si no se precenta el paro 
                   PORTBbits.RB0 = 1;
                   if(PORTAbits.RA2 == 0){ // si detecta en alto RA2 se detiene la ejecucion y enciende el led verde 
                      PORTBbits.RB0 = 0;   // y se envia al caso PARADO donde se pude ranudar la ejecucion o 
                      PORTBbits.RB1 = 1;  // se procede a cerrarce 
                      __delay_ms(800); 
                       R = tiempoA;    // de locntrario se cumple su tiempo de encendido, sin interruciones y el led 
                       A = 1;          // amarillo se apaga indicando que ya esta abierto completamente 
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
                
        case CERRANDO:             // prende el led rojo que indica el cierre de la puerta 
            if(PORTAbits.RA3 == 0){
               for(int i=0;i<=R2;i+=1 ){ //cuenta del tiempo de cerrado para detener en 10 segundos, si no se precenta el paro 
                   PORTBbits.RB2 = 1;
                   __delay_ms(500);
                   if(PORTAbits.RA2 == 0){ // paroo en la rutina cerrando
                      PORTBbits.RB2 = 0;
                      PORTBbits.RB1 = 1; // al detectarce el paro se rompe el ciclo 
                      __delay_ms(600);   // de locntrario se cumple su tiempo de cerrado, sin interruciones y el led 
                      R2 = tiempoC;     //rojo se apaga indicando que ya esta cerrado completamente 
                      C = 1;
                     }
                   else { tiempoC+=1;}
                   if(TC=0){
                   __delay_ms(60);} 
                   else{ __delay_ms(10); }  }
               
                PORTBbits.RB1 = 0;
                PORTBbits.RB2 = 0;
               __delay_ms(100); 
               if (C == 1 )
                  {Estado = PARADO;}
               else 
               {Estado = ABRIENDO;}}
            break;  
        case PARADO:                   // este estado indica que se interrumpio alguna rutina 
            if(PORTAbits.RA3 == 0){  // se pregunta por el estado de los puertos para continuar con los estados 
               Estado = CERRANDO;
               TC=1;                  
                }
            if(PORTAbits.RA0 == 0){
               Estado = ABRIENDO;
               TA=1;
                }
            break;
                
            
        }
    
}
    




/**
 End of File
*/
