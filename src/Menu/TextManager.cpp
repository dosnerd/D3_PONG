/*
 * TextManager.cpp
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#include <Menu/TextManager.h>
#include <FPGA.h>

namespace Menu {

uint8_t TextManager::m_row = 0, TextManager::m_column = 0;
uint16_t TextManager::m_color = 0xFFF;
bool TextManager::m_colorChanged = true;
TextManager::TextManager()
{
}

TextManager::~TextManager() {

}

void Menu::TextManager::print(std::string text) {
	uint16_t i;
	for (i = 0; i < text.length(); ++i) {
		if (text.c_str()[i] == '\n'){
			m_column = 0;
			m_row++;
		} else {
			FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_ADDRESS, m_column + m_row * 128);
			FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_VALUE, text.c_str()[i]);
			if (m_colorChanged){
				FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_COLOR, m_color);
				m_colorChanged = false;
			}
			m_column++;
		}
	}
}

void Menu::TextManager::printLine(std::string text) {
	print(text);
	m_column = 0;
	m_row++;
}

void Menu::TextManager::clearAll() {
	uint16_t i;
	m_column = 0;
	m_row = 0;
	for (i = 0; i < 128 * 32; ++i) {
		FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_ADDRESS, i + m_row * 128);
		FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_VALUE, 0x0);
		FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_COLOR, m_color);
	}
}

void TextManager::setColor(uint16_t color) {
	m_color = color;
	m_colorChanged = true;
}

void Menu::TextManager::clearLine() {
	uint8_t i;
	m_column = 0;
	for (i = 0; i < 128; ++i) {
		FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_ADDRESS, i + m_row * 128);
		FPGA::getInstance()->setRegister(FPGA_REGISTER_TEXT_VALUE, 0x0);
	}
}

void Menu::TextManager::setLine(uint8_t line) {
	m_row = line;
}

void TextManager::setColumn(uint8_t column) {
	m_column = column;
}

std::string TextManager::to_string(int16_t number, bool hex) {
	std::string buffer;
	bool negative = number < 0;
	uint8_t firstNumber;

	if (number < 0)
		number *= -1;

	do {
		if (hex){
			firstNumber = number % 16;
			number -= firstNumber;
			number /= 16;
		} else {
			firstNumber = number % 10;
			number -= firstNumber;
			number /= 10;
		}
		switch(firstNumber){
		case 1:
			buffer = "1" + buffer;
			break;
		case 2:
			buffer = "2" + buffer;
			break;
		case 3:
			buffer = "3" + buffer;
			break;
		case 4:
			buffer = "4" + buffer;
			break;
		case 5:
			buffer = "5" + buffer;
			break;
		case 6:
			buffer = "6" + buffer;
			break;
		case 7:
			buffer = "7" + buffer;
			break;
		case 8:
			buffer = "8" + buffer;
			break;
		case 9:
			buffer = "9" + buffer;
			break;
		case 0xA:
			buffer = "A" + buffer;
			break;
		case 0xB:
			buffer = "B" + buffer;
			break;
		case 0xC:
			buffer = "C" + buffer;
			break;
		case 0xD:
			buffer = "D" + buffer;
			break;
		case 0xE:
			buffer = "E" + buffer;
			break;
		case 0xF:
			buffer = "F" + buffer;
			break;
		case 0:
		default:
			buffer = "0" + buffer;
			break;
		}
	} while (number > 0);

	if (negative)
		buffer = "-" + buffer;
	return buffer;
}

} /* namespace Menu */

