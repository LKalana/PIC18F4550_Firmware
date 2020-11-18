/* 
 * File:   XC8_SPI_Driver.h
 * Author: Kalana
 *
 * Created on June 3, 2020, 3:12 PM
 * Modified on Octomber 24, 2020, 4:47 PM
 *  -> Added __delay_ms(1);
             PIR1bits.SSPIF=0;
 * 
 * Cleared SSPIF Flag manually.
 */

/* Set TRISAbits.TRISA5 as Output */

#ifndef XC8_SPI_DRIVER_H
#define	XC8_SPI_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ 4000000

#define SS PORTAbits.RA5
#define SDO PORTCbits.RC7
#define SCK PORTBbits.RB1
#define SDI PORTBbits.RB0

 void xc8_spi_init()
{
 TRISAbits.RA5 = 0;// SS as Output.
 TRISCbits.RC7 = 0;//SDO as Output.
 TRISBbits.RB0 = 1;// SDI as Input.
 TRISBbits.RB1 = 0;//SCK as Output.
 SSPCON1 = 0x20;// Set SSPEN and CKP.
 SSPSTAT = 0x40;// Set CKE.
}

void SPI_WAIT()
{ 
while(!SSPSTATbits.BF && PIR1bits.SSPIF==0);
}

void xc8_spi_write(int data)
{
 SSPBUF = data;
 SPI_WAIT(); 
 __delay_ms(1);
 PIR1bits.SSPIF=0;
}


#ifdef	__cplusplus
}
#endif

#endif	/* XC8_SPI_DRIVER_H */

