#include "Game.h"

#include "Enemy.h"
#include "Player.h"
#include "Math/Grid.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include <string>

#include "Abilities/Ability.h"
#include "Utility/Random.h"

void Game::PrintCombat(const bool turn, const Player* character1, const Character* character2, const std::string& statusMessage,
	const std::string& actionMessage)
{
	system("CLS");

	//Instructions
	std::string message;
	if (turn)
	{
		message = "Press a to attack, ";
		const std::vector<Ability*>& abilities = character1->GetAbilities();
		for (int i = 0; i < abilities.size(); ++i)
		{
			message += "Press " + std::to_string(i + 1) + " to cast " + abilities[i]->m_Name;
			if (i < abilities.size() - 1)
				message += ", ";
		}
	}
	else
	{
		message = "Press Enter";
	}
	std::cout << message << "\n\n";
	std::cout << statusMessage << "\n\n";
	character1->PrintStatus();
	std::cout << "\n";
	character2->PrintStatus();
	std::cout << "\n" << actionMessage << "\n";
}

bool Game::OnFightEnd(const bool won)
{
	system("CLS");
	std::cout << (won ? "The Player won the fight!" : "The Player was defeated!") << std::endl;
	std::cin.get();
	return won;
}

bool Game::OnGameEnd(bool won)
{
	system("CLS");
	std::cout << (won ? "The Player won the game!" : "The Player lost the game!") << std::endl;
	std::cin.get();
	return won;
}

//Combat Loop
bool Game::Fight(Enemy* opponent) const
{
	PrintCombat(true, m_Player, opponent, "", "");
	CombatResult result;
	while (true)
	{
		bool playerTurn = true;

		//loop until the m_Player enters a valid input
		while (playerTurn)
		{
			const char c = static_cast<char>(_getch());

			result = m_Player->FightTakeTurn(c, opponent);

			PrintCombat(!result.success, m_Player, opponent, result.message, result.actionMessage);
			if (result.success)
				playerTurn = false;
		}

		m_Player->EndTurn();

		if (opponent->IsDead())
			return OnFightEnd(true);


		std::cin.get();

		result = opponent->TakeTurn(m_Player);
		opponent->EndTurn();

		PrintCombat(true, m_Player, opponent, result.message, result.actionMessage);


		if (m_Player->IsDead())
			return OnFightEnd(false);
	}
}

Game::Game(const GameParameters& params)
{
	this->params = params;
	m_Grid = new Grid(params.gridWidth, params.gridHeight);
	m_Player = new Player("Player", 45, 8);
}

Game::~Game()
{
	delete m_Player;
	delete m_Grid;
	for (auto enemy : enemies)
	{
		delete enemy;
	}
}
bool Game::Run()
{
	Random::Init();

	m_Player->AddAbility(EAbilityType::Fireball);
	m_Player->AddAbility(EAbilityType::Rejuvenate);
	m_Player->SetPosition(params.playerStart);

	for (int i = 0; i < params.enemyCount; ++i)
	{
		//position enemy
		constexpr int maxIter = 100;
		int it = 0;
		int2 pos;


		while (it < maxIter)
		{
			++it;

			pos = int2(Random::Next(0U, params.gridWidth), Random::Next(0U, params.gridHeight));
			const unsigned int dist = pos.ManhattanDistance(params.playerStart);
			//test if distance to m_Player is big enough
			if (dist < 3)
				continue;

			//test if cell is already occupied
			if (Grid::Instance->GetCellAtLocation(pos).m_Character != nullptr)
				continue;

			break;
		}

		//enemy could not be placed
		if (it == maxIter)
		{
			std::cout << "enemy could not be placed" << std::endl;
			continue;
		}

		Enemy* enemy = Enemy::GenerateRandomEnemy();
		enemy->SetPosition(pos);
		enemies.push_back(enemy);
	}

	PrintBoard("");
	while (true)
	{
		char c = _getch();

		MoveResult result = m_Player->MoveTakeTurn(c);

		PrintBoard(result.message);

		//when an m_Enemy is encountered, fight against it and return whether the fight was won
		if (result.encounteredChar != nullptr)
		{
			const bool fightResult = Fight(dynamic_cast<Enemy*>(result.encounteredChar));
			//if the fight was won, clean up the enemy from the array and take its place on the m_Grid
			if (fightResult)
			{
				//if no more enemies are present, return true
				if (enemies.size() == 1)
				{
					return OnGameEnd(true);
				}

				//remove enemy
				enemies.erase(std::remove(enemies.begin(), enemies.end(), result.encounteredChar), enemies.end());

				//take enemies position
				const int2 enemyPosition = result.encounteredChar->GetCurrentPosition();
				Grid::Instance->GetCellAtLocation(enemyPosition).m_Character = nullptr;
				m_Grid->GetCellAtLocation(m_Player->GetCurrentPosition()).m_Character = nullptr;
				m_Player->SetPosition(enemyPosition);

				//end of fight
				m_Player->GainXP(dynamic_cast<Enemy*>(result.encounteredChar)->GetXPDrop());
				delete result.encounteredChar;

				m_Player->HealDamage(static_cast<int>(static_cast<float>(m_Player->GetMaximumHealth()) / 2.0f));
				m_Player->ResetCooldowns();


				PrintBoard(result.message);
			}
			else
			{
				return OnGameEnd(false);
			}
		}
	}
}

void Game::PrintBoard(const std::string& statusMessage) const
{
	system("CLS");
	std::cout << "*Laura Wagner*";
	std::cout << statusMessage << "\n\n";
	m_Grid->Print();
}