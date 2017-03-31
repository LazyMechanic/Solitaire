#include <iostream>

#include "card.h"

Card::Card(const sf::Image& cardsImage, int suit, int rating) :
	m_suit(suit), m_rating(rating), m_idHandled(false)
{
	if (!m_texture.loadFromImage(cardsImage, sf::IntRect(71 * rating, 96 * suit, 71, 96))) {
		throw std::runtime_error("Can't load texture from image");
	}

	m_sprite.setTexture(m_texture, true);
}

void Card::Draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Card::Draw(sf::RenderWindow & window, const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
	Draw(window);
}

void Card::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void Card::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
	if (m_sprite.getGlobalBounds().top != y) {
		std::cout << m_sprite.getGlobalBounds().top << "\n";
	}
}
