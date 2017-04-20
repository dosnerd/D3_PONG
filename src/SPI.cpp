/*
 * SPI.cpp
 *
 *  Created on: 20 apr. 2017
 *      Author: Acer
 */

#include <SPI.h>
#include <stm32f4xx_conf.h>

SPI::SPI() {
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
}

SPI::~SPI() {
}

void SPI::write(uint16_t data){
	uint16_t input;
	while (!(SPI2->SR & SPI_I2S_FLAG_TXE))
				; // wait until transmit buffer empty
	while ( SPI2->SR & SPI_I2S_FLAG_BSY)
		; // wait until SPI is not busy anymore

	//check if receive buffer is not empty
	if (SPI2->SR & SPI_I2S_FLAG_RXNE){
		input = SPI2->DR;
		m_buffer.add(input);
	}

	SPI_I2S_SendData(SPI2, data);
}

const uint16_t SPI::read() {
	uint16_t buffer = 0;
	if (m_buffer.length() > 0){
		buffer = m_buffer[0];
		m_buffer.remove(0);
	}

	return buffer;
}

const uint16_t SPI::getBufferLenght() const{
	return m_buffer.length();
}
