#include <iostream>

#include "gaming_table.h"
#include "game.h"

GamingTable::GamingTable()
{
}

GamingTable::~GamingTable()
{
}

void GamingTable::Init(const sf::Image& cardsImage, const sf::Image& backgroundImage, sf::RenderWindow & window)
{
	// Set new timer
	Timer::SetTimer(Timer::GetConstTimer());

	m_footer.setSize(sf::Vector2f(800, 20));
	m_footer.setPosition(sf::Vector2f(0, 580));
	m_footer.setFillColor(sf::Color(220, 220, 220, 255));

	// Set background sprite
	m_backgroundTexture.loadFromImage(backgroundImage);
	m_background.setTexture(m_backgroundTexture);

	// Init pause menu
	m_pMenu.Init(window, m_background);

	// Set button reset sprite
	m_cardsImage = cardsImage;
	m_buttonResetTexture.loadFromImage(m_cardsImage, sf::IntRect(923, 288, 29, 27));
	m_buttonReset.setTexture(m_buttonResetTexture, true);
	m_buttonReset.scale(2.0f, 2.0f);

	// Create cards deck
	for (int i = 0; i < 4; i++) {
		m_cards.push_back(std::make_unique<Card>(m_cardsImage, 0, 13)); // Flower
	}
	for (int i = 0; i < 4; i++) {
		m_cards.push_back(std::make_unique<Card>(m_cardsImage, 1, 13)); // Crown
	}
	for (int i = 0; i < 8; i++) {
		m_cards.push_back(std::make_unique<Card>(m_cardsImage, 2, 13)); // Empty
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			m_cards.push_back(std::make_unique<Card>(m_cardsImage, i, j));
		}
	}

	/*
	* [ first mainCol card, ..x6.., last mainCol card,
	* first buffer card, ..x2.., last buffer card,
	* first win card, ..x2.., last win card,
	* first card, ..x50.., last card ]
	*/

	// Shuffle deck

	std::random_shuffle(m_cards.begin() + 16, m_cards.end());

	/// Fill columns and areas

	// Fill buffer areas and win columns
	for (int i = 0; i < 4; i++)
	{
		m_bufferAreas.push_back(std::vector<Card*>());
		m_bufferAreas[i].push_back(m_cards[i].get());
		m_bufferAreas[i].back()->SetColumnId(8 + i);
		m_bufferAreas[i].back()->SetPlaceId(0);

		m_winColumns.push_back(std::vector<Card*>());
		m_winColumns[i].push_back(m_cards[4 + i].get());
		m_winColumns[i].back()->SetColumnId(12 + i);
		m_winColumns[i].back()->SetPlaceId(0);
	}

	/*
	// First 4 columns 
	for (int i = 0; i < 4; i++) {
		m_mainColumns.push_back(std::vector<Card*>());
		m_mainColumns[i].push_back(m_cards[8 + i].get());///
		m_mainColumns[i].back()->SetColumnId(i);///
		m_mainColumns[i].back()->SetPlaceId(0);///
		for (int j = 0; j < 7; j++) {
			m_mainColumns[i].push_back(m_cards[16 + 7 * i + j].get());
			m_mainColumns[i].back()->SetColumnId(i);
			m_mainColumns[i].back()->SetPlaceId(j + 1);
		}
	}

	// Last 4 columns 
	for (int i = 4; i < 8; i++) {
		m_mainColumns.push_back(std::vector<Card*>());
		m_mainColumns[i].push_back(m_cards[8 + i].get());///
		m_mainColumns[i].back()->SetColumnId(i);///
		m_mainColumns[i].back()->SetPlaceId(0);///
		for (int j = 0; j < 6; j++) {
			m_mainColumns[i].push_back(m_cards[16 + 4 + 6 * i + j].get());
			m_mainColumns[i].back()->SetColumnId(i);
			m_mainColumns[i].back()->SetPlaceId(j + 1);
		}
	}
	*/
	
	///*
	///EXPERIMENT
	for (int i = 0; i < 8; i++) {
		m_mainColumns.push_back(std::vector<Card*>());
		m_mainColumns[i].push_back(m_cards[8 + i].get());///
		m_mainColumns[i].back()->SetColumnId(i);///
		m_mainColumns[i].back()->SetPlaceId(0);///
		for (int j = 0; j < 7; j++) {
			if (i < 4) {
				m_mainColumns[i].push_back(m_cards[16 + 7 * i + j].get());
				m_mainColumns[i].back()->SetColumnId(i);
				m_mainColumns[i].back()->SetPlaceId(j + 1);
			}
			else {
				if (j < 6) {
					m_mainColumns[i].push_back(m_cards[16 + 4 + 6 * i + j].get());
					m_mainColumns[i].back()->SetColumnId(i);
					m_mainColumns[i].back()->SetPlaceId(j + 1);
				}
			}
		}
	}
	///
	//*/

	// Sort deck excluding the first 16 cards where are the service cards for correctly drawing
	std::sort(m_cards.begin() + 16, m_cards.end(), [](const std::unique_ptr<Card>& a, const std::unique_ptr<Card>& b) { return a->GetPlaceId() < b->GetPlaceId(); });
}

