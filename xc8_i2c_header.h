/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

//------------------------------------------------------------------------------------------------------------------- Custom made I2C_INIT Function.
void _i2c_init(){
	SSPSTATbits.SMP = 0;//Setting up the I2C Standard Speed to 4 KHz.
	SSPADD = 0x14;//Setting up the BRG.Useing FOSC/4*(SSPADD+1).Anyway the formula dosen't working fine. 
	//For sake.In this case SSPADD is filled with 0x14 by referancing Proteus Simulation using MikroC I2C.
	//SSPCON = 0b00111000;//Set SSPCON I2C Master mode.
	SSPCON1 = 0b00111011;//Set SSPCON I2C Master (Slave Idle) mode.
}
//------------------------------------------------------------------------------------------------------------------- Custom made I2C_START Function.
void _i2c_start(){
	SSPCON2bits.SEN = 1;//Set Start I2C bit.
	while(SSPCON2bits.SEN == 0){}//Wait until the I2C Start complete.
}
//------------------------------------------------------------------------------------------------------------------- Custom made I2C_STOP Function.
void _i2c_stop(){
	SSPCON2bits.PEN = 1;//Set Stop I2C bit.
	while(SSPCON2bits.PEN){}//Wait until the I2C Stop complete.
}
//------------------------------------------------------------------------------------------------------------------- Custom made I2C_WRITE Function.
void _i2c_write(int data){
	while(SSPSTAT & 0x04 || SSPCON2 & 0x1F){}//Check both Transmission W/R bit clear and all SEN,PEN,RCEN,RCEN is set.
	  SSPBUF = data;//Load data to SSPBUFF Register.
}
//------------ 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

