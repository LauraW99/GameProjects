#include "Enemy.h"
#include "Utility/Random.h"

#include "Enemies/Crawler.h"
#include "Enemies/Exile.h"
#include "Enemies/FoF.h"
#include "Enemies/Monolith.h"
#include "Enemies/Yeti.h"


Enemy::Enemy(const std::string& name, int maximumHealth, int damage, char symbol, int tempo, std::string element, int xpDrop)
	: Character(name, maximumHealth, damage, symbol), m_Tempo(tempo), m_Element(element), m_XPDrop(xpDrop)
{
}

CombatResult Enemy::TakeTurn(Character* other)
{
	int index = 0;
	if (m_Abilities.size() > 0 && m_Abilities[1]->GetCooldown() > m_Abilities[0]->GetCooldown() && m_Abilities[1]->CanCast())
		index = 1;
	auto result = TryUseAbility(index, other);
	if(!result.success)
		return BasicAttack(other);
	
	return result;
}

int Enemy::GetXPDrop()
{
	return m_XPDrop;
}

int Enemy::GetSpawnChance(EEnemyType Type)
{
	switch (Type) {
	case EEnemyType::Yeti: return 2;
	case EEnemyType::Crawler: return 3;
	case EEnemyType::Monolith: return 1;
	case EEnemyType::Exile: return 3;
	case EEnemyType::FoF: return 2;
	}
	return 0;
}

EEnemyType Enemy::GenerateRandomEnemyType()
{
	unsigned int weightSum = 0;
	for (int i = 0; i < sizeof(EEnemyType); i++) {
		EEnemyType enemyType = static_cast<EEnemyType>(i);
		weightSum += GetSpawnChance(enemyType);
	}
	int rnd = Random::Next(0U, weightSum);
	for (int i = 0; i < sizeof(EEnemyType); i++) {
		EEnemyType enemyType = static_cast<EEnemyType>(i);
		if (rnd < GetSpawnChance(enemyType))
			return enemyType;
		rnd -= GetSpawnChance(enemyType);
	}
}

Enemy* Enemy::GenerateRandomEnemy()
{
	EEnemyType Type = GenerateRandomEnemyType();
	Enemy* enemy = nullptr;
	switch (Type) {
	case EEnemyType::Yeti:
		enemy = new Yeti();
		enemy->AddAbility(EAbilityType::Smash);
		enemy->AddAbility(EAbilityType::Howl);
		break;
	case EEnemyType::Crawler:
		enemy = new Crawler();
		enemy->AddAbility(EAbilityType::Claw);
		break;
	case EEnemyType::Monolith:
		enemy = new Monolith();
		enemy->AddAbility(EAbilityType::Rumble);
		enemy->AddAbility(EAbilityType::Smash);
		break;
	case EEnemyType::Exile:
		enemy = new Exile();
		enemy->AddAbility(EAbilityType::Backstab);
		break;
	case EEnemyType::FoF:
		enemy = new FoF();
		enemy->AddAbility(EAbilityType::Fireball);
		enemy->AddAbility(EAbilityType::MeteorStrike);
		break;
	}
	return enemy;
}