void GamingTable::ReInit()
{
	// Set new timer
	Timer::SetTimer(Timer::GetConstTimer());
	Timer::SetRunning(true);

	/*
	* [ first mainCol card, ..x6.., last mainCol card,
	* first buffer card, ..x2.., last buffer card,
	* first win card, ..x2.., last win card,
	* first card, ..x50.., last card ]
	*/

	// Shuffle deck
	std::random_shuffle(m_cards.begin() + 16, m_cards.end());

	// Clean handled cards
	std::for_each(m_handledCards.begin(), m_handledCards.end(), [](Card* card) {
		card->GetSprite().setColor(sf::Color::White);
	});
	m_handledCards.clear();

	// Clear all columns and areas
	m_bufferAreas.clear();
	m_winColumns.clear();
	m_mainColumns.clear();

	/// Fill columns and areas

	// Fill buffer areas and win columns
	for (int i = 0; i < 4; i++)
	{
		m_bufferAreas.push_back(std::vector<Card*>());
		m_bufferAreas[i].push_back(m_cards[i].get());
		m_bufferAreas[i].back()->SetColumnId(8 + i);
		m_bufferAreas[i].back()->SetPlaceId(0);

		m_winColumns.push_back(std::vector<Card*>());
		m_winColumns[i].push_back(m_cards[4 + i].get());
		m_winColumns[i].back()->SetColumnId(12 + i);
		m_winColumns[i].back()->SetPlaceId(0);
	}

	// Fill main columns

	///EXPERIMENT
	for (int i = 0; i < 8; i++) {
		m_mainColumns.push_back(std::vector<Card*>());
		m_mainColumns[i].push_back(m_cards[8 + i].get());///
		m_mainColumns[i].back()->SetColumnId(i);///
		m_mainColumns[i].back()->SetPlaceId(0);///
		for (int j = 0; j < 7; j++) {
			if (i < 4) {
				m_mainColumns[i].push_back(m_cards[16 + 7 * i + j].get());
				m_mainColumns[i].back()->SetColumnId(i);
				m_mainColumns[i].back()->SetPlaceId(j + 1);
			}
			else {
				if (j < 6) {
					m_mainColumns[i].push_back(m_cards[16 + 4 + 6 * i + j].get());
					m_mainColumns[i].back()->SetColumnId(i);
					m_mainColumns[i].back()->SetPlaceId(j + 1);
				}
			}
		}
	}
	///

	// Sort deck excluding the first 8 cards where are the service cards for correctly drawing
	std::sort(m_cards.begin() + 16, m_cards.end(), [](const std::unique_ptr<Card>& a, const std::unique_ptr<Card>& b) { return a->GetPlaceId() < b->GetPlaceId(); });
}

void GamingTable::InitOffset(const sf::Vector2u & windowSize)
{
	m_mainColumnsTopOffset = 20.0f + 96.0f + 20.0f;
	m_mainColumnsLeftOffset = (windowSize.x - 8.0f * 71.0f) / 9.0f;
	m_mainColumnsCardOffset = 30.0f;

	m_winColumnsLeftOffset = windowSize.x - 10.0f - (71.0f + 10.0f) * 4.0f;

	m_buttonReset.setPosition(windowSize.x / 2 - 29.0f, 20.0f + 21.0f);
}

