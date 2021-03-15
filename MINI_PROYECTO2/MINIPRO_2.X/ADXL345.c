#include "ADXL345.h"

// ADXL345  Registers
#define W_DATA      0xA6    //Used to perform a Write operation
#define R_DATA      0xA7    //Used to perform a Read operation
#define D_FRM       0x31    //Read/Write Register, Selects the operating mode. Default = Single measurement
#define BW_RT       0x2C
#define P_CTL       0x2D    //Send continuous Measurement mode.
#define F_CTL       0x38    //Send Fifo Bypass mode
#define X_LSB       0x32    //Read Register, Output of X LSB 8-bit value.
#define X_MSB       0x33    //Read Register, Output of X MSB 8-bit value.
#define Y_LSB       0x34    //Read Register, Output of Z LSB 8-bit value.
#define Y_MSB       0x35    //Read Register, Output of Z MSB 8-bit value.
#define Z_LSB       0x36    //Read Register, Output of Y LSB 8-bit value.
#define Z_MSB       0x37    //Read Register, Output of Y MSB 8-bit value.
#define _XTAL_FREQ 8000000
 
void ADXL345_Write(int add, int data)
{
         MAS_START();
         MAS_WRITE(W_DATA);
         MAS_WRITE(add);
         MAS_WRITE(data);
         MAS_STOP();
 
}
      
int ADXL345_Read(int add){
         int retval;
         MAS_START();
         MAS_WRITE(W_DATA);
         MAS_WRITE(add);
         MAS_START();
         MAS_WRITE(R_DATA);
         retval=MAS_READ(0);
         MAS_STOP();
         return retval;
}
 
void ADXL345_Init(void){
         ADXL345_Write(D_FRM,0x0B);
         __delay_ms(2);
         ADXL345_Write(P_CTL,0x08);
         __delay_ms(2);
}