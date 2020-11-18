/* 
 * File:   MAX7219Header.h
 * Author: Kalana
 *
 * Created on October 19, 2020, 10:47 PM
 */

#ifndef MAX7219HEADER_H
#define	MAX7219HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------------------------------------------- Initialize Max7219 Chip.
/*
 For the changes, Refer Datasheet.
*/

// Note:- To use DP, instead of using 0000 use 1000 (0x80).
// Example = to display 0x1F with DP, Use 0x9F.

// ----------------------------------------------------- Letters.
int lttrA[5]={0x9F,0x24,0x24,0x24,0x9F};   
int lttrB[5]={0xBF,0xA4,0xA4,0xA4,0x1B};
int lttrC[5]={0x1F,0xA0,0xA0,0xA0,0x11};
int lttrD[5]={0xBF,0xA0,0xA0,0xA0,0x1F};
int lttrE[5]={0xBF,0xA4,0xA4,0xA4};
int lttrF[5]={0xBF,0x24,0x24,0x24,0x20};
int lttrG[5]={0x1F,0xA0,0xA4,0xA4,0x17};
int lttrH[5]={0xBF,0x04,0x04,0x04,0xBF};
int lttrI[3]={0xA0,0xBF,0xA0};
int lttrJ[5]={0x01,0xA0,0xA0,0xA0,0x3F};
int lttrK[5]={0xBF,0x04,0x04,0x0A,0xB1};
int lttrL[5]={0xBF,0x80,0x80,0x80,0x80};
int lttrM[5]={0xBF,0x10,0x08,0x10,0xBF};
int lttrN[5]={0xBF,0x08,0x04,0x02,0xBF};
int lttrO[5]={0x1F,0xA0,0xA0,0xA0,0x1F};
int lttrP[5]={0xBF,0x24,0x24,0x24,0x18};
int lttrQ[5]={0x1F,0xA0,0xA2,0xA1,0x9F};
int lttrR[5]={0xBF,0x24,0x24,0x24,0x9B};
int lttrS[5]={0x19,0xA4,0xA4,0xA4,0x13};
int lttrT[5]={0x20,0x20,0xBF,0x20,0x20};
int lttrU[5]={0x3F,0x80,0x80,0x80,0x3F};
int lttrV[5]={0x3E,0x01,0x80,0x01,0x3E};
int lttrW[5]={0xBF,0x01,0x02,0x01,0xBF};
int lttrX[5]={0xB1,0x0A,0x04,0x0A,0xB1};
int lttrY[5]={0x30,0x08,0x87,0x08,0x30};
int lttrZ[5]={0xA1,0xA2,0xA4,0xA8,0xB0};
//---------------------------------------------------- Numbers.


int mx_pos;
    
void max7219_init()
{
/* Decode Mode Register */
SS = 0;
xc8_spi_write(0x09);
xc8_spi_write(0x00);
SS = 1;
/* Intensity Register */
SS = 0;
xc8_spi_write(0x0A);
xc8_spi_write(0x0F);
SS = 1;
/* Scan Limit Register */
SS = 0;
xc8_spi_write(0x0B);
xc8_spi_write(0x07);
SS = 1;
/* Shutdown Register */
SS = 0;
xc8_spi_write(0x0C);
xc8_spi_write(0x01);
SS = 1;
/* Display Test Register */
SS = 0;
xc8_spi_write(0x0F);
xc8_spi_write(0x00);
SS = 1;
	
}
//------------------------------------------------------------------------------------------------------------------- Clear Function.
void max7219_disp_clear()
{
   for(int i=0x01;i<0x09;i++)
     {
        SS = 0;
        xc8_spi_write(i);
        xc8_spi_write(0x00);
        SS = 1;
 }
}
//-------------------------------------------------------------------------------------------------------------------- Display Single Character.
void max7219_disp_char(char data)
{
// Switch condition
  switch (data)
  {
      // If data = A.
      case 'A' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;// Enable Chip Select.
                       xc8_spi_write(mx_pos);// Digit Register.
                       xc8_spi_write(lttrA[i]);// Segments.
                       SS = 1;// Disable Chip Select.
                       mx_pos++;// Increment my_pos.
                    }
                break;
      // If data = B.
      case 'B' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrB[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = C.
      case 'C' :mx_pos = 0x02;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrC[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = D.
      case 'D' :mx_pos = 0x02;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrD[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = E.
      case 'E' :mx_pos = 0x03;
                for(int i=0;i<4;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrE[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
       // If data = F.
      case 'F' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrF[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = G.
      case 'G' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrG[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = H.
      case 'H' :mx_pos = 0x02;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrH[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = I.
      case 'I' :mx_pos = 0x04;
                for(int i=0;i<3;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrI[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = J.
      case 'J' :mx_pos = 0x02;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrJ[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = K.
      case 'K' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrK[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = L.
      case 'L' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrL[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = M.
      case 'M' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrM[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = N.
      case 'N' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrN[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = O.
      case 'O' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrO[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = P.
      case 'P' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrP[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = Q.
      case 'Q' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrQ[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = R.
      case 'R' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrR[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = S.
      case 'S' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrS[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = T.
      case 'T' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrT[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = U.
      case 'U' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrU[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = V.
      case 'V' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrV[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = W.
      case 'W' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrW[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = X.
      case 'X' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrX[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = Y.
      case 'Y' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;
                       xc8_spi_write(mx_pos);
                       xc8_spi_write(lttrY[i]);
                       SS = 1;
                       mx_pos++;
                    }
                break;
      // If data = Z.
      case 'Z' :mx_pos = 0x03;
                for(int i=0;i<5;i++)
                    {
                       SS = 0;// Disable Chip Select.
                       xc8_spi_write(mx_pos);// Digit Register.
                       xc8_spi_write(lttrZ[i]);// Segments.
                       SS = 1;// Disable Chip Select.
                       mx_pos++;// Increment my_pos.
                    }
                break;
      // If data = Default. 
      default  :SS = 0;
                xc8_spi_write(0x01); // Digit Register.
                xc8_spi_write(0x00);// Segments.
                SS = 1;
                break;
  }   
}
#ifdef	__cplusplus
}
#endif

#endif	/* MAX7219HEADER_H */

