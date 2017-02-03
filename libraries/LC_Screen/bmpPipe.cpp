#include "bmpPipe.h"
#include <colorObj.h>

#define COLOR_BUF_SIZE  4   // When grabbing a color off a bitmap you get 3 or 4 bytes. Go big!

bmpPipe::bmpPipe(void) { 
  
  fileOpen = false;
  haveInfo = false;
  haveSourceRect = false;
}


bmpPipe::bmpPipe(rect sourceRect) { 

  fileOpen = false;
  haveInfo = false;
  haveSourceRect = false;
  setSourceRect(sourceRect);
}


boolean bmpPipe::openPipe(char* filename) {

	rect aRect;
	
  fileOpen = false;
  haveInfo = false;
  if ((bmpFile = SD.open(filename)) != NULL) {        // Can we open the file?
    fileOpen = true;                                  // Got that far at least.
    haveInfo = readInfo();                            // Then see if we can understand it.
    if (haveInfo && !haveSourceRect) {                // If we can..
      aRect.x = 0;                               			// Default the source to the image.
      aRect.y = 0;
      aRect.width = imageWidth;
      aRect.height = imageHeight;
      setSourceRect(aRect);
    }
  }
  return haveInfo;                                    // Tell the caller if it worked.
}


bmpPipe::~bmpPipe(void) { 
  
    if (fileOpen) {
      bmpFile.close();
      fileOpen = false;
    }
 }


// .bmp files have the 2 & 4 byte numbers stored in reverse byte order
// than what we use here in Arduinoland. These two routines swap 'em back.

// For 2 byte numbers.
uint16_t bmpPipe::read16(File f) {

    uint16_t result;
  
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
  }

// For 4 byte numbers.
uint32_t bmpPipe::read32(File f) {
  
    uint32_t result;
  
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
  }


void bmpPipe::setSourceRect(rect inRect) { 
  
  sourceRect = inRect;
  haveSourceRect = true;
}


boolean bmpPipe::readInfo(void) {

    boolean   success = false;
    uint32_t  temp;
  
    if (fileOpen) {                                     // We get a file handle?
      if (read16(bmpFile) == 0x4D42) {                  // If we have something or other..
        temp = read32(bmpFile);                         // We grab the file size.
        temp = read32(bmpFile);                         // Creator bits
        temp = read32(bmpFile);                         // image offset (Why read it into temp first?)
        imageOffset = temp;                             // image offset!?! Save this! (Actually, this shuts up the compiler.)
        temp = read32(bmpFile);                         // read DIB header size?
        imageWidth = read32(bmpFile);                   // width? Good thing to save for later.
        imageHeight = read32(bmpFile);                  // Height? Negative means the data is right side up. Go figure..
        if (read16(bmpFile) == 1) {                     // if the next word is 1? What's this mean? Needs to be though.
          imageDepth = read16(bmpFile);                 // color depth.
          if (imageDepth == 24 || imageDepth == 32) {   // We can do 24 or 32 bits..
            pixBytes = imageDepth / 8;                  // Bytes / pixel
            if (!read32(bmpFile)) {                     // And no compression!
              bytesPerRow = imageWidth * pixBytes;      // Data takes up this much, but..
              while(bytesPerRow % 4) bytesPerRow++;     // We need to pad it to a multiple of 4.
              success = true;                           // Made it this far? We can do this!
            }
          }
        }
      }
    }
    return success;
  }


void bmpPipe::drawLine(int x,int y) {

    colorObj  thePixal;
    uint8_t   buf[COLOR_BUF_SIZE];   
    int       trace;
    int       endTrace;

    endTrace = x+sourceRect.width;
    for (trace=x;trace<=endTrace; trace++) {       // Ok, trace does x..x+width.
      bmpFile.read(buf,pixBytes);                 // Grab a pixel.
      thePixal.setColor(buf[2],buf[1],buf[0]);    // Load colorObj.
      screen->drawPixel(trace,y,&thePixal);       // Spat it out to the screen.
    }
  }


long bmpPipe::filePtr(int x,int y) {

    long  index;
  
    index = imageOffset;                                // Starting here..
    if (imageHeight>0) {                                // The image is upside down?
       index = index + ((imageHeight-y-1)*bytesPerRow);   // reverse..
    } else {
      index = index + (y*bytesPerRow);                  // not reverse.
    }
    index = index + (sourceRect.x * pixBytes);          // Add offset for x.
    return index;                                       // Tell the world.
  }

  
void bmpPipe::drawBitmap(int x,int y) {
  
  int trace;
  int endY;
  int srcY;
  
  if (haveInfo) {                                                                                      
    endY = y+sourceRect.height;
    srcY = sourceRect.y;
    for (trace=y; trace<=endY;trace++) {
      bmpFile.seek(filePtr(x,srcY++));
      drawLine(x,trace);
    }       
  }
}


/*
void bmpPipe::showPipe(void) {

  Serial.print("Src rect x,y,w,h : ");Serial.print(sourceRect.x);Serial.print(", ");Serial.print(sourceRect.y);
  Serial.print(", ");Serial.print(sourceRect.width);Serial.print(", ");Serial.println(sourceRect.height);
  Serial.print("Have src rect    : ");Serial.println(haveSourceRect);
  Serial.print("File Open        : ");Serial.println(fileOpen);
  Serial.print("Have info        : ");Serial.println(haveInfo);
  Serial.print("image offset     : ");Serial.println(imageOffset);
  Serial.print("image width      : ");Serial.println(imageWidth);
  Serial.print("Image height     : ");Serial.println(imageHeight);
  Serial.print("Image depth      : ");Serial.println(imageDepth);
  Serial.print("Pix Bytes        : ");Serial.println(pixBytes);
  Serial.print("Bytes per Row    : ");Serial.println(bytesPerRow);
}
*/
