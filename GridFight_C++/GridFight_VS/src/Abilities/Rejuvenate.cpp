#include "Rejuvenate.h"
#include "../Character.h"

Rejuvenate::Rejuvenate() : Ability("Rejuvenate", 4)
{
	
}

CombatResult Rejuvenate::Use(Character* other)
{
	Ability::Use(other);
	m_Owner->HealDamage(0.3f);
	return CombatResult::ActionResult(false, m_Owner->m_Name + " used " + m_Name);
}

