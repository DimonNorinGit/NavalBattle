#include "PersonPlayer.h"



PersonPlayer::PersonPlayer()
{
}


void PersonPlayer::arrangeShips(GameField& field, ships::Ship* ship_set[]) {
	u_char field_size = gamerules::FIELD_SIZE;
	char diff[4];
	ships::Ship* ship = 0;
	//void GameField::fillCells(char* diff, u_char cell_status, ships::Ship* ship)
	for (int s = 0; s < gamerules::SHIPS_COUNT; ++s) {
		ship = ship_set[s];
		diff[0] = ship->getTopXY().first;
		diff[1] = ship->getBottomXY().first;
		diff[2] = ship->getTopXY().second;
		diff[3] = ship->getBottomXY().second;
		field.fillCells(diff, gamerules::cellstate::SHIP, ship);
	}
}
std::pair<u_char, u_char> PersonPlayer::play(GameField* field , char* data) {
	return std::make_pair(data[0] , data[1]);
}

PersonPlayer::~PersonPlayer()
{
}
