#pragma once
#include <SFML\Graphics.hpp>

#include "input.h"
#include "gaming_table.h"
#include "config.h"
#include "timer.h"
#include "end_game.h"

class Game
{
public:
	~Game();

	bool Init();
	void Run();

	enum Condition {
		Nothing = 0,
		Win		= 1,
		Lose	= 2
	};

	static short g_gameCondition;

	sf::RenderWindow m_window;
private:
	sf::Image m_cardsImage;
	sf::Image m_backgroundImage;
	sf::Image m_windowIcon;

	GamingTable m_gamingTable;
};