void GamingTable::LightHoveredCard()
{
	// Pointer to card under the mouse pointer
	static Card* hoveredCard = nullptr;

	// If previous card been under the mouse pointer
	if (hoveredCard) {
		hoveredCard->GetSprite().setColor(sf::Color::White);
	}

	// Clean pointer
	hoveredCard = nullptr;

	// Set pointer to card on main columns
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < m_mainColumns[i].size(); ++j) {
			if (m_mainColumns[i][j]->GetBounds().contains(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
				hoveredCard = m_mainColumns[i][j];
			}
		}
		if (hoveredCard) {
			break;
		}
	}

	// Set pointer to card on buffer areas
	for (int i = 0; i < 4; i++) {
		if (m_bufferAreas[i].back()->GetBounds().contains(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			hoveredCard = m_bufferAreas[i].back();
		}
		if (hoveredCard) break;
	}

	// Set pointer to card on win columns
	for (int i = 0; i < 4; i++) {
		if (m_winColumns[i].back()->GetBounds().contains(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			hoveredCard = m_winColumns[i].back();
		}
		if (hoveredCard) break;

	}

	// Set color hovered card
	if (hoveredCard) {
		hoveredCard->GetSprite().setColor(sf::Color(200, 200, 200, 255));

		// Selected cards
		if (Input::IsMouseButtonPressed(sf::Mouse::Left)) {
			OnCardPressed(hoveredCard);
		}
	}
	else {
		// Deselect cards
		if (Input::IsMouseButtonPressed(sf::Mouse::Left)) {
			if (m_handledCards.size()) {
				std::for_each(m_handledCards.begin(), m_handledCards.end(), [&](Card* card) {
					card->GetSprite().setColor(sf::Color::White);
				});
				m_handledCards.clear();
			}
		}
	}
}

void GamingTable::OnCardPressed(Card* card)
{
	// If handled card is exist
	if (m_handledCards.size()) {
		// If handled card is in main columns
		if (m_handledCards.back()->GetColumnId() < 8) {

			// If clicked buffer zone, move card there
			if (card->GetColumnId() > 7 && card->GetColumnId() < 12) {
				// check whether buffer area is empty or not
				if (m_bufferAreas[card->GetColumnId() - 8].size() == 1) {
					m_mainColumns[m_handledCards.back()->GetColumnId()].pop_back();

					m_bufferAreas[card->GetColumnId() - 8].push_back(m_handledCards.back());
					m_handledCards.back()->SetColumnId(card->GetColumnId());
					m_handledCards.back()->SetPlaceId(1);
				}
			}
		}

		// If clicked last card in other main column, move card there
		if (card->GetColumnId() < 8 && card->GetPlaceId() == m_mainColumns[card->GetColumnId()].size() - 1 &&
			m_mainColumns[card->GetColumnId()].size() + m_handledCards.size() < 13) {
			if (card->GetSuit() % 2 != m_handledCards.front()->GetSuit() % 2 && card->GetRating() - 1 == m_handledCards.front()->GetRating() ||
				card->GetPlaceId() == 0) {
				for (int i = 0; i < m_handledCards.size(); i++) {
					m_mainColumns[card->GetColumnId()].push_back(m_handledCards[i]);
				}

				if (m_handledCards.front()->GetColumnId() < 8) {
					m_mainColumns[m_handledCards.front()->GetColumnId()].erase(m_mainColumns[m_handledCards.front()->GetColumnId()].begin() + m_handledCards.front()->GetPlaceId(), m_mainColumns[m_handledCards.front()->GetColumnId()].end());
				}
				else {
					m_bufferAreas[m_handledCards.front()->GetColumnId() - 8].pop_back();
				}

				for (int i = 0; i < m_handledCards.size(); i++) {
					m_handledCards[i]->SetColumnId(card->GetColumnId());
					m_handledCards[i]->SetPlaceId(card->GetPlaceId() + 1 + i);
				}

				// Sorting for correctly drawing
				std::sort(m_cards.begin() + 16, m_cards.end(), [](const std::unique_ptr<Card>& a, const std::unique_ptr<Card>& b) { return a->GetPlaceId() < b->GetPlaceId(); });
			}
		}
		// If clicked card places on win columns
		if (card->GetColumnId() > 11) {
			// If size vector on handledCards == 1
			if (m_handledCards.size() == 1) {
				// To check the correctness of sequence
				if ((m_handledCards.front()->GetSuit() == card->GetSuit() && 
					m_handledCards.front()->GetRating() - 1 == card->GetRating()) || 
					(card->GetRating() == 13 && m_handledCards.front()->GetRating() == 0)) {
					m_winColumns[card->GetColumnId() - 12].push_back(m_handledCards.front());
					Config::Update(10);

					// If handledCard places on mainColumns delete it
					if (m_handledCards.front()->GetColumnId() < 8) {
						m_mainColumns[m_handledCards.front()->GetColumnId()].pop_back();
					}
					// If handledCard places on bufferAreas delete it
					else {
						m_bufferAreas[m_handledCards.front()->GetColumnId() - 8].pop_back();
					}

					m_handledCards.front()->SetColumnId(card->GetColumnId());
					m_handledCards.front()->SetPlaceId(card->GetPlaceId() + 1);
					
					// Sorting for correctly drawing
					std::sort(m_cards.begin() + 16, m_cards.end(), [](const std::unique_ptr<Card>& a, const std::unique_ptr<Card>& b) { return a->GetPlaceId() < b->GetPlaceId(); });

					// Check winColumns
					bool win = true;
					for (int i = 0; i < m_winColumns.size(); i++) {
						if (m_winColumns[i].back()->GetRating() != Card::King) {
							win = false;
							break;
						}
					}
					// Check win condition
					if (win) {
						Timer::SetRunning(false);
						Game::g_gameCondition = Game::Condition::Win;
					}
				}
			}
		}
		// Clean handledCards
		std::for_each(m_handledCards.begin(), m_handledCards.end(), [&](Card* card) {
			card->GetSprite().setColor(sf::Color::White);
		});
		m_handledCards.clear();
	}

	// If handled card is no exist
	else {
		// If click on buffer area or win columns
		if (card->GetColumnId() > 7) {
			// If click on empty cell or win columns not light
			if (card->GetColumnId() > 11 || card->GetPlaceId() == 0) {
				std::for_each(m_handledCards.begin(), m_handledCards.end(), [&](Card* card) {
					card->GetSprite().setColor(sf::Color::White);
				});
				m_handledCards.clear();
			}
			// Else push clicked card in handledCards
			else {
				card->GetSprite().setColor(sf::Color(66, 156, 44, 255));
				m_handledCards.push_back(card);
			}
		}
		else {
			// If clicked card places in main columns and column not empty
			if (/*card->GetColumnId() < 8 && useless*/ card->GetPlaceId() > 0) {
				// Checking sequence
				bool checkSequence = true;
				m_handledCards.push_back(card);
				for (int i = card->GetPlaceId() + 1; i < m_mainColumns[card->GetColumnId()].size(); ++i) {
					if (m_mainColumns[card->GetColumnId()][i - 1]->GetSuit() % 2 == m_mainColumns[card->GetColumnId()][i]->GetSuit() % 2 ||
						m_mainColumns[card->GetColumnId()][i - 1]->GetRating() - 1 != m_mainColumns[card->GetColumnId()][i]->GetRating()) {
						checkSequence = false;
						break;
					}
					else {
						m_handledCards.push_back(m_mainColumns[card->GetColumnId()][i]);
					}
				}
				if (!checkSequence) {
					m_handledCards.clear();
				}
			}
			// Else clean handledCards
			else {
				std::for_each(m_handledCards.begin(), m_handledCards.end(), [&](Card* card) {
					card->GetSprite().setColor(sf::Color::White);
				});
				m_handledCards.clear();
			}
		}
	}
}

void GamingTable::Update(const float& dt)
{
	LightHoveredCard();

	// If there is selected a card, set them color 
	if (m_handledCards.size()) {
		std::for_each(m_handledCards.begin(), m_handledCards.end(), [&](Card* card) {
			card->GetSprite().setColor(sf::Color(66, 156, 44, 255));
		});
	}

	// Reset button
	if (Input::IsMouseButtonPressed(sf::Mouse::Left)) {
		if (m_buttonReset.getGlobalBounds().contains(Input::GetMousePosition().x, Input::GetMousePosition().y)) {
			Config::Update(-200);
			ReInit();
		}
	}

	// Game pause menu
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape)) {
		Timer::SetRunning(false);
		m_pMenu.Run();
	}
}

