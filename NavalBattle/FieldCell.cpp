#include "FieldCell.h"



FieldCell::FieldCell()
{
	state_ = gamerules::cellstate::CLEAR;
	ship_ = nullptr;
}
void FieldCell::set_status(u_char st) {
	state_ = st;
}
u_char FieldCell::get_status()const {
	return state_;
}
ships::Ship* FieldCell::get_ship()const {
	return ship_;
}

void FieldCell::set_ship(ships::Ship* ship) {
	ship_ = ship;
}

FieldCell::~FieldCell()
{
}
