/*
 * TimingControl.h
 *
 *  Created on: 4 jun. 2017
 *      Author: Acer
 */

#ifndef INC_TIMINGCONTROL_H_
#define INC_TIMINGCONTROL_H_

#include <stdint.h>

#define AMOUNTS_OF_TIMERS		4
#define GAME_TIMER				0
#define ANIMATION_TIMER			1
#define SYNC_TIMER				2
#define MENU_TEST_TIMER			3
#define TIMER_NO_DELAY			0xFFFFFFFF
#define TIMER_MAX_VALUE			0xFFFFFFF0

class TimingControl {
public:
	virtual 					~TimingControl();

private:
								TimingControl();
	void initTimerArray();
	void initTimer();

public:
	void						setDelay(uint8_t timer, uint32_t delay);
	static TimingControl		*getInstance();
	uint32_t					getTime();
	bool						isDone(uint8_t timer);

private:
	static TimingControl		sInstance;
	uint32_t					m_timers[AMOUNTS_OF_TIMERS];
	uint32_t					m_activeOn[AMOUNTS_OF_TIMERS];
};

#endif /* INC_TIMINGCONTROL_H_ */
