#include "enc28j60.h"
uint8_t spi1_rx_buf[RXBUF_SIZE];
uint8_t spi1_tx_buf[TXBUF_SIZE];
uint8_t rx_buf_head = 0;
uint8_t rx_buf_tail = 0;

uint8_t tx_index; 			//тут хранится количество переданных байт
uint8_t tx_len;   			//сколько всего байт нужно передать
uint8_t *tx_data;     		//указатель на массив с передаваемыми данными

void SPI_SendByte(uint8_t *data, uint8_t len)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) {};
	tx_index = 0;
	tx_len = len;
	tx_data = data;
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);
}

uint8_t SPI_ReceiveByte(void)
{
	uint8_t bt = spi1_rx_buf[rx_buf_tail];
	rx_buf_tail++;
//	rx_buf_tail = rx_buf_tail+1 % TXBUF_SIZE;
	return bt; //вернём регистр данных
}

void enc28j60_init (void)
{
	delay_ms(100);
	RST_0();
	delay_ms(5);
	RST_1();

	while (rx_buf_tail != RXBUF_SIZE) {
		spi1_rx_buf[rx_buf_tail] = 0x00;
		rx_buf_tail++;
	}
	rx_buf_tail = 0;

	SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

	enc28j60_writeOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);
	delay_ms(2);
	//проверим, что всё перезагрузилось
	while(!(enc28j60_readOp(ENC28J60_READ_CTRL_REG,ESTAT)&ESTAT_CLKRDY));
}

void enc28j60_writeOp(uint8_t op,uint8_t addres, uint8_t data)
{
	spi1_tx_buf[0] = op|(addres&ADDR_MASK);
	spi1_tx_buf[1] = data;
	SPI_SendByte(spi1_tx_buf, 2);
}

uint8_t enc28j60_readOp(uint8_t op, uint8_t addres)
{
	uint8_t result;
	enc28j60_writeOp (op, addres, 0x00);
	while (rx_buf_head != rx_buf_tail) {
		result = spi1_rx_buf[rx_buf_tail];
		rx_buf_tail++;
	}
//	spi1_tx_buf[0] = spi1_tx_buf[1] = 0xFF;
//	SPI_SendByte(spi1_tx_buf, 2);
//	//пропускаем ложный байт
//	if(addres & 0x80) SPI_ReceiveByte();
//	result=SPI_ReceiveByte();

	return result;
}

void SPI1_IRQHandler (void)
{
	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE)) {
		CS_SELECT();
		SPI_I2S_SendData(SPI1, tx_data[tx_index]);
		tx_index++;
		if (tx_index >= tx_len) {
			SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
			while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) {};
			CS_DESELECT();
			NVIC_ClearPendingIRQ(SPI1_IRQn);
		}
		SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_TXE);
	}

	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE)) {
		GPIOC->ODR ^= GPIO_Pin_14;
		spi1_rx_buf[rx_buf_head++] = (uint8_t)(SPI_I2S_ReceiveData(SPI1));
		SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
	}
}
