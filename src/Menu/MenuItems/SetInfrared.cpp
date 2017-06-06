/*
 * SetInfrared.cpp
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/SetInfrared.h>
#include <Menu/MenuBox.h>
#include <FPGA.h>

namespace Menu {
namespace MenuItems {

SetInfrared::SetInfrared(MenuItem * parent)
	: MenuItem(
			(FPGA::getInstance()->getOptions() & FPGA_OPTION_INFRARED_MODE) == FPGA_OPTION_INFRARED_MODE ? "Infrared: ON" : "Infrared: OFF",
			parent
	)
{
}

SetInfrared::~SetInfrared() {
}

void SetInfrared::select() {
	FPGA::getInstance()->setOption(FPGA::getInstance()->getOptions() ^ FPGA_OPTION_INFRARED_MODE);
	setTitle((FPGA::getInstance()->getOptions() & FPGA_OPTION_INFRARED_MODE) == FPGA_OPTION_INFRARED_MODE ? "Infrared: ON" : "Infrared: OFF");
	Menu::MenuBox::getInstance()->show(getParent());
}

} /* namespace MenuItems */
} /* namespace Menu */
