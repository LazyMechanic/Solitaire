#include "end_game.h"

sf::Font EndGame::m_endFont;
sf::Text EndGame::m_endText;
sf::Text EndGame::m_scoreText;
sf::Sprite EndGame::m_background;
sf::Texture EndGame::m_backgroundTexture;

bool EndGame::Init(const sf::Image& backgroundImage)
{
	if (!m_endFont.loadFromFile("data/font.ttf")) return false;


	m_backgroundTexture.loadFromImage(backgroundImage);
	m_background.setTexture(m_backgroundTexture, true);

	m_endText.setFont(m_endFont);
	m_endText.setPosition(sf::Vector2f(229, 225));
	m_endText.setCharacterSize(45);
	m_endText.setColor(sf::Color::White);
	m_endText.setStyle(sf::Text::Bold);

	m_scoreText.setFont(m_endFont);
	m_scoreText.setPosition(sf::Vector2f(229, 280));
	m_scoreText.setCharacterSize(20);
	m_scoreText.setColor(sf::Color::White);
	m_scoreText.setStyle(sf::Text::Bold);

	return true;
}

void EndGame::Draw(sf::RenderWindow & window, short victoryCondition)
{
	if (victoryCondition == 1) {
		m_endText.setString(L"¬€ ¬€»√–¿À»!");
		m_scoreText.setString(L"—◊≈“: ");
		window.clear();
		window.draw(m_background);
		window.draw(m_scoreText);
		m_scoreText.setString(std::to_string(Config::playerScore));
		m_scoreText.setPosition(sf::Vector2f(300, 280));
		window.draw(m_scoreText);
		window.draw(m_endText);
		window.display();
	}
	else {
		m_endText.setString(L"¬€ œ–Œ»√–¿À»!");
		m_scoreText.setString(L"—◊≈“: ");
		window.clear();
		window.draw(m_background);
		window.draw(m_scoreText);
		m_scoreText.setString(std::to_string(Config::playerScore));
		m_scoreText.setPosition(sf::Vector2f(300, 280));
		window.draw(m_scoreText);
		window.draw(m_endText);
		window.display();
	}
}
