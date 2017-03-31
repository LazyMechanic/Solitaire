#pragma once

#include <memory>
#include <vector>

#include "card.h"
#include "input.h"
#include "pause_menu.h"
#include "timer.h"
#include "config.h"

class GamingTable
{
public:
	GamingTable();
	~GamingTable();

	void Init(const sf::Image& cardsImage, const sf::Image& backgroundImage, sf::RenderWindow & window);
	void ReInit();

	void InitOffset(const sf::Vector2u& windowSize);

	void LightHoveredCard();
	void OnCardPressed(Card* card);

	void Update(const float& dt);

	void Draw(sf::RenderWindow& window);
private:
	std::vector<std::unique_ptr<Card>> m_cards;

	std::vector<std::vector<Card*>> m_mainColumns;
	std::vector<std::vector<Card*>> m_winColumns;
	std::vector<std::vector<Card*>> m_bufferAreas;

	float m_mainColumnsTopOffset;
	float m_mainColumnsLeftOffset;
	float m_mainColumnsCardOffset;
	float m_winColumnsLeftOffset;

	sf::Texture m_buttonResetTexture;
	sf::Sprite m_buttonReset;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;

	std::vector<Card*> m_handledCards;

	PauseMenu m_pMenu;

	sf::RectangleShape m_footer;

	sf::Image m_cardsImage;
};