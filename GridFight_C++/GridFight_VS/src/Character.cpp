#include "Character.h"
#include <iostream>

#include "Abilities/Ability.h"
#include "Abilities/Fireball.h"
#include "Abilities/Rejuvenate.h"
#include "Abilities/Meteorstrike.h"
#include "Abilities/Backstab.h"
#include "Abilities/Claw.h"
#include "Abilities/Howl.h"
#include "Abilities/Rumble.h"
#include "Abilities/Smash.h"
#include "Math/Grid.h"

Character::Character(const std::string& name, const int maximumHealth, int damage, char symbol) 
	: m_Name(name), m_AttackDamage(damage), m_MaximumHealth(maximumHealth), m_CurrentHealth(maximumHealth), m_Symbol(symbol)
{

}

Character::~Character()
{
	for (int i = 0; i < m_Abilities.size(); ++i)
	{
		delete m_Abilities[i];
	}
}

void Character::HealDamage(float percentage)
{
	m_CurrentHealth += static_cast<int>(m_MaximumHealth * percentage);
	if (m_CurrentHealth > m_MaximumHealth)
		m_CurrentHealth = m_MaximumHealth;
}

CombatResult Character::BasicAttack(Character* other) const
{
	const std::string message = m_Name + " dealt " + std::to_string(m_AttackDamage) + " damage to " + other->m_Name + " using basic attack";

	const bool lethal = other->TakeDamage(m_AttackDamage);
	return CombatResult::ActionResult(lethal, message);
}


constexpr int max_Abilities = 2;
void Character::AddAbility(EAbilityType Type)
{
	if (m_Abilities.size() >= max_Abilities)
		return;

	Ability* newAbility = nullptr;
	switch (Type)
	{
	case EAbilityType::Fireball:
		newAbility = new Fireball();
		break;
	case EAbilityType::MeteorStrike:
		newAbility = new Meteorstrike();
		break;
	case EAbilityType::Rejuvenate:
		newAbility = new Rejuvenate();
		break;
	case EAbilityType::Backstab:
		newAbility = new Backstab();
		break;
	case EAbilityType::Claw:
		newAbility = new Claw();
		break;
	case EAbilityType::Howl:
		newAbility = new Howl();
		break;
	case EAbilityType::Rumble:
		newAbility = new Rumble();
		break;
	case EAbilityType::Smash:
		newAbility = new Smash();
		break;
	}

	if(m_Abilities.size() < max_Abilities)
	{
		m_Abilities.push_back(newAbility);
		newAbility->SetOwner(this);
	}
}

const std::vector<Ability*>& Character::GetAbilities() const
{
	return m_Abilities;
}

Ability* Character::GetAbility(const unsigned int index) const
{
	return m_Abilities[index];
}

bool Character::HasAbility(const unsigned int index) const
{
	return index < m_Abilities.size();
}

void Character::UseAbility(const unsigned int index, Character* other) const
{
	if(HasAbility(index))
		m_Abilities[index]->Use(other);
}

void Character::ResetCooldowns()
{
	for (auto ability : m_Abilities)
	{
		ability->ResetCooldown();
	}
}

void Character::SetPosition(const int2 position)
{
	if(!Grid::Instance->LocationInBounds(position))
	{
		std::cout << position << " was not in bounds of grid" << std::endl;
		return;
	}
	Cell& cell = Grid::Instance->GetCellAtLocation(position);
	cell.m_Character = this;
	m_CurrentPosition = position;
}

MoveResult Character::Move(const int2 movementDelta)
{
	const int2 newPosition = m_CurrentPosition + movementDelta;
	if (!Grid::Instance->LocationInBounds(newPosition))
		return MoveResult::Error(static_cast<std::string>(newPosition) + " was not in bounds of grid");
	
	Cell& newCell = Grid::Instance->GetCellAtLocation(newPosition);

	//check if the target cell was already occupied by a different character
	if (newCell.m_Character != nullptr)
		return { true, m_CurrentPosition, false, newCell.m_Character, "" };

	Cell& currentCell = Grid::Instance->GetCellAtLocation(m_CurrentPosition);
	currentCell.m_Character = nullptr;

	newCell.m_Character = this;
	m_CurrentPosition = newPosition;
	return { true, newPosition, true, nullptr, "" };
	
}

char Character::GetSymbol()
{
	return m_Symbol;
}

int Character::GetCurrentHealth() const
{
	return m_CurrentHealth;
}

int Character::GetMaximumHealth() const
{
	return m_MaximumHealth;
}

int2 Character::GetCurrentPosition() const
{
	return m_CurrentPosition;
}

void Character::PrintStatus() const
{
	std::cout << m_Name << ": \n" << "HP: " << m_CurrentHealth << "/" << m_MaximumHealth << "\n" << "Abilities: \n";
	for (int i = 0; i < m_Abilities.size(); ++i)
	{
		const Ability* current = m_Abilities[i];
		std::cout << (i + 1) << ": " << current->m_Name << "  Cooldown: " << current->GetCurrentCooldown() << "/" << current->GetCooldown() << std::endl;
	}
}

bool Character::TakeDamage(const int amount)
{
	m_CurrentHealth -= amount;
	if (m_CurrentHealth <= 0)
		return true;

	return false;
}

bool Character::IsDead() const
{
	return m_CurrentHealth <= 0;
}


CombatResult Character::TryUseAbility(unsigned index, Character* target)
{
	if (!HasAbility(index))
	{
		return  CombatResult::Error(m_Name + " does not have that ability!");
	}
	Ability* ability = GetAbility(index);
	if (!ability->CanCast())
	{
		return CombatResult::Error("Ability " + ability->m_Name + " is currently on cooldown");
	}
	return ability->Use(target);
}

void Character::EndTurn()
{
	for (auto ability : m_Abilities)
	{
		ability->ReduceCooldown();
	}
}




