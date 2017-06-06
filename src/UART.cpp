/*
 * UART.cpp
 *
 *  Created on: 22 apr. 2017
 *      Author: Acer
 */
#include <UART.h>
#include <LEDS.h>

UART UART::sInstance2(USART2);
UART UART::sInstance4(UART4);

UART::UART(USART_TypeDef* USARTx)
	: m_USARTx(USARTx)
{
	if (m_USARTx != UART4 && m_USARTx != USART2){
		throw "Invalid port";
	}

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	if (m_USARTx == UART4){

#if UART_TRANSMIT_ENABLE
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
#else
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
#endif

	} else {

#if UART_TRANSMIT_ENABLE
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
#else
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
#endif

	}

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void UART::GPIOconfig() {
	//Configure PA0, PA1 as UART4

	if (m_USARTx == UART4){
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
#if UART_TRANSMIT_ENABLE
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
#endif
	} else {
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_UART4);
#if UART_TRANSMIT_ENABLE
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_UART4);
#endif
	}
}

void UART::UARTinit() {
	USART_InitTypeDef USART_InitStructure;

	//Configure UART4
	if (m_USARTx == UART4)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	else
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStructure.USART_BaudRate = 1578.5000; //1562.5000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

#if UART_TRANSMIT_ENABLE
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
#else
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
#endif
	USART_Init(m_USARTx, &USART_InitStructure);
}

UART *UART::getInstance(uint8_t port){
	if (port == 2)
		return &sInstance2;
	else
		return &sInstance4;
}

void UART::write(uint16_t data){
#if UART_TRANSMIT_ENABLE
	while(!(m_USARTx->SR & USART_FLAG_TC));
	USART_SendData(m_USARTx, data);
#else
	(void)data;
#endif
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
	if (m_USARTx->SR & USART_FLAG_RXNE){
		buffer = USART_ReceiveData(m_USARTx);
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
	USART_ITConfig(m_USARTx, USART_IT_RXNE, ENABLE);
	if (m_USARTx == UART4)
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	else
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void UART::interruptRead(){
	uint16_t buffer;

	buffer = USART_ReceiveData(m_USARTx);
	if (m_buffer.length() < UART_BUFFER_LENGTH){
		//read from uart buffer
		m_buffer.add(buffer);
	}
	notifyObservers();
}

void USART2_IRQHandler(void) {
	//check if buffer is not empty interrupt
	if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
		UART::getInstance(2)->interruptRead();
	}
}

void UART4_IRQHandler(void) {
	//check if buffer is not empty interrupt
	if (USART_GetITStatus(UART4, USART_IT_RXNE)) {
		UART::getInstance(4)->interruptRead();
	}
}

#endif
