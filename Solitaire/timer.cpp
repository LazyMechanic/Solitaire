#include "timer.h"
#include <string>
#include <iostream>

unsigned long Timer::m_constTime = 0;
long Timer::m_time = 0;
bool Timer::m_isRunning = true;
sf::Font Timer::m_timerFont = sf::Font();
sf::Text Timer::m_timerText = sf::Text();

void Timer::SetTimer(unsigned long time)
{
	m_time = time;
}

void Timer::SetConstTimer(unsigned long cTime)
{
	m_constTime = cTime;
}

void Timer::Update(const long dt)
{
	if (m_isRunning) {
		m_time -= dt;
	}
}

void Timer::SetRunning(bool isRunning)
{
	m_isRunning = isRunning;
}

bool Timer::SetTimerText()
{
	if (!m_timerFont.loadFromFile("data/font.ttf")) return false;
	return true;
}

sf::Text Timer::GetTimerText()
{
	std::string m_text = "Timer (sec):\t\t" + std::to_string(m_time / 1000);
	m_timerText.setPosition(sf::Vector2f(640, 580));
	m_timerText.setFont(m_timerFont);
	m_timerText.setCharacterSize(16);
	m_timerText.setString(m_text);
	m_timerText.setColor(sf::Color(sf::Color(1, 1, 1, 255)));

	return m_timerText;
}