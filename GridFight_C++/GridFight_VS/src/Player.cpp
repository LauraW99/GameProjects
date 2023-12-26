#include "Player.h"
#include "Math/Grid.h"

Player::Player(const std::string& name, const int maximumHealth, int damage)
	: Character(name, maximumHealth, damage, 'p'), m_CurrentLevel(1), m_CurrentXP(0), m_RequiredXP(50)
{
}

void Player::LevelUp()
{
	m_CurrentLevel++;
	m_CurrentXP = m_CurrentXP % m_RequiredXP;
	m_RequiredXP = static_cast<int>(m_RequiredXP * 1.3);

	m_AttackDamage = static_cast<int>(m_AttackDamage * 1.2);
	m_MaximumHealth = static_cast<int>(m_MaximumHealth * 1.2);
}

void Player::GainXP(int amount)
{
	m_CurrentXP += amount;
	if (m_CurrentXP >= m_RequiredXP) {
		LevelUp();
	}
}

void Player::PrintStatus() const
{
	Character::PrintStatus();
	std::cout << "Level: " << m_CurrentLevel << "(" << m_CurrentXP << "|" << m_RequiredXP << ")\n";
}

MoveResult Player::MoveTakeTurn(const char input)
{
	switch(input)
	{
	case 'w': return Move(int2(0, 1));
	case 'a': return Move(int2(-1, 0));
	case 's': return Move(int2(0, -1));
	case 'd': return Move(int2(1, 0));
	default:
		return { false, m_CurrentPosition, false, nullptr, std::to_string(input) + " is not a valid player input for moving" };
	}
}

CombatResult Player::FightTakeTurn(const char input, Character* enemy)
{
	switch (input)
	{
	case 'a':
		return BasicAttack(enemy);
	case '1':
		return TryUseAbility(0, enemy);
	case '2':
		return TryUseAbility(1, this);

	default:
		return CombatResult::Error(std::to_string(input) + " is not a valid player input for fighting");
	}
}