void GamingTable::Draw(sf::RenderWindow & window)
{
	window.draw(m_background);
	window.draw(m_buttonReset);

	for (auto& card : m_cards) {
		// Draw main columns
		if (card->GetColumnId() < 8) {
			if (card->GetPlaceId() > 0) {
			card->Draw(window, sf::Vector2f(m_mainColumnsLeftOffset + (71.0f + m_mainColumnsLeftOffset) * card->GetColumnId(), m_mainColumnsTopOffset + m_mainColumnsCardOffset * (card->GetPlaceId() - 1)));
			}
			else {
				card->Draw(window, sf::Vector2f(m_mainColumnsLeftOffset + (71.0f + m_mainColumnsLeftOffset) * card->GetColumnId(), m_mainColumnsTopOffset));
			}
		}
		// Draw buffer areas
		else if (card->GetColumnId() < 12) {
			card->Draw(window, sf::Vector2f(20.0f + (71.0f + 10.0f) * (card->GetColumnId() - 8), 20.0f));
		}
		// Draw win columns
		else {
			card->Draw(window, sf::Vector2f(m_winColumnsLeftOffset + (71.0f + 10.0f) * (card->GetColumnId() - 12), 20.0f));
		}
	}
	
	// Draw all footer
	window.draw(m_footer);
	window.draw(Timer::GetTimerText());
	Config::DrawConfigText(window);
}