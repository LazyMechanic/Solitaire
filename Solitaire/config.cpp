#include "config.h"

#include <map>

std::string Config::playerName;
long Config::playerScore;
sf::Font Config::m_configFont;
sf::Text Config::m_configText;

void Config::Save()
{
	std::fstream file;
	file.open("cash.ini", std::fstream::in);

	std::map<std::string, int> records;

	std::string tokenName, tokenScore;
	while (file >> tokenName >> tokenScore) {
		records[tokenName] = std::atoi(tokenScore.c_str());
	}

	records[playerName] = playerScore;

	file.close();
	file.open("cash.ini", std::fstream::out | std::fstream::trunc);
	for (auto& record : records) {
		file << record.first << " " << record.second << "\n";
	}
	file.close();
}

void Config::Update(long u_score)
{
	if (playerScore + u_score < 0) playerScore = 0;
	else playerScore += u_score;
}

bool Config::Init()
{
	if (!m_configFont.loadFromFile("data/font.ttf")) return false;

	m_configText.setFont(m_configFont);
	m_configText.setCharacterSize(16);
	m_configText.setColor(sf::Color(sf::Color(1, 1, 1, 255)));

	return true;
}

void Config::DrawConfigText(sf::RenderWindow& window)
{
	std::string config = "Name:\t\t" + playerName;
	m_configText.setString(config);
	m_configText.setPosition(sf::Vector2f(20, 580));
	window.draw(m_configText);

	config = "Score:\t\t" + std::to_string(playerScore);
	m_configText.setString(config);
	m_configText.setPosition(sf::Vector2f(353, 580));
	window.draw(m_configText);
}
