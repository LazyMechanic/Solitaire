#pragma once
#include <SFML/Graphics.hpp>

class Timer
{
public:
	static void SetTimer(unsigned long time);
	static void SetConstTimer(unsigned long cTime);
	static unsigned long GetConstTimer() { return m_constTime; };

	static void Update(const long dt);
	static void SetRunning(bool isRunning);
	static bool m_isRunning;
	static unsigned int GetCurrentTime() { return m_time / 1000; }

	static bool SetTimerText();
	static sf::Text GetTimerText();
private:
	static long m_time;
	static unsigned long m_constTime;

	static sf::Font m_timerFont;
	static sf::Text m_timerText;
};