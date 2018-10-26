#include "GameField.h"



GameField::GameField()
{
	field_size_ = gamerules::FIELD_SIZE;
	//std::memset(ncells_ , gamerules::cellstate::CLEAR , gamerules::FIELD_SIZE * gamerules::FIELD_SIZE);//fill cells to default
}

void GameField::showField()const
{
	for (size_t i = 0; i <= field_size_; ++i) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < gamerules::FIELD_SIZE; ++i) {
		for (size_t j = 0; j < gamerules::FIELD_SIZE; ++j) {
			if (ncells_[i * field_size_ + j].get_status() == gamerules::cellstate::HIT) {
				std::cout << "!";
			}
			else if (ncells_[i * field_size_ + j].get_status() == gamerules::cellstate::USED) {
				std::cout << "*";
			}
			else if (ncells_[i * field_size_ + j].get_status() == gamerules::cellstate::SHIP) {
				std::cout << "^";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	for (size_t i = 0; i <= field_size_; ++i) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

FieldCell* GameField::getCell(const size_t x, const size_t y)const {
	return const_cast<FieldCell*>(&ncells_[field_size_ * y + x]);
}

void GameField::fillCells(char* diff, u_char cell_status, ships::Ship* ship) {
	for (char x = diff[0]; x <= diff[1]; ++x) {
		for (char y = diff[2]; y <= diff[3]; ++y) {
			if (x >= 0 && x < field_size_ && y >= 0 && y < field_size_) {
				if (ncells_[y * field_size_ + x].get_status() == gamerules::cellstate::HIT) {
					continue;
				}
				ncells_[y * field_size_ + x].set_status(cell_status);
				if (ship) {
					ncells_[y * field_size_ + x].set_ship(ship);
				}
			}
		}
	}
}


GameField::~GameField()
{
}
