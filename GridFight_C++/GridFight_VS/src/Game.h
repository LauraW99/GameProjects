#pragma once
#include <vector>

#include "../GameParameters.h"

class Character;
class Player;
class Grid;
class Enemy;

class Game
{
private:
	Grid* m_Grid = nullptr;
	Player* m_Player = nullptr;
	std::vector<Enemy*> enemies;
	GameParameters params;
public:
	Game(const GameParameters& params);
	~Game();
	bool Run();

private:
	bool Fight(Enemy* opponent) const;

	void PrintBoard(const std::string& statusMessage) const;
	static void PrintCombat(bool turn, const Player* character1, const Character* character2, const std::string& statusMessage, const std::string& actionMessage);
	static bool OnFightEnd(bool won);
	static bool OnGameEnd(bool won);
};

