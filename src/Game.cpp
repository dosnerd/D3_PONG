/*
 * Game.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#include <Game.h>
#include <config_file.h>
#include <FPGA.h>
#include <UART.h>

#include <gameEngine/Engine.h>

#include <GameControllers/Demo.h>
#include <GameControllers/GameController.h>

#include <Menu/MenuBox.h>
#include <Menu/MenuItem.h>
#include <Menu/MenuItems/StartDemo.h>
#include <Menu/MenuItems/StartTennis.h>
#include <Menu/MenuItems/StartHandball.h>
#include <Menu/MenuItems/PlayerColorSelect.h>
#include <Menu/MenuItems/OpenMainMenu.h>
#include <Menu/MenuItems/ResumeGame.h>
#include <Menu/MenuItems/SetInfrared.h>

Game Game::sInstance;
Game::Game()
	: m_engine(new GameEngine::Engine())
	, m_player1(UART::getInstance())
	, m_player2(UART::getInstance())
	, m_currentController(new GameControllers::Demo(m_engine->getBall(), &m_player1, &m_player2))
	, m_mainMenu("Main Menu")
	, m_pauseMenu("Pause")
	, m_MenuViewer(Menu::MenuBox::getInstance())
{
	FPGA::getInstance()->turnOn();
	createMenu();

	m_player1.setColor(COLOR_PLAYER1);
	m_player2.setColor(COLOR_PLAYER2);

	m_currentController->bind(FPGA::getInstance());
	m_currentController->setupField(m_engine);

	wait(0xFF); //wait everthing is table

	FPGA::getInstance()->setRegister(FPGA_REGISTER_COLOR_PLAYER1, m_player1.getColor());
	FPGA::getInstance()->setRegister(FPGA_REGISTER_COLOR_PLAYER2, m_player2.getColor());
}

Game::~Game() {
	delete m_currentController;
	delete m_engine;
}

Game* Game::getInstance() {
	return &sInstance;
}

void Game::setGameController(GameControllers::GameController* controller) {
	delete m_currentController;
	m_currentController = controller;
}

GameEngine::Engine* Game::getEngine() {
	return m_engine;
}

GameControllers::PlayerController* Game::getPlayer(uint8_t player) {
	if (player == 1)
		return &m_player1;
	else
		return &m_player2;
}

void Game::setEngine(GameEngine::Engine* engine) {
	delete m_engine;
	m_engine = engine;
}

void Game::openMainMenu() {
	setEngine(new GameEngine::Engine());
	GameControllers::Demo *demo = new GameControllers::Demo(m_engine->getBall(), getPlayer(1), getPlayer(2));
	setGameController(demo);

	demo->bind(FPGA::getInstance());
	demo->setupField(m_engine);
	Menu::MenuBox::getInstance()->show(&m_mainMenu);
}

void Game::pause() {
	m_currentController->pause();
	Menu::MenuBox::getInstance()->show(&m_pauseMenu);
}

void Game::resume() {
	Menu::MenuBox::getInstance()->hide();
	m_currentController->play();
	FPGA::getInstance()->update(FPGA_UPDATE_ALL);
}

void Game::addSettings(Menu::MenuItem* menu) {
	Menu::MenuItem* settings = new Menu::MenuItem("Settings", menu);

	Menu::MenuItem* colorPlayer1 = new Menu::MenuItem("Color player 1",settings);
	colorPlayer1->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer1, 1, 0x00F));
	colorPlayer1->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer1, 1, 0x0FF));
	colorPlayer1->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer1, 1, 0x0F0));
	colorPlayer1->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer1, 1, 0xFF0));
	colorPlayer1->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer1, 1, 0xF00));
	colorPlayer1->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer1, 1, 0xFFF));
	colorPlayer1->addChild(new Menu::MenuItem("Cancel", colorPlayer1));

	Menu::MenuItem* colorPlayer2 = new Menu::MenuItem("Color player 2",settings);
	colorPlayer2->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer2, 2, 0x00F));
	colorPlayer2->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer2, 2, 0x0FF));
	colorPlayer2->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer2, 2, 0x0F0));
	colorPlayer2->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer2, 2, 0xFF0));
	colorPlayer2->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer2, 2, 0xF00));
	colorPlayer2->addChild(new Menu::MenuItems::PlayerColorSelect(colorPlayer2, 2, 0xFFF));
	colorPlayer2->addChild(new Menu::MenuItem("Cancel", colorPlayer1));

	settings->addChild(colorPlayer1);
	settings->addChild(colorPlayer2);
	settings->addChild(new Menu::MenuItems::SetInfrared(settings));
	settings->addChild(new Menu::MenuItem("Cancel", settings));

	menu->addChild(settings);
}

void Game::createMainMenu() {
	Menu::MenuItem* startGame = new Menu::MenuItem("Start Game", &m_mainMenu);
	startGame->addChild(new Menu::MenuItems::StartDemo(startGame));
	startGame->addChild(new Menu::MenuItems::StartTennis(startGame));
	startGame->addChild(new Menu::MenuItem("Hockey", startGame));
	startGame->addChild(new Menu::MenuItems::StartHandball(startGame));

	m_mainMenu.addChild(startGame);
	addSettings(&m_mainMenu);
}

void Game::CreatePauseMenu() {
	Menu::MenuItem* menuMainMenu = new Menu::MenuItems::OpenMainMenu(&m_pauseMenu);
	Menu::MenuItem* menuContinue = new Menu::MenuItems::ResumeGame(&m_pauseMenu);

	m_pauseMenu.addChild(menuContinue);
	addSettings(&m_pauseMenu);
	m_pauseMenu.addChild(menuMainMenu);
}

void Game::createMenu() {
	createMainMenu();
	CreatePauseMenu();
}

void Game::tick() {
	m_engine->moveBall();
	MVC::Observer::handleNotifications();
	m_MenuViewer.animate();//for animations
}

void Game::wait(uint32_t time) {
	while(time--) {
		asm volatile ("nop");
	}
}

GameControllers::GameController* Game::getCurrentController() {
	return m_currentController;
}
