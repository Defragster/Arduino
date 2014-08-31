#ifndef gyro_h
#define gyro_h

#include <idlers.h>

// ************************************************************************************************************
// I2C Gyroscope ITG3200 
// ************************************************************************************************************
//  
//  InvenSense Inc.
//  1197 Borregas Ave, 
//  Sunnyvale, CA 94089 U.S.A. 
//  Tel: +1 (408) 988-7339
//  Website: www.invensense.com
//  
// PN : ITG3200
 
 /*
 Next chips to code..
 BMP085
 HMC5883
 */


class gyro : 
public idler {

public:
   gyro(void);
   ~gyro(void);

   virtual void    idle(void);
   boolean newReadings(void);
   void    readValues(int* x,int* y,int* z);              
   
   void calibrate(void);                                       // Calculate the offsets. (Needs to be running first)
   void readOffsets(int* xOffset,int* yOffset,int* zOffset);   // Lets say we wanted to save these in Flash memory?
   void setOffsets(int xOffset,int yOffset,int zOffset);
   void readAngles(int* xAngle,int* yAngle,int* zAngle);       // What does the gyro think our angles are?
   void setAngles(int xAngle,int yAngle,int zAngle);           // Lets say the angles are here. 
   //void    dataDump(void);

protected:
   boolean readRegisters(byte regNum,byte* buff,int numBytes);
   byte    readRegister(byte regNum);
   boolean writeRegister(byte regNum, byte value);
   void    initGyro(void);
   void    checkGyro(void);
   void    readGyro(void);

   byte    state;
   boolean dataReady;
   
   int     x_offset;      // Calibration offset
   int     y_offset;
   int     z_offset;
   
   int     x_rotation;    // How fast is it changing now? (raw values)
   int     y_rotation;
   int     z_rotation;
   
   unsigned long lastRead;      // When was the last read seen?
<<<<<<< HEAD
   float           x_angle;       // Integrated, accumulated angle
   float           y_angle;
   float           z_angle;
=======
   unsigned long currentRead;   // What time was the current reading seen?
   
   int           x_angle;       // Integrated, accumulated angle
   int           y_angle;
   int           z_angle;
>>>>>>> FETCH_HEAD
};


#endif // gyro_h

