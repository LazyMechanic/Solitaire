#pragma once

#include <SFML\Graphics.hpp>

class Card
{
public:
	enum Suit
	{
		Clubs,
		Diamonds,
		Spades,
		Hearts,

		Stuff
	};

	enum Rating
	{
		Ace,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,

		Empty
	};

	Card(const sf::Image& cardsImage, int suit, int rating);

	void Draw(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window, const sf::Vector2f& position); // changes position and renders sprite on this position

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& position);

	void SetHandled(bool handled) { m_idHandled = handled; }
	bool IsHandled() const { return m_idHandled; }

	sf::FloatRect GetBounds() const { return m_sprite.getGlobalBounds(); }
	sf::Vector2f GetPosition() const { return m_sprite.getPosition(); }
	
	int GetSuit() const { return m_suit; }
	int GetRating() const { return m_rating; }

	sf::Sprite& GetSprite() { return m_sprite; }

	void SetPlaceId(int placeId) { m_placeId = placeId; }
	int GetPlaceId() const { return m_placeId; }

	void SetColumnId(int columnId) { m_columnId = columnId; }
	int GetColumnId() const { return m_columnId; }
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int m_suit;
	int m_rating;

	int m_columnId;
	int m_placeId;

	bool m_idHandled;
};