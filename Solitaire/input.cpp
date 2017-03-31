#include "input.h"
#include "game.h"

Game* Input::m_game = nullptr;

std::vector<bool> Input::m_previousKeyStates;
std::vector<bool> Input::m_currentKeyStates;
std::vector<bool> Input::m_prevMouseKeyStates;
std::vector<bool> Input::m_currentMouseKeyStates;
sf::Vector2i Input::m_mousePosition;

void Input::Init(Game * game)
{
	m_game = game;
	m_previousKeyStates.assign(sf::Keyboard::KeyCount, false);
	m_currentKeyStates.assign(sf::Keyboard::KeyCount, false);
	m_prevMouseKeyStates.assign(sf::Mouse::Button::ButtonCount, false);
	m_currentMouseKeyStates.assign(sf::Mouse::Button::ButtonCount, false);
}

bool Input::IsKeyPressed(sf::Keyboard::Key key)
{
	return m_currentKeyStates[key] && !m_previousKeyStates[key];
}

bool Input::IsKeyReleased(sf::Keyboard::Key key)
{
	return !m_currentKeyStates[key] && m_previousKeyStates[key];
}

bool Input::IsKeyDown(sf::Keyboard::Key key)
{
	return m_currentKeyStates[key];
}


bool Input::IsMouseButtonPressed(sf::Mouse::Button button)
{
	return m_currentMouseKeyStates[button] && !m_prevMouseKeyStates[button];
}

bool Input::IsMouseButtonReleased(sf::Mouse::Button button)
{
	return !m_currentMouseKeyStates[button] && m_prevMouseKeyStates[button];
}


sf::Vector2i Input::GetMousePosition()
{
	return m_mousePosition;
}

void Input::Update()
{
	m_previousKeyStates = m_currentKeyStates;
	m_prevMouseKeyStates = m_currentMouseKeyStates;

	sf::Event m_event;
	while (m_game->m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::KeyPressed:
			if (m_event.key.code > -1)
			m_currentKeyStates[m_event.key.code] = true;
			break;
		case sf::Event::KeyReleased:
			if (m_event.key.code > -1)
			m_currentKeyStates[m_event.key.code] = false;
			break;
		case sf::Event::MouseButtonPressed:
			m_currentMouseKeyStates[m_event.mouseButton.button] = true;
			break;
		case sf::Event::MouseButtonReleased:
			m_currentMouseKeyStates[m_event.mouseButton.button] = false;
			break;
		case sf::Event::MouseMoved:
			m_mousePosition = sf::Vector2i(m_event.mouseMove.x, m_event.mouseMove.y);
			break;
		case sf::Event::Closed:
			m_game->m_window.close();
			break;
		}
	}
}

