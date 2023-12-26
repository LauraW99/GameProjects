#pragma once
#include "Character.h"

enum class EEnemyType
{
	Yeti,
	Crawler,
	Monolith,
	Exile,
	FoF
};

class Enemy : public Character
{
private:
	unsigned int m_Tempo;
	std::string m_Element;
	unsigned int m_XPDrop;

public:
	Enemy(const std::string& name, int maximumHealth, int damage, char symbol, int tempo, std::string element, int xpDrop);

	CombatResult TakeTurn(Character* other);

	int GetXPDrop();
	static int GetSpawnChance(EEnemyType Type);

	static EEnemyType GenerateRandomEnemyType();
	static Enemy* GenerateRandomEnemy();
};


