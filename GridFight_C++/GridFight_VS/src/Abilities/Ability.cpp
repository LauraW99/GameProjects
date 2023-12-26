#include "Ability.h"

Ability::Ability(std::string name, int cooldown) 
	: m_Owner(nullptr), m_Name(name), m_Cooldown(cooldown), m_CurrentCooldown(0)
{
	
}

bool Ability::CanCast()
{
	return m_CurrentCooldown <= 0;
}

int Ability::GetCooldown() const
{
	return m_Cooldown;

}

int Ability::GetCurrentCooldown() const
{
	return m_CurrentCooldown;
}

CombatResult Ability::Use(Character* other)
{
	//reset cooldown
	m_CurrentCooldown = m_Cooldown;
	return {};
}

void Ability::SetOwner(Character* owner)
{
	m_Owner = owner;
}

void Ability::ReduceCooldown()
{
	m_CurrentCooldown--;
	if (m_CurrentCooldown < 0)
		m_CurrentCooldown = 0;
}

void Ability::ResetCooldown()
{
	m_CurrentCooldown = 0;
}


