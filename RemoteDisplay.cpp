#include <RemoteDisplay.h>

RemoteDisplay::RemoteDisplay(int16_t w, int16_t h,Transport &transporter) : transporter(transporter) {
    displayWidth = w;
    displayHeight = h;    
    x = 0;
    y = 0;
    wrap = true;
    rotation = 0;
    font = NULL;
    fontSize = 1;
    memset(&message,0,sizeof(message));
    memset(&writeMessage,0,sizeof(writeMessage));
}

void RemoteDisplay::reset() {
   message.command = RD_RESET;
   sendMessage();
}

void RemoteDisplay::begin() {
   message.command = RD_BEGIN;
   sendMessage();
}


void RemoteDisplay::drawPixel(int16_t x, int16_t y, uint16_t color) {
    message.command = RD_DRAW_PIXEL;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.color = color;
    sendMessage();
}

void RemoteDisplay::startWrite(void) {
    message.command = RD_START_WRITE;
    sendMessage();
}

void RemoteDisplay::writePixel(int16_t x, int16_t y, uint16_t color) {
    message.command = RD_WRITE_PIXEL;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.color = color;
    sendMessage();
}

void RemoteDisplay::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    message.command = RD_WRITE_FILL_RECT;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    sendMessage();
}

void RemoteDisplay::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    message.command = RD_WRITE_FAST_VLINE;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.height = h;
    message.a4.color = color;
    sendMessage();
}

void RemoteDisplay::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    message.command = RD_WRITE_FAST_HLINE;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.color = color;
    sendMessage();
}

void RemoteDisplay::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    message.command = RD_WRITE_LINE;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.x = x1;
    message.a4.y = y1;
    message.a5.color = color;
    sendMessage();
}

void RemoteDisplay::endWrite(void) {
    message.command = RD_END_WRITE;
    sendMessage();
}

void RemoteDisplay::setRotation(uint8_t r) {
    message.command = RD_SET_ROTATION;
    message.a1.rotation = r;

    // swap the coordinates
    // if switching from landscape to portrait, or vice versa
    if ((rotation % 2) != (r % 2)) {
        uint16_t temp = displayHeight;
        displayHeight = displayWidth;
        displayWidth = temp;
    }
    rotation = r;

    sendMessage();
}

void RemoteDisplay::invertDisplay(boolean i) {
    message.command = RD_INVERT_DISPLAY;
    message.a1.b = i;
    sendMessage();
}

void RemoteDisplay::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    message.command = RD_DRAW_FAST_VLINE;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.height = h;
    message.a4.color = color;
    sendMessage();
}

void RemoteDisplay::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    message.command = RD_DRAW_FAST_HLINE;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.color = color;
    sendMessage();
}

void RemoteDisplay::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    message.command = RD_FILL_RECT;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    sendMessage();
}

void RemoteDisplay::fillScreen(uint16_t color) {
    message.command = RD_FILL_SCREEN;
    message.a1.color = color;
    sendMessage();
}

void RemoteDisplay::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    message.command = RD_DRAW_LINE;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.x = x1;
    message.a4.y = y1;
    message.a5.color = color;
    sendMessage();
}

void RemoteDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    message.command = RD_DRAW_RECT;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    sendMessage();
}

void RemoteDisplay::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    message.command = RD_DRAW_CIRCLE;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.radius = r;
    message.a4.color = color;
    sendMessage();
}

void RemoteDisplay::drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
    message.command = RD_DRAW_CIRCLE_HELPER;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.radius = r;
    message.a4.cornerName = cornername;
    message.a5.color = color;
    sendMessage();
}

void RemoteDisplay::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    message.command = RD_FILL_CIRCLE;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.radius = r;
    message.a4.color = color;
    sendMessage();
}

void RemoteDisplay::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
    message.command = RD_FILL_CIRCLE_HELPER;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.radius = r;
    message.a4.cornerName = cornername;
    message.a5.delta = delta;
    message.a6.color = color;
    sendMessage();
}

