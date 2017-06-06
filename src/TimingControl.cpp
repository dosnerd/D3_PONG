/*
 * TimingControl.cpp
 *
 *  Created on: 4 jun. 2017
 *      Author: Acer
 */

#include <TimingControl.h>
#include <stm32f4xx_conf.h>

TimingControl TimingControl::sInstance;

void TimingControl::initTimerArray() {
	uint8_t i;
	for (i = 0; i < AMOUNTS_OF_TIMERS; ++i) {
		m_timers[i] = TIMER_NO_DELAY;
	}
}

void TimingControl::initTimer() {
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InitStructure.TIM_Prescaler = 0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = TIMER_MAX_VALUE;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

TimingControl::TimingControl() {
	initTimerArray();
	initTimer();
}

TimingControl::~TimingControl() {
}

TimingControl* TimingControl::getInstance() {
	return &sInstance;
}

void TimingControl::setDelay(uint8_t timer, uint32_t delay) {
	if (timer < AMOUNTS_OF_TIMERS){
		m_activeOn[timer] = getTime();
		m_timers[timer] = getTime() + delay;
	}
}

uint32_t TimingControl::getTime() {
	return TIM2->CNT;
}

bool TimingControl::isDone(uint8_t timer) {
	uint8_t i;
	uint32_t time;

	if (timer < AMOUNTS_OF_TIMERS){
		for (i = 0; i < AMOUNTS_OF_TIMERS; ++i) {
			time = getTime();
			if (m_timers[i] != TIMER_NO_DELAY){
				if (time < m_activeOn[i] || time > m_timers[i]){
					m_timers[i] = TIMER_NO_DELAY;
				}
			}
		}

		if (m_timers[timer] == TIMER_NO_DELAY)
			return true;
	}
	return false;
}
