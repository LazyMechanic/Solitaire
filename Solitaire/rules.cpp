#include "rules.h"
#include "game.h"

#include <iostream>

Rules::Rules()
{
}

void Rules::Init(sf::RenderWindow & window, sf::Sprite& background, const sf::Texture& buttons)
{
	m_window = &window;
	m_background = &background;

	m_whiteRect.setSize(sf::Vector2f(700, 550));
	m_whiteRect.setPosition(sf::Vector2f(80, 25));
	m_whiteRect.setFillColor(sf::Color(255, 255, 255, 255));
	m_whiteRect.setOutlineThickness(3.0f);
	m_whiteRect.setOutlineColor(sf::Color(178, 178, 178, 255));

	m_buttonBack = sf::Sprite(buttons, sf::IntRect(0, 120, 50, 50));
	m_buttonBack.setPosition(sf::Vector2f(14, 22));

	if (!m_rulesFont.loadFromFile("data/font.ttf")) {
		throw std::runtime_error("Unable to load font");
	}

	m_rulesText.setPosition(sf::Vector2f(95, 40));
	m_rulesText.setFont(m_rulesFont);
	m_rulesText.setCharacterSize(16);
	m_rulesText.setString(L"��� ����� ���������� ������ ���� � �������� �� ��� ����� ��� �� ����� � �������\n�����������, �� ������ �� ������.\n������ ������� �� 52 ����.\n��� ������ �������������� �� 8 ������ �� ����� ����.\n���������� ������ ����� �������� � �������������� ���.\n������ ��������� ����� ��� \"����\" - ������ ������, ���� ����� ���������� ���� �\n ��������� �����, ����� ��������.\n� ����� � ����� - ��� ������ ��������� ������, �� ���� ����� ��� ������� ����.\n���� ������ �� ����� �����, �� ����, ��� �� ����� ������� �����.\n��� ����� ������� ����� � �������� ������� :\n-����� ����� ������ �������� ����� � ����� ������;\n-����� ����� ������ �� ������� ������ ������� �����\n   (������ ������ �� ������� ������ � ��� �����);\n-����� ����� ������ �� ���� �� \"��������� �����\" ������ ����� � �����.\n  � ����� ������ ����� ������ ������ ���� �����;\n-����� ����� ����� �������� � ������ �������, ���� �� ��������� ������,\n ��� �����������.\n  ������ ������ �� �� ����� ����������� �� ������� ��������, �� ���� �������\n  ����� � �� ��������.\n- ����� ����� ������ � \"���\", ������� � ���� � ���������� �������, ��� �� ����� �\n  �� �����������.\n  �� ��� ����� �������� ������, �� ������ - ������ � ��� �� ��������� �����,\n  ���� �� ����� ������ ������� ������ � ������������ �������.");
	m_rulesText.setColor(sf::Color(1, 1, 1, 255));
}

void Rules::Run()
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

void Rules::Update()
{
	LightButtons();
}

void Rules::LightButtons()
{
	static sf::Sprite* hoveredButton = nullptr;

	if (hoveredButton) {
		hoveredButton->setColor(sf::Color::White);
	}

	hoveredButton = nullptr;

	if (m_buttonBack.getGlobalBounds().contains(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
		hoveredButton = &m_buttonBack;
	}

	if (hoveredButton) {
		hoveredButton->setColor(sf::Color(200, 200, 200, 255));

		if (Input::IsMouseButtonPressed(sf::Mouse::Left)) {
			m_back = true;
		}
	}
}

void Rules::Draw()
{
	m_window->draw(*m_background);
	m_window->draw(m_whiteRect);
	m_window->draw(m_buttonBack);
	m_window->draw(m_rulesText);
}
