/*
 * TextManager.h
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_TEXTMANAGER_H_
#define INC_MENU_TEXTMANAGER_H_

#include <string>

namespace Menu {

class TextManager {
private:
								TextManager();
	virtual 					~TextManager();

public:
	static std::string 			to_string(int16_t number, bool hex = false);
	static void					print(std::string text);
	static void					printLine(std::string text);
	static void					clearAll();
	static void					clearLine();

	static void					setColor(uint16_t color);
	static void					setLine(uint8_t line);
	static void					setColumn(uint8_t column);


private:
	static uint8_t				m_row, m_column;
	static uint16_t				m_color;
};

} /* namespace Menu */

#endif /* INC_MENU_TEXTMANAGER_H_ */
