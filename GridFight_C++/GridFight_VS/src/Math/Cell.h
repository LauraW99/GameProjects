#pragma once
#include "Int2.h"

class Character;

class Cell
{
private:
	int2 m_Position;

public:
	Cell(int2 position);
	Cell();

	int2 GetPosition();

	bool blocked = false;
	Character* m_Character = nullptr;
};
