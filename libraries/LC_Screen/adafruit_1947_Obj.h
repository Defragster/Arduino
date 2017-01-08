#include <SPI.h>
#include <Wire.h>      			// this is needed for FT6206
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

#include "displayObj.h"

#define ADAFRUIT_1947_SPI_CLK 	13
#define ADAFRUIT_1947_SPI_MISO	12
#define ADAFRUIT_1947_SPI_MOSI	11
#define ADAFRUIT_1947_SPI_CS		10
#define ADAFRUIT_1947_SPI_DC	 	 9
#define ADAFRUIT_1947_SPI_RST		-1

// Rotation
#define PORTRAIT      0  // USB up
#define LANDSCAPE     1  // USB left
#define INV_PORTRAIT  2  // USB down
#define INV_LANDSCAPE 3  // USB right

class adafruit_1947_Obj : public displayObj {

  public :
  adafruit_1947_Obj(byte inCS,byte inDC,byte inMOSI,byte inSCLK,byte inRST,byte inMISO);
  ~adafruit_1947_Obj(void);
  
  virtual boolean dispObjBegin(void);
  virtual void    setRotation(byte inRotation);
  virtual void    setTextColor(colorObj* tColor);
  virtual void    setTextColor(colorObj* tColor,colorObj* bColor);
  virtual void    setTextSize(byte inSize);
  virtual void    setCursor(int inX,int inY);
  virtual void    drawText(char* inText);
  virtual void    fillScreen(colorObj* inColor);
  virtual void    fillRect(word locX,word locY,word width,word height,colorObj* inColor);
  virtual void    drawRect(word locX,word locY,word width,word height,colorObj* inColor);
  virtual void    fillRoundRect(word locX,word locY,word width,word height,word radius,colorObj* inColor);
  virtual void    drawRoundRect(word locX,word locY,word width,word height,word radius,colorObj* inColor);
  virtual void    drawPixel(word x,word y,colorObj* pColor);
  
  virtual point     getPoint(void);
  virtual boolean   touched(void);
  
  private:
          Adafruit_FT6206*  cTS;
          Adafruit_ILI9341* theTFT;
          byte              cs;
          byte              dc;
          byte              mosi;
          byte					 miso;
          byte              sclk;
          byte              rst;
};
