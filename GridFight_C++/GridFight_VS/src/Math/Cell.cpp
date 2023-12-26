#include "Cell.h"

Cell::Cell(int2 position) : m_Position(position)
{

}

Cell::Cell() : m_Position(int2(0,0))
{
}

int2 Cell::GetPosition()
{
	return m_Position;
}
