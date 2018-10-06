#include "GameField.h"



GameField::GameField()
{
	field_size_ = gamerules::FIELD_SIZE;
	//std::memset(ncells_ , gamerules::cellstate::CLEAR , gamerules::FIELD_SIZE * gamerules::FIELD_SIZE);//fill cells to default
}

void GameField::showField()const
{
	for (size_t i = 0; i < gamerules::FIELD_SIZE; ++i) {
		for (size_t j = 0; j < gamerules::FIELD_SIZE; ++j) {
			std::cout << int(ncells_[i * field_size_ + j].get_status()) << int(ncells_[i * field_size_ + j].get_status());
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
/*char GameField::getCellStatus(const size_t x , const size_t y)const
{
	//check x and y or not(
	return ncells_[x][y].get_status();
}

void GameField::setCellStatus(const size_t x, const size_t y, u_char state)
{
	//check x and y and state or not(
	ncells_[x][y].set_status(state);
}*/



FieldCell* GameField::get_cell(const size_t x, const size_t y)const {
	return const_cast<FieldCell*>(&ncells_[field_size_ * y + x]);
}

GameField::~GameField()
{
}
