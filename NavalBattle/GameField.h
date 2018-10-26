#pragma once
#include"GameRules.h"
#include"FieldCell.h"

class GameField
{

	FieldCell ncells_[gamerules::FIELD_SIZE * gamerules::FIELD_SIZE];
	u_char field_size_;
public:
	//only for Test
	void showField()const;

	FieldCell* getCell(const size_t x, const size_t y)const;

	void fillCells(char* diff, u_char cell_status , ships::Ship* ship = 0);


	GameField();

	~GameField();
};

