#include "net.h"
#include "string.h"
#include "uart.h"

uint8_t net_buf[ENC28J60_MAXFRAME];


void eth_read(enc28j60_frame_ptr *frame, uint16_t len)
{
	if (len>=sizeof(enc28j60_frame_ptr))
	{
//		printf(str1, "%d", len);
//		sprintf(str1, "%02X; %d", frame->addr_src[0], len);
//		sprintf(str1,"%02X:%02X:%02X:%02X:%02X:%02X-%02X:%02X:%02X:%02X:%02X:%02X; %d; %04Xrn",
//				frame->addr_src[0],frame->addr_src[1],frame->addr_src[2],frame->addr_src[3],frame->addr_src[4],frame->addr_src[5],
//				frame->addr_dest[0],frame->addr_dest[1],frame->addr_dest[2],frame->addr_dest[3],frame->addr_dest[4],frame->addr_dest[5],len,be16toword(frame->type));
//		uart1_send_buf((uint8_t*)str1, strlen(str1));
//		HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
	}
}

void net_pool(void)
{
	uint8_t str1[]={"Transmitt"};
	uint8_t len = 66;
	enc28j60_frame_ptr *frame=(void*)net_buf;
//	while ((len=enc28j60_packetReceive(net_buf,sizeof(net_buf)))>0)
//	  {
//	    eth_read(frame,len);
//	  }
	uart1_send(0x22);
	uart1_send(0x33);
	uart1_send(0x44);
	uart1_send_buf(str1, strlen(str1));

}



