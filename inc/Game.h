/*
 * Game.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

#include <GameControllers/PlayerController.h>
#include <Menu/MenuViewer.h>
#include <Menu/MenuItem.h>

namespace GameEngine {
	class Engine;
}
namespace GameControllers {
	class GameController;
}

class Game {
public:
										Game();
	virtual 							~Game();

public:
	void								tick();
	void								wait(uint32_t time);
	void								setGameController(GameControllers::GameController *controller);
	void								setEngine(GameEngine::Engine *engine);
	void								openMainMenu();

	void								pause();
	void								resume();

public:
	static Game							*getInstance();
	GameEngine::Engine					*getEngine();
	GameControllers::PlayerController	*getPlayer(uint8_t player);
	GameControllers::GameController		*getCurrentController();


private:
	static Game							sInstance;
	GameEngine::Engine					*m_engine;
	GameControllers::PlayerController 	m_player1, m_player2;
	GameControllers::GameController		*m_currentController;

	Menu::MenuItem						m_mainMenu, m_pauseMenu;
	Menu::MenuViewer					m_MenuViewer;


private:
	void 								createMenu();
	void 								createMainMenu();
	void 								CreatePauseMenu();
	void 								addSettings(Menu::MenuItem* menu);
};

#endif /* INC_GAME_H_ */
