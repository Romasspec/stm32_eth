#ifndef NET_H_
#define NET_H_

#include "enc28j60.h"

//--------------------------------------------------
typedef struct enc28j60_frame{
  uint8_t addr_dest[6];
  uint8_t addr_src[6];
  uint16_t type;
  uint8_t data[];
} enc28j60_frame_ptr;

#define be16toword(a) ((((a)>>8)&0xff)|(((a)<<8)&0xff00))

void net_pool(void);

#endif /* NET_H_ */
