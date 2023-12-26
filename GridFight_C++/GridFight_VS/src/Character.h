#pragma once
#include <vector>

#include "Abilities/Ability.h"
#include "Math/Grid.h"
#include "Math/Int2.h"

enum class EAbilityType;
class Ability;

struct CombatResult
{
	bool success;
	bool lethal;
	std::string message;
	std::string actionMessage;

	static CombatResult Error(const std::string& _message)
	{
		return { false, false, _message, "" };
	}

	static CombatResult ActionResult(const bool _lethal, const std::string& _actionMessage)
	{
		return { true, _lethal, "", _actionMessage };
	}
};

class Character
{
public:
	int m_AttackDamage = 3;
	std::string m_Name;

protected:
	char m_Symbol;
	int m_MaximumHealth = 0;
	int m_CurrentHealth = 0;
	int2 m_CurrentPosition;

	std::vector<Ability*> m_Abilities;

public:
	Character(const std::string& name, int maximumHealth, int damage, char symbol);
	virtual ~Character();

	//recover a certain percentage of the max health
	void HealDamage(float percentage);

	//take a certain amount of damage, return true if dead
	bool TakeDamage(int amount);
	bool IsDead() const;

	CombatResult BasicAttack(Character* other) const;

	void AddAbility(EAbilityType type);

	const std::vector<Ability*>& GetAbilities() const;
	Ability* GetAbility(unsigned int index) const;
	bool HasAbility(unsigned int index) const;
	void UseAbility(unsigned int index, Character* other) const;
	void ResetCooldowns();

	void SetPosition(int2 position);
	MoveResult Move(int2 movementDelta);
	char GetSymbol();
	int GetCurrentHealth() const;
	int GetMaximumHealth() const;
	int2 GetCurrentPosition() const;

	virtual void PrintStatus() const;

	void EndTurn();

protected:
	CombatResult TryUseAbility(unsigned int index, Character* target);

};