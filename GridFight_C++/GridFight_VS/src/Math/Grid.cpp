#include "Grid.h"
#include <iostream>

#include "../Player.h"


Grid* Grid::Instance = nullptr;

Grid::Grid(const unsigned width, const unsigned height) : m_Width(width), m_Height(height)
{
	Instance = this;
	InitializeCells();
}

void Grid::InitializeCells()
{
	m_Values.resize(m_Width * m_Height);

	for (unsigned int y = 0, idx = 0; y < m_Height; ++y)
	{
		for (unsigned int x = 0; x < m_Width; ++x, ++idx)
		{
			m_Values[idx] = Cell(int2(x, y));
		}
	}
}

bool Grid::GetValueAtIndex(const unsigned index) const
{
	if(IndexInBounds(index))
		return m_Values[index].blocked;

	std::cout << "Index was out of range" << std::endl;
	return false;
}

bool Grid::GetValueAtLocation(const int2 location) const
{
	const unsigned int index = GetIndexFromLocation(location);
	return GetValueAtIndex(index);
}

void Grid::SetValueAtIndex(const unsigned index, const bool value)
{
	m_Values[index].blocked = value;
}

void Grid::SetValueAtLocation(const int2 location, const bool value)
{
	const unsigned int index = GetIndexFromLocation(location);
	SetValueAtIndex(index, value);
}

Cell& Grid::GetCellAtIndex(const unsigned index)
{
	if (IndexInBounds(index))
		return m_Values[index];

	std::cout << "index not in bounds" << std::endl;
	return m_Values[0];
}

Cell& Grid::GetCellAtLocation(const int2 location)
{
	return GetCellAtIndex(GetIndexFromLocation(location));
}

unsigned int Grid::GetIndexFromLocation(const int2 location) const
{
	return m_Width * location.y + location.x;
}

int2 Grid::GetLocationFromIndex(const unsigned int index)
{
	return m_Values[index].GetPosition();
}

unsigned Grid::GetWidth() const
{
	return m_Width;
}

unsigned Grid::GetHeight() const
{
	return m_Height;
}

bool Grid::IndexInBounds(const unsigned index) const
{
	return index < m_Width * m_Height;
}

bool Grid::LocationInBounds(const int2 location) const
{
	return location.x >= 0 && location.x < m_Width && location.y >= 0 && location.y < m_Height;
}

void Grid::Print()
{
	//std::cout << "Grid: " << std::endl;
	for (int y = m_Height - 1; y >= 0; --y)
	{
		for (unsigned int x = 0; x < m_Width; ++x)
		{
			const Cell& currentCell = GetCellAtLocation(int2(x,y));
			char symbol = '.';
			if (currentCell.m_Character != nullptr)
			{
				const auto* cast = dynamic_cast<Player*>(currentCell.m_Character);
				symbol = currentCell.m_Character->GetSymbol();
			}
			std::cout << symbol;
			if (x < m_Width - 1)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}