void RemoteDisplay::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    message.command = RD_DRAW_TRIANGLE;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.x = x1;
    message.a4.y = y1;
    message.a5.x = x2;
    message.a6.y = y2;
    message.a7.color = color;
    sendMessage();
}

void RemoteDisplay::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    message.command = RD_FILL_TRIANGLE;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.x = x1;
    message.a4.y = y1;
    message.a5.x = x2;
    message.a6.y = y2;
    message.a7.color = color;
    sendMessage();
}

void RemoteDisplay::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
    message.command = RD_DRAW_ROUND_RECT;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.radius = radius;
    message.a6.color = color;
    sendMessage();
}

void RemoteDisplay::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
    message.command = RD_FILL_ROUND_RECT;
    message.a1.x = x0;
    message.a2.y = y0;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.radius = radius;
    message.a6.color = color;
    sendMessage();
}

//
//  1 bit/pixel bitmap
//  Rows are byte alligned
//
void RemoteDisplay::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
    message.command = RD_DRAW_BITMAP1;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    int16_t size = (w+7)/8*h; 
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    message.command = RD_DRAW_BITMAP2;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    message.a6.color = bg;
    int16_t size = (w+7)/8*h;  
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    message.command = RD_DRAW_BITMAP1;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    int16_t size = (w+7)/8*h;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    message.command = RD_DRAW_BITMAP2;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    message.a6.color = bg;
    int16_t size = (w+7)/8*h;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
    message.command = RD_DRAW_X_BITMAP;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    message.a5.color = color;
    uint16_t size = (w+7)/8*h;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h) {
    message.command = RD_DRAW_GRAYSCALE_BITMAP1;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) {
    message.command = RD_DRAW_GRAYSCALE_BITMAP1;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], const uint8_t mask[], int16_t w, int16_t h) {
    message.command = RD_DRAW_GRAYSCALE_BITMAP2;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h;
    uint16_t maskSize = (w+7)/8*h;
    sendMessage(size,bitmap,maskSize,mask);
}

void RemoteDisplay::drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h) {
    message.command = RD_DRAW_GRAYSCALE_BITMAP2;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h;
    uint16_t maskSize = (w+7)/8*h;
    sendMessage(size,bitmap,maskSize,mask);
}

void RemoteDisplay::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h) {
    message.command = RD_DRAW_RGB_BITMAP1;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h*2;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h) {
    message.command = RD_DRAW_RGB_BITMAP1;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h*2;
    sendMessage(size,bitmap);
}

void RemoteDisplay::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h) {
    message.command = RD_DRAW_RGB_BITMAP2;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h*2;
    uint16_t maskSize = (w+7)/8*h;
    sendMessage(size,bitmap,maskSize,mask);
}

void RemoteDisplay::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h) {
    message.command = RD_DRAW_RGB_BITMAP2;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = w;
    message.a4.height = h;
    uint16_t size = w*h*2;
    uint16_t maskSize = (w+7)/8*h;
    sendMessage(size,bitmap,maskSize,mask);
}

void RemoteDisplay::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
    message.command = RD_DRAW_CHAR;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.c = c;
    message.a4.color = color;
    message.a5.color = bg;
    message.a6.size = size;
    sendMessage();
}

void RemoteDisplay::setCursor(int16_t x, int16_t y) {
    message.command = RD_SET_CURSOR ;
    message.a1.x = x;
    message.a2.y = y;
    this->x = x;
    this->y = y;
    sendMessage();
}

void RemoteDisplay::setTextColor(uint16_t c) {
    message.command = RD_SET_TEXT_COLOR1;
    message.a1.color = c;
    sendMessage();
}

void RemoteDisplay::setTextColor(uint16_t c, uint16_t bg) {
    message.command = RD_SET_TEXT_COLOR2;
    message.a1.color = c;
    message.a2.color = bg;
    sendMessage();
}

void RemoteDisplay::setTextSize(uint8_t s) {
    message.command = RD_SET_TEXT_SIZE;
    message.a1.size = s;
    fontSize = s;
    sendMessage();
}

void RemoteDisplay::setTextWrap(boolean w) {
    message.command = RD_SET_TEXT_WRAP;
    message.a1.b = w;
    wrap = w;
    sendMessage();
}

