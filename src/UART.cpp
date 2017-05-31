/*
 * UART.cpp
 *
 *  Created on: 22 apr. 2017
 *      Author: Acer
 */
#include <UART.h>
#include <LEDS.h>
#include <stm32f4xx_conf.h>

UART UART::sInstance;

UART::UART() {
	GPIOinit();
	GPIOconfig();
	UARTinit();

#if UART_INTERRUPT_ENABLE
	UARTinterruptConfig();
#endif

	USART_Cmd(UART4, ENABLE);
}

UART::~UART() {

}

void UART::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	//Configure PA0, PA1 as alternate function pushpull mode
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void UART::GPIOconfig() {
	//Configure PA0, PA1 as UART4
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
}

void UART::UARTinit() {
	USART_InitTypeDef USART_InitStructure;

	//Configure UART4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	USART_InitStructure.USART_BaudRate = 273.5;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_Init(UART4, &USART_InitStructure);
}

UART *UART::getInstance(){
	return &sInstance;
}

void UART::write(uint16_t data){
	//wait until available
	while(!(UART4->SR & USART_FLAG_TC));
	USART_SendData(UART4, data);
}

const uint16_t UART::read(){
	uint16_t buffer = 0;

#if UART_INTERRUPT_ENABLE
	//use data in buffer if exists
	if (m_buffer.length() > 0){
		buffer = m_buffer[0];
		m_buffer.remove(0);
	}
#else
	//read from uart buffer
	if (UART4->SR & USART_FLAG_RXNE){
		buffer = USART_ReceiveData(UART4);
	}
#endif

	return buffer;
}

const uint16_t UART::getBufferLenght() const{
	return m_buffer.length();
}

#if UART_INTERRUPT_ENABLE

void UART::UARTinterruptConfig() {
	NVIC_InitTypeDef NVIC_InitStructure;

	//enable interrupt
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void UART::interruptRead(){
	uint16_t buffer;

	//read from uart buffer
	buffer = USART_ReceiveData(UART4);
	m_buffer.add(buffer);
	notifyObservers();
}

void UART4_IRQHandler(void) {
	//check if buffer is not empty interrupt
	if (USART_GetITStatus(UART4, USART_IT_RXNE)) {
		UART::getInstance()->interruptRead();
	}
}

#endif
