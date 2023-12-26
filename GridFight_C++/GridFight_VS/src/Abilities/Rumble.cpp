#include "Rumble.h"

Rumble::Rumble() : Ability("Rumble", 6)
{
    m_CurrentCooldown = m_Cooldown;
}

CombatResult Rumble::Use(Character* other)
{
	Ability::Use(other);
	const int damage = static_cast<int>(m_Owner->m_AttackDamage * 5.0);
	const bool lethal = other->TakeDamage(damage);
	return CombatResult::ActionResult(lethal, m_Owner->m_Name + " used " + m_Name + " on " + other->m_Name + " and dealt " + std::to_string(damage) + " damage");
}
