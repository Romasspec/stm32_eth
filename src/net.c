#include "net.h"

uint8_t net_buf[ENC28J60_MAXFRAME];
char str1[60]={0};

void eth_read(enc28j60_frame_ptr *frame, uint16_t len)
{
	if (len>=sizeof(enc28j60_frame_ptr))
	{
//		sprintf(str1,"%02X:%02X:%02X:%02X:%02X:%02X-%02X:%02X:%02X:%02X:%02X:%02X; %d; %04Xrn",
//		frame->addr_src[0],frame->addr_src[1],frame->addr_src[2],frame->addr_src[3],frame->addr_src[4],frame->addr_src[5],
//		frame->addr_dest[0],frame->addr_dest[1],frame->addr_dest[2],frame->addr_dest[3],frame->addr_dest[4],frame->addr_dest[5],len,be16toword(frame->type));
//		HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
	}
}

void net_pool(void)
{
	uint16_t len;
	enc28j60_frame_ptr *frame=(void*)net_buf;
}



