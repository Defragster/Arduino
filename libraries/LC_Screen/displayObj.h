#ifndef displayObj_h
#define displayObj_h

#include <colorObj.h>

// This is going to by our base display object. Similar to adafruit's GFX object.
// The plan is to inherit this for whatever glue code each piece of 
// hardware needs to run.

// point needs to go here 'cause it spans both the display side and
// the drawing object side. So, this is the lowest common denominator
// if you will.

  struct point {
    int x;
    int y;
  }; 



class displayObj {    

public :
  displayObj(bool inGraphic,bool inColor,bool inTouch,bool inSD,bool inReadable);

  virtual boolean dispObjBegin(void);
  virtual void setRotation(byte inRotation);
  virtual void setTextColor(colorObj* tColor);
  virtual void setTextColor(colorObj* tColor,colorObj* bColor);
  virtual void setTextSize(byte inSize);
  virtual void setTextWrap(boolean inWrap);
  virtual void setCursor(int inX,int inY);
  virtual void drawText(char* inText);
  virtual void fillScreen(colorObj* inColor);
  virtual void fillRect(int locX,int locY,word width,word height, colorObj* inColor);
  virtual void drawRect(int locX,int locY,word width,word height, colorObj* inColor);
  virtual void fillRectGradient(int inX,int inY,word inXSize,word inYSize,colorObj* startColor,colorObj* endColor,boolean vertical=true);
  virtual void fillScreenGradient(colorObj* startColor,colorObj* endColor,boolean vertical=true);
  virtual void fillRoundRect(int locX,int locY,word width,word height,word radius,colorObj* inColor);
  virtual void drawRoundRect(int locX,int locY,word width,word height,word radius,colorObj* inColor);
  virtual void drawCircle(int locX,int locY,word inDiam, colorObj* inColor);
  virtual void fillCircle(int locX,int locY,word inDiam, colorObj* inColor);
  virtual void drawVLine(int locX,int locY,word height,colorObj* inColor);
  virtual void drawHLine(int locX,int locY,word width,colorObj* inColor);
  virtual void drawLine(int locX,int locY,int locX2,int locY2,colorObj* inColor);
  virtual void drawPixel(int x,int y,colorObj* pColor);
    
  virtual void drawPixelInvert(int x,int y);
  virtual void frameRectInvert(int x,int y,word width,word height);

  virtual point     getPoint(void);
  virtual boolean   touched(void);
  
  boolean isGraphic(void);
  boolean isColor(void);
  boolean hasTouchScreen(void);
  boolean hadSDDrive(void);
  boolean canRead(void);
  
  protected:
    boolean  graphic;
    boolean  color;
    boolean  hasTouch;
    boolean  hasSD;
    boolean  readable;
};

#endif

