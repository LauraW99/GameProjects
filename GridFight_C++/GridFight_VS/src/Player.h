#pragma once

#include "Character.h"
#include "Math/Grid.h"

class Grid;

class Player : public Character
{
private:
	int m_CurrentLevel;
	int m_CurrentXP;
	int m_RequiredXP;

	void LevelUp();

public:
	Player(const std::string& name, int maximumHealth, int damage);

	void GainXP(int amount);
	void PrintStatus() const override;

	MoveResult MoveTakeTurn(char input);
	//return whether the turn was completed -> if the input was invalid, then just repeat the turn
	CombatResult FightTakeTurn(const char input, Character* enemy);
};
