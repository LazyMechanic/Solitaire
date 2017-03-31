#pragma once
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>

class Config
{
public:
	static void Save();
	static void Update(long u_score);

	static bool Init();
	static void DrawConfigText(sf::RenderWindow& window);

	static std::string playerName;
	static long playerScore;
private:
	static sf::Font m_configFont;
	static sf::Text m_configText;
};