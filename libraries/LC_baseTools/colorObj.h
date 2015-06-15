#ifndef colorObj_h
#define colorObj_h

#include "mapper.h"
#include "multiMap.h"

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF


// mask extremes..
#define OPAQUE       100   // All the new color
#define TRANSPARENT  0     // None of the new color

class colorObj {

public:
  colorObj(byte inRed, byte inGreen, byte inBlue);
  colorObj(word color16);
  colorObj(void);

  void setColor(byte inRed, byte inGreen, byte inBlue);
  void setColor(word color16);
  void setColor(colorObj* inColor);
  word getColor16(void);
    
  byte getRed(void);
  byte getGreen(void);
  byte getBlue(void);

  colorObj blend(colorObj* mixinColor,byte mixPercent);
    
 // void printRGB(void);

private :
  byte red;
  byte green;
  byte blue;
};

extern colorObj red;
extern colorObj blue;
extern colorObj white;
extern colorObj black;
extern colorObj green;
extern colorObj cyan;
extern colorObj magenta;
extern colorObj yellow;


// ****** colorMapper ******

class colorMapper {

public:
  colorMapper(void);
  colorMapper(colorObj* inStart, colorObj* inEnd);
  colorMapper(word startC16,word endC16);
  ~colorMapper(void);
  
  void setColors(colorObj* inStart, colorObj* inEnd);

  colorObj Map(float percent);
  //void     printColors(void);
  
private :
  mapper* redMapper;
  mapper* greenMapper;
  mapper* blueMapper;
};


// ****** colorMultiMap ******


class colorMultiMap {
    
    public :
    colorMultiMap(void);
    ~colorMultiMap(void);
    
    void      addColor(double inX, colorObj* color);  // At some numeric value we resolve to this color.
    void      clearMap(void);
    colorObj  Map(double inVal);
    
    protected :
    multiMap  redMap;
    multiMap  greenMap;
    multiMap  blueMap;
};


#endif
