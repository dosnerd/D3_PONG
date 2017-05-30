/*
 * FPGA.h
 *
 *  Created on: 25 apr. 2017
 *      Author: Acer
 */

#ifndef INC_FPGA_H_
#define INC_FPGA_H_

#include <stdint.h>

#define FPGA_OPTION_NONE 			0x00
#define FPGA_OPTION_TEST_MODE 		0x01
#define FPGA_OPTION_INFRARED_MODE 	0x02
#define FPGA_OPTION_MENU 			0x08
#define FPGA_OPTION_HANDBAL_MODE 	0x32
#define FPGA_OPTION_HOCKEY_MODE 	0x64

#define FPGA_REGISTER_X_BALL		0x1
#define FPGA_REGISTER_Y_BALL		0x2
#define FPGA_REGISTER_Z_BALL		0x3
#define FPGA_REGISTER_X_BAT_P1		0x4
#define FPGA_REGISTER_Y_BAT_P1		0x5
#define FPGA_REGISTER_X_BAT_P2		0x6
#define FPGA_REGISTER_Y_BAT_P2		0x7
#define FPGA_REGISTER_TEXT_ADDRESS	0x8
#define FPGA_REGISTER_TEXT_VALUE	0x9
#define FPGA_REGISTER_STATE			0xF

#define FPGA_UPDATE_BALL			0x1
#define FPGA_UPDATE_P1				0x2
#define FPGA_UPDATE_P2				0x4
#define FPGA_UPDATE_OPTIONS			0x8
#define FPGA_UPDATE_ALL				FPGA_UPDATE_BALL | FPGA_UPDATE_P1 | FPGA_UPDATE_P2 | FPGA_UPDATE_OPTIONS

#define NUMBERS_OF_OBJECTS 			3

namespace GameEngine {
	class GameObject;
}

class Stream;
class FPGA {
public:
	virtual 					~FPGA();

private:
								FPGA(Stream *stream);

public:
	virtual void				turnOn();
	virtual void				turnOff();
	virtual void				update(uint8_t items = FPGA_UPDATE_ALL);

public:
	virtual void				setBall(GameEngine::GameObject *ball);
	virtual void				setBat(uint8_t player, GameEngine::GameObject *bat);
	virtual void				setOption(uint16_t options);
	virtual void				setRegister(uint8_t reg, uint16_t value);
	
	

public:
	static FPGA					*getInstance();
	uint16_t 					getOptions() const;

private:
	static FPGA					sInstance;
	uint16_t					m_options;
	Stream						*m_stream;
	GameEngine::GameObject		*m_objects[NUMBERS_OF_OBJECTS];

	void 						GPIOinit();
};

#endif /* INC_FPGA_H_ */
