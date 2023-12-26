#include "Howl.h"

Howl::Howl() : Ability("Howl", 5)
{
}

CombatResult Howl::Use(Character* other)
{
	Ability::Use(other);
	m_Owner->HealDamage(0.1f);
	const int damage = static_cast<int>(m_Owner->m_AttackDamage * 1.1);
	const bool lethal = other->TakeDamage(damage);
	return CombatResult::ActionResult(lethal, m_Owner->m_Name + " used " + m_Name + " on " + other->m_Name + " and dealt " + std::to_string(damage) + " damage");
}
