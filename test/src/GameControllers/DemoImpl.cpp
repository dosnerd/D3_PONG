/*
 * DemoImpl.cpp
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#include <GameControllers/DemoImpl.h>
#include <iostream>
#include <Game.h>

namespace GameControllers {

DemoImpl::DemoImpl(GameEngine::Ball *ball)
	: Demo(ball, Game::getInstance()->getPlayer(1), Game::getInstance()->getPlayer(2))
{

}

DemoImpl::~DemoImpl() {
}

void DemoImpl::winMatch(uint8_t player) {
	m_stats.add(player);
}

Vector<uint8_t>& DemoImpl::getStats() {
	return m_stats;
}

} /* namespace GameControllers */
