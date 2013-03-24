#ifndef touchObj_h
#define touchObj_h

#include "drawObj.h"
#include "lists.h"
#include "idlers.h"

enum { 
  active,    // unselected, waiting
  inactive,  // not accepting touches.
  touched,   // Selected
  dragging   // Selected and tracking.
};

class touchObj : public drawObj, public linkListObj {
  
  public:
    touchObj(void);
    touchObj(Point inLoc, word inWidth,word inHeight);
    ~touchObj(void);
  
    virtual void    setState(byte inState);
    virtual boolean checkActiveTouch(Point where);
    virtual boolean checkInactiveTouch(Point where);
    virtual boolean checkTouchedTouch(Point where);
    virtual boolean checkDraggingTouch(Point where);
    virtual boolean checkTouch(Point where);
    virtual void    drawSelf(void);
    virtual void    doAction(Point where);      // Override me for action!

  protected:
            byte    state;
            boolean dragable;
};


class touchList : public idler, public linkList {
  
  public:
    touchList(void);
    ~touchList(void);
    
    void init(void);
    void addObj(touchObj* newObj);
    void deselect(void);
    void idle(void);
  
  private:
    touchObj*  selected;
};


extern touchList theTouchList;


#endif
