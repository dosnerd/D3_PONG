/*
 * SPI.cpp
 *
 *  Created on: 20 apr. 2017
 *      Author: Acer
 */

#include <SPI.h>
#include <Vector.h>
#include <stm32f4xx_conf.h>

SPI SPI::sInstance;

SPI::SPI() {
	GPIOinit();
	GPIOconfig();
	SPIinit();

#if SPI_INTERRUPT_ENABLE
	//enable SPI2 interrupt
	SPIinterruptConfig();
#endif

	//enable SPI
	SPI_Cmd(SPI2, ENABLE);
}

SPI::~SPI() {
}

void SPI::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure2;

	//Configure PB13, PB14, PB15 as alternate functoin pushpull
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


#if SPI_SLAVE_MODE_ENABLE
	//Configure PB12 as output pushpull
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure2);
#endif
}

void SPI::GPIOconfig() {
	//Configure PB13, PB14, PB15 as SPI2
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
}

void SPI::SPIinit() {
	SPI_InitTypeDef SPI_InitStructure;

	//Configure SPI2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI2, &SPI_InitStructure);
}

void SPI::write(uint16_t data){
#if SPI_SLAVE_MODE_ENABLE
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
#endif

	while (!(SPI2->SR & SPI_I2S_FLAG_TXE))
				; // wait until transmit buffer empty
	while ( SPI2->SR & SPI_I2S_FLAG_BSY)
		; // wait until SPI is not busy

	SPI_I2S_SendData(SPI2, data);
}

const uint16_t SPI::read() {
	uint16_t buffer = 0;

#if SPI_INTERRUPT_ENABLE
	//read from buffer if not empty
	if (m_buffer.length() > 0){
		buffer = m_buffer[0];
		m_buffer.remove(0);
	}
#else
	while ( SPI2->SR & SPI_I2S_FLAG_BSY)
			; //wait until SPI is not busy

	//check if receive buffer is not empty
	if (SPI2->SR & SPI_I2S_FLAG_RXNE){
		buffer = SPI2->DR;
	}
#endif

	return buffer;
}

const uint16_t SPI::getBufferLenght() const{
	return m_buffer.length();
}

SPI *SPI::getInstance(){
	return &sInstance;
}

#if SPI_INTERRUPT_ENABLE

void SPI::SPIinterruptConfig() {
	NVIC_InitTypeDef NVIC_InitStructure;

	//enable SPI2 interrupt
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	SPI_ITConfig(SPI2, SPI_IT_RXNE, ENABLE);
}

void SPI::interruptRead(){
	uint16_t buffer;

	//check if receive buffer is not empty
	if (SPI2->SR & SPI_I2S_FLAG_RXNE){
		buffer = SPI2->DR;
		m_buffer.add(buffer);
	}
}

void SPI2_IRQHandler(){
	//check if buffer is not empty interrupt
	if (SPI_GetITStatus(SPI2, SPI_IT_RXNE)){
		SPI::getInstance()->interruptRead();

#if SPI_SLAVE_MODE_ENABLE
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
#endif
	}
}
#endif
