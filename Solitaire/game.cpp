#include <iostream>

#include "game.h"

short Game::g_gameCondition = Condition::Nothing;

Game::~Game()
{
}

bool Game::Init()
{
	// Check files
	if (!m_cardsImage.loadFromFile("data/cards.png") || !m_backgroundImage.loadFromFile("data/background.png") || !m_windowIcon.loadFromFile("data/ico.png") || !Timer::SetTimerText() || !EndGame::Init(m_backgroundImage) || !Config::Init()) {
		return false;
	}

	// Create window
	m_window.create(sf::VideoMode(800, 600), "Solitaire", sf::Style::Titlebar | sf::Style::Close);
	m_window.setIcon(32, 32, m_windowIcon.getPixelsPtr());
	m_window.setVerticalSyncEnabled(true);

	// Init gaming table, his constans and Input
	Input::Init(this);
	m_gamingTable.Init(m_cardsImage, m_backgroundImage, m_window);
	m_gamingTable.InitOffset(m_window.getSize());

	return true;
}

void Game::Run()
{
	sf::Clock timer;
	while (m_window.isOpen() && Game::g_gameCondition == Condition::Nothing && Timer::GetCurrentTime() > 0) {
		auto dt = timer.restart();
		// Update scene
		Input::Update();
		Timer::Update(dt.asMilliseconds() > 100 ? 100 : dt.asMilliseconds());

		m_gamingTable.Update(dt.asSeconds());
		m_window.clear(sf::Color(0, 128, 0));
		// Draw scene
		m_gamingTable.Draw(m_window);
		// Display scene
		m_window.display();
	}
	// Check loss time
	if (Timer::GetCurrentTime() < 1) {
		Game::g_gameCondition = Condition::Lose;
		Config::Update(-300);
	}

	// Draw last scene - end game
	EndGame::Draw(m_window, Game::g_gameCondition);
	// closing waiting
	while (m_window.isOpen()) Input::Update();
	// Save score
	Config::Save();
}
