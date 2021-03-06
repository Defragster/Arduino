#ifndef adafruit_1947_Obj_h
#define adafruit_1947_Obj_h

#include <SPI.h>
#include <Wire.h>      			// this is needed for FT6206
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

#include "displayObj.h"

/*
// This block os for Arduino UNO.
#define ADAFRUIT_1947_SPI_CLK 	13
#define ADAFRUIT_1947_SPI_MISO	12
#define ADAFRUIT_1947_SPI_MOSI	11
#define ADAFRUIT_1947_SPI_CS	10
#define ADAFRUIT_1947_SPI_DC	 9
#define ADAFRUIT_1947_SPI_RST	-1
#define ADAFRUIT_1947_SPI_SD_CS  4
*/

// This block os for Arduino teensy 3.2
#define ADAFRUIT_1947_SPI_CLK 	13
#define ADAFRUIT_1947_SPI_MISO	12
#define ADAFRUIT_1947_SPI_MOSI	11
#define ADAFRUIT_1947_SPI_CS	10
#define ADAFRUIT_1947_SPI_DC	 9
#define ADAFRUIT_1947_SPI_RST	-1
#define ADAFRUIT_1947_SPI_SD_CS  4

// Rotation
#define PORTRAIT      0  // USB up
#define LANDSCAPE     1  // USB left
#define INV_PORTRAIT  2  // USB down
#define INV_LANDSCAPE 3  // USB right

#ifndef swap
#define swap(a, b) { int16_t t = a; a = b; b = t; }
#endif

class adafruit_1947_Obj : public displayObj {

  public :
  adafruit_1947_Obj(void);        // This is for creating the hardware version.
  adafruit_1947_Obj(byte inCS,byte inDC,byte inMOSI,byte inSCLK,byte inRST,byte inMISO);
  ~adafruit_1947_Obj(void);
  
  virtual boolean dispObjBegin(void);
  virtual void    setRotation(byte inRotation);
  virtual void    setTextColor(colorObj* tColor);
  virtual void    setTextColor(colorObj* tColor,colorObj* bColor);
  virtual void    setTextSize(byte inSize);
  virtual void    setTextWrap(boolean wrap);
  virtual void    setCursor(int inX,int inY);
  virtual void    drawText(char* inText);
  virtual void    fillScreen(colorObj* inColor);
  virtual void    fillRect(int locX,int locY,word width,word height,colorObj* inColor);
  virtual void    drawRect(int locX,int locY,word width,word height,colorObj* inColor);
  virtual void    fillRoundRect(int locX,int locY,word width,word height,word radius,colorObj* inColor);
  virtual void    drawRoundRect(int locX,int locY,word width,word height,word radius,colorObj* inColor);
  virtual void    drawCircle(int locX,int locY,word inDiam, colorObj* inColor);
  virtual void    fillCircle(int locX,int locY,word inDiam, colorObj* inColor);
  virtual void    drawVLine(int locX,int locY,word height,colorObj* inColor);
  virtual void    drawHLine(int locX,int locY,word width,colorObj* inColor);
  virtual void    drawLine(int locX,int locY,int locX2,int locY2,colorObj* inColor);
  virtual void    drawPixel(int x,int y,colorObj* pColor);
  
  virtual point     getPoint(void);
  virtual boolean   touched(void);
  
  private:
          Adafruit_FT6206*  cTS;
          Adafruit_ILI9341* theTFT;
          boolean           hardware;
          byte              cs;
          byte              dc;
          byte              mosi;
          byte					 miso;
          byte              sclk;
          byte              rst;
};

#endif