#ifndef __TRANSPORT_H
#define __TRANSPORT_H

class Transport {
   public:

       virtual boolean write(uint16_t size,const void *data) = 0;
       virtual boolean read(uint16_t size,void *data) = 0;
};

#endif

