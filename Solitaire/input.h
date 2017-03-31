#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Game;

class Input
{
public:
	static void Init(Game* game);
	static void Update();

	static bool IsKeyPressed(sf::Keyboard::Key key);
	static bool IsKeyReleased(sf::Keyboard::Key key);
	static bool IsKeyDown(sf::Keyboard::Key key);

	static bool IsMouseButtonPressed(sf::Mouse::Button button);
	static bool IsMouseButtonReleased(sf::Mouse::Button button);
	static sf::Vector2i GetMousePosition();

private:
	static Game* m_game;

	static std::vector<bool> m_previousKeyStates;
	static std::vector<bool> m_currentKeyStates;

	static std::vector<bool> m_prevMouseKeyStates;
	static std::vector<bool> m_currentMouseKeyStates;

	static sf::Vector2i m_mousePosition;
};