void RemoteDisplay::cp437(boolean x) {
    message.command =  RD_CP437;
    message.a1.b = x;
    sendMessage();
}

void RemoteDisplay::vertScroll(uint16_t y, int16_t height, int16_t offset) {
    message.command =  RD_VSCROLL;
    message.a1.y = y;
    message.a2.height = height;
    message.a3.delta = offset;
    sendMessage();
}

void RemoteDisplay::horzScroll(uint16_t x, uint16_t width, uint16_t offset) {
    message.command =  RD_HSCROLL;
    message.a1.x = x;
    message.a2.width = width;
    message.a3.delta = offset;
    sendMessage();
}

void RemoteDisplay::scroll(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t dx, uint16_t dy) {
    message.command =  RD_SCROLL;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.width = width;
    message.a4.height = height;
    message.a5.delta = dx;
    message.a6.delta = dy;
    sendMessage();

}

void RemoteDisplay::setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1) {
    message.command =  RD_SET_ADDR_WINDOW;
    message.a1.x = x;
    message.a2.y = y;
    message.a3.x = x1;
    message.a4.y = y1;
    sendMessage();
}

void RemoteDisplay::pushColors(const uint8_t *block, int16_t n, bool first) {
    message.command =  RD_PUSH_COLORS;
    message.a1.b = first;
    sendMessage(n*2,block);
}

void RemoteDisplay::pushColors(uint16_t cacheKey, int16_t n, bool first) {
    message.command =  RD_PUSH_COLORS;
    message.a1.b = first;
    message.a2.size16 = n;
    message.a3.cacheHandle = cacheKey;
    sendMessage();
}

void RemoteDisplay::cacheData(uint16_t cacheKey,uint16_t size, const uint8_t *block) {
    message.command =  RD_CACHE_DATA;
    message.a1.cacheHandle = cacheKey;
    sendMessage(size,block);
}


void RemoteDisplay::setFont(const GFXfont *f) {
    int16_t size = 0;

    message.command = RD_SET_FONT;

    if (f != NULL) {
        this->font = f;
        charHeight = f->yAdvance ;
    } else {
        charHeight = 8; 
    }
    sendMessage(f);
}

uint16_t RemoteDisplay::charWidth(const char c) {

    if (!font) {
       return (6 * fontSize);
    } else {
       uint16_t size = 0;

       if ((c >= font->first) && (c <= font->last)) {
           const GFXglyph &glyph = font->glyph[c-font->first];
           size = glyph.width * fontSize;
       } 

       return (size); 
    }
}

void RemoteDisplay::flush() {
    if (writeMessage.length > 0) {
        writeMessage.command = RD_WRITE;
        if (transporter.write(sizeof(writeMessage),&writeMessage)) {
            memset(&writeMessage,0,sizeof(writeMessage));
        }
    }
}

size_t RemoteDisplay::write(uint8_t c) {
    writeMessage.data[writeMessage.length++] = c; 
    if (writeMessage.length == sizeof(writeMessage.data)) {
        flush();
    }

    switch (c) {
       case '\n':
           x = 0;
           y = y + charHeight * fontSize;
           flush();
           break;
       case '\r':
           // do nothing for CR
           break;
       default:
           uint16_t width = charWidth(c);
           x +=  width;
           if ((wrap) && (x >= displayWidth)) {
               x = width;
               y += charHeight * fontSize;
           }
           break;
    }
    return (1);
}

int16_t RemoteDisplay::height(void) const {
     return (displayHeight);
}

int16_t RemoteDisplay::width(void) const {
    return (displayWidth);
}

uint8_t RemoteDisplay::getRotation(void) const {
    return (rotation);
}

int16_t RemoteDisplay::getCursorX(void) const {
    return (x);
}

int16_t RemoteDisplay::getCursorY(void) const {
    return (y);
}

void    RemoteDisplay::getTextBounds(char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
   int len = strlen(string);
   int wid = len*fontSize*8;
   *x1 = x;
   *y1 = y;
   *w = wid;
   *h = fontSize * 8;
}

void    RemoteDisplay::getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
}

void RemoteDisplay::sendMessage() {

     //
     // Do we have any un-written character data?
     // If so, send that first.
     //
     if (writeMessage.length > 0) {
         flush();
     }

     if (transporter.write(sizeof(message),&message)) {
         memset(&message,0,sizeof(message));
     }
}

//
// index up to three buffers as one.
//
uint8_t getcc(uint16_t size,const void *buffer,
              uint16_t size2,const void *buffer2,
              uint16_t size3,const void *buffer3,
              uint16_t index) {

    if (index < size) {
       return ((uint8_t*)buffer)[index];
    } else if (index < (size+size2)) {
       return ((uint8_t*)buffer2)[index - size];
    } else if (index < (size+size2+size3)) {
       return ((uint8_t*)buffer3)[index - size - size2];
    } else {
       return (0);
    }
}

void RemoteDisplay::sendMessage(uint16_t size,const void *buffer,
                                uint16_t size2,const void *buffer2,
                                uint16_t size3,const void *buffer3) {

    //
    // Do we have any un-written character data?
    // If so, send that first.
    //
    if (writeMessage.length > 0) {
        flush();
    }

    uint16_t index = 0;
    uint16_t loopMax;

    message.length = size + size2 + size3;    

    if (size > sizeof(message.data)) {
        loopMax = sizeof(message.data);
    } else {
      loopMax = size;
    }
    
    for (int i = 0; i < loopMax; i++) {
        message.data[i] = getcc(size,buffer,size2,buffer2,size3,buffer3,index++);
    }          

    // Send the first packet
    if (transporter.write(sizeof(message),&message)) {
        memset(&message,0,sizeof(message));

        //
        // While we still have data
        // send packets
        //
        while (index < size) {
            RD_DATA   dataMessage;

            dataMessage.command = RD_DATA_MSG;

            loopMax = (size - index);
            if (loopMax > sizeof(message.data)) {
                loopMax = sizeof(message.data);
            }

            for (int i = 0; i < loopMax; i++) {
                dataMessage.data[i] = getcc(size,buffer,size2,buffer2,size3,buffer3,index++);
            }          

            //
            // Send the data packet
            //
            if (!transporter.write(sizeof(dataMessage),&dataMessage)) {
                //
                // if sending the data packet failed for some reason,
                // send a data-reset packet, just in case the 
                // other side is back.
                //
                dataMessage.command = RD_DATA_RESET;
                transporter.write(sizeof(dataMessage),&dataMessage);
                break;
            }
        }

    }
}



void RemoteDisplay::sendMessage(const GFXfont *f) {
   uint16_t size = sizeof(GFXfont);
   uint16_t fontCharCount = (f->last-f->first)+1;
   uint16_t maxBitmapData = 0;
   uint16_t lastBitmapDataSize = 0;

   size += (fontCharCount*sizeof(GFXglyph));

   // 
   // Assume the font bitmap is ordered the same way as the glyph array
   // it will work either way, but will be less effecient
   //
   for (int i = (fontCharCount-1); i >= 0; i--) {
      if (f->glyph[i].bitmapOffset > maxBitmapData) {
          maxBitmapData = f->glyph[i].bitmapOffset;
          // figure out how many bytes make up this bitmap
          lastBitmapDataSize = (f->glyph[i].width * f->glyph[i].height + 7)/8;
      } 
   }

   message.a1.size = (fontCharCount * sizeof(GFXglyph));
   message.a2.size = (maxBitmapData + lastBitmapDataSize);

   sendMessage(sizeof(GFXfont),f,
               message.a1.size,f->glyph,
               message.a2.size,f->bitmap);

}

boolean  RemoteDisplay::getMessage(RD_ARGS &message,unsigned long timeout) {

   if (transporter.read(sizeof(message),&message)) {
       return (true);
   } 
   if (timeout != 0) {
       delay(timeout);
   }
   if (transporter.read(sizeof(message),&message)) {
       return (true);
   } 

   return (false);
}

