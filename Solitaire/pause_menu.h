#pragma once
#include <SFML\Graphics.hpp>

#include "input.h"
#include "rules.h"

class PauseMenu
{
public:
	PauseMenu();
	void Init(sf::RenderWindow & window, sf::Sprite& background);
	void Run();
	void Update();
	void Draw();
private:
	sf::Texture m_buttonMenuTexture;
	std::vector<sf::Sprite> m_buttonsMenu;

	sf::RenderWindow* m_window;
	sf::Sprite* m_background;

	Rules m_rules;

	void LightButtons();
	void OnButtonPressed(sf::Sprite* button, int placeId);

	float m_buttonsTopOffset;
	float m_buttonsLeftOffset;
	float m_buttonsOffset;

	bool m_back;
};