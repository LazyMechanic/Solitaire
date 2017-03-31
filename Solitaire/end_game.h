#pragma once
#include <SFML\Graphics.hpp>

#include "config.h"

class EndGame
{
public:
	static bool Init(const sf::Image& backgroundImage);
	static void Draw(sf::RenderWindow& window, short victoryCondition);
private:
	static sf::Font m_endFont;
	static sf::Text m_endText;
	static sf::Text m_scoreText;
	static sf::Sprite m_background;
	static sf::Texture m_backgroundTexture;
};