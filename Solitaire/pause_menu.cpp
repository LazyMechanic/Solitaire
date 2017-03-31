#include "pause_menu.h"
#include "timer.h"
#include "game.h"

#include <iostream>
PauseMenu::PauseMenu()
{
}

void PauseMenu::Init(sf::RenderWindow& window, sf::Sprite& background)
{
	m_window = &window;
	m_background = &background;

	m_buttonsOffset = 10.0f;
	m_buttonsLeftOffset = 300.0f;
	m_buttonsTopOffset = 225.0f;

	if (!m_buttonMenuTexture.loadFromFile("data/menubuttons.png")) {
		throw std::runtime_error("Unable to load buttonds textures");
	}

	for (int i = 0; i < 3; i++) {
		m_buttonsMenu.push_back(sf::Sprite(m_buttonMenuTexture, sf::IntRect(0, 40 * i, 200, 40)));
	}

	m_rules.Init(window, background, m_buttonMenuTexture);
}

void PauseMenu::Run()
{
	m_back = false;
	while (m_window->isOpen() && !m_back)
	{
		Input::Update();
		Update();
		m_window->clear();
		Draw();
		m_window->display();
	}
}

void PauseMenu::Update()
{
	LightButtons();
}

void PauseMenu::Draw()
{
	m_window->draw(*m_background);

	for (int i = 0; i < 3; i++) {
		m_buttonsMenu[i].setPosition(sf::Vector2f(m_buttonsLeftOffset, m_buttonsTopOffset + 40 * i + m_buttonsOffset * i));
		m_window->draw(m_buttonsMenu[i]);
	}
}

void PauseMenu::LightButtons()
{
	static sf::Sprite* hoveredButton = nullptr;

	if (hoveredButton) {
		hoveredButton->setColor(sf::Color::White);
	}

	hoveredButton = nullptr;
	int placeId = -1;

	for (int i = 0; i < m_buttonsMenu.size(); ++i) {
		if (m_buttonsMenu[i].getGlobalBounds().contains(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			hoveredButton = &m_buttonsMenu[i];
			placeId = i;
		}
		if (hoveredButton) {
			break;
		}
	}

	if (hoveredButton) {
		hoveredButton->setColor(sf::Color(200, 200, 200, 255));

		if (Input::IsMouseButtonPressed(sf::Mouse::Left)) {
			OnButtonPressed(hoveredButton, placeId);
		}
	}
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape)) {
		Timer::SetRunning(true);
		m_back = true;
	}
}

void PauseMenu::OnButtonPressed(sf::Sprite * button, int placeId)
{
	switch (placeId)
	{
	case 0:
		m_back = true;
		Timer::SetRunning(true);
		break;
	case 1:
		m_rules.Run();
		break;
	case 2:
		m_window->close();
		break;
	}
}
