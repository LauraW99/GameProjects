#include "Backstab.h"

Backstab::Backstab() : Ability("Backstab", 2)
{
}

CombatResult Backstab::Use(Character* other)
{
	Ability::Use(other);

	int damage;
	if (static_cast<double>(other->GetCurrentHealth()) / other->GetMaximumHealth() < 0.3) {
		damage = static_cast<int>(m_Owner->m_AttackDamage * 2.2);
	}
	else {
		damage = static_cast<int>(m_Owner->m_AttackDamage * 1.1);
	}

	const bool lethal = other->TakeDamage(damage);
	return CombatResult::ActionResult(lethal, m_Owner->m_Name + " used " + m_Name + " on " + other->m_Name + " and dealt " + std::to_string(damage) + " damage");
}
