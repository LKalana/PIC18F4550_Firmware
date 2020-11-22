/* 
 * File:   firmware_4550.c
 * Author: Liyanage Kalana Perera 
 *
 * Created on November 11, 2020, 11:22 AM
 */

// Solo Purpose to program PIC on this Laptop....
// In This program.It is trying to control PCF8574.
// This version works well on Proteus Simulation.
/*
 * Git Fixes:-
 * Add void main.
 * Break the program loop using loop_breaker (MCU execute void main repeatedly.This attempt will break the loop.).
 * Change the Delay value to check the present of program loop and change equal operator to logical AND.
 * Last commit doesn't work.Therefore changing the delay element will solved the loop problem temporary.
 * Set BOR to ON_ACTIVE,BOR voltage set to 2.79v and WDT Disabled.
 * Sudden Processor reset fixed by Disabling WDT. In earlier commits WDT missed to Disable.In this commit STACK_OVER/UNDER_FLOW Disabled.
 * 
*/
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_HS // Oscillator Selection bits (Internal oscillator, HS oscillator used by USB (INTHS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include "pic18f4550.h"
#include "xc8_i2c_header.h"// Including XC8 Custom I2C Header.
#include "pcf8574_header.h"// Including XC8 Custom PCF8574 Header.
//#include "XC8_SPI_Driver.h"// Including XC8 Custom SPI Header.
//#include "MAX7219Header.h"// Including XC8 Custom Max7219 Header.
#define _XTAL_FREQ 4000000 // Define Clock.
/*
 * 
 */
//int loop_breaker = 1;// This variable act as a lock to avoid void main looping.
void main()
{
    /*
     Note :- Even if i add loop_breaker the system still loops.By further observations,that identifies that the delay element after the matrix 
             clear cause the blink glitch.Reducing the delay between 1 to 10 ms will solve the problem temporary.
     */
    //---------------------------------------------------------- PIC18F4550 Init.
    ADCON0bits.ADON = 0; // Disable Analog Module.
    ADCON1 = 0x0F; // Setting GPIO to Digital.
    CMCON = 0x07; // Disable Comparators and set Digital.
    //----------------------------------------------------------- Program Loop.
    _i2c_init(); // Initialize I2C.
    //xc8_spi_init(); // Initialize SPI.
    //max7219_init(); // Initialize Max7219.
    //max7219_disp_clear();
    //__delay_ms(100);
    //TRISD = 0x00;
   while(1)
   {
      pcf8574_write_(0x04);// Call Custom Function.
      __delay_ms(100);
      pcf8574_write_(0x00);// Call Custom Function.
      __delay_ms(100);
   }
}
