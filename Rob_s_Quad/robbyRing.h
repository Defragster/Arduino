#ifndef robbyRing_h
#define robbyRing_h

#include <timeObj.h>
#include <chainPixels.h>


class robbyRing : public pixelGroup {
  
  public:
            robbyRing(word numLEDs);
            ~robbyRing(void);
            
            float  calculatePercent(void);
    virtual void   draw(void);
    
  private:
          timeObj  lightTimer;
          int      currentSlice;
          boolean  ourInit;
};
 
 
 class robbyTailLight : public pixelGroup {
  
  public:
            robbyTailLight(word numLEDs);
            ~robbyTailLight(void);
            
    virtual void   draw(void);
    
  private:
         
          boolean  drawn;
};


#endif   
