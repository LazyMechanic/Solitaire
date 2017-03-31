#pragma once
#include <SFML\Graphics.hpp>

#include "input.h"

class Rules
{
public:
	Rules();
	void Init(sf::RenderWindow& window, sf::Sprite& background, const sf::Texture& buttons);
	void Run();
private:
	void Update();
	void Draw();
	void LightButtons();

	sf::RenderWindow* m_window;
	sf::Sprite* m_background;

	sf::Sprite m_buttonBack;
	sf::Text m_rulesText;
	sf::Font m_rulesFont;

	sf::RectangleShape m_whiteRect;

	sf::Texture m_rulesTextTexture;

	bool m_back;
};