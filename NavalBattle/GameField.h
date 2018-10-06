#pragma once
#include"GameRules.h"
#include"FieldCell.h"

class GameField
{

	FieldCell ncells_[gamerules::FIELD_SIZE * gamerules::FIELD_SIZE];
	u_char field_size_;
public:

	//char getCellStatus(const size_t x, const size_t y)const;

	//void setCellStatus(const size_t x, const size_t y, u_char state);

	//only for Test
	void showField()const;

	//void clear();

	FieldCell* get_cell(const size_t x, const size_t y)const;

	GameField();

	~GameField();
};

