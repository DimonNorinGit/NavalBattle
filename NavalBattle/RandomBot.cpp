#include "RandomBot.h"



RandomBot::RandomBot()
{
	

}


bool RandomBot::check_space(GameField& field, u_char ship_space , u_char* diff) {
	u_char field_size = gamerules::FIELD_SIZE;
	u_char status;
	for (u_char x = diff[0]; x <= diff[1]; ++x) {
			for (u_char y = diff[2]; y <= diff[3]; ++y) {
				status = field.getCell(x , y )->get_status();
				if (status != gamerules::cellstate::CLEAR) {
					return false;
				}
			}
	}
	return true;
}

void RandomBot::setShipPos(u_char ship_space, GameField& field , ships::Ship* ship) {
	u_char x = 0;
	u_char y = 0;
	u_char possible_sides[4] = { 0 }; //top->right->down->left
	u_char field_size = gamerules::FIELD_SIZE;
	while (true) {
		x = std::rand() % field_size;
		y = std::rand() % field_size;
		u_char status = field.getCell(x, y)->get_status();
		if (status == gamerules::cellstate::CLEAR) {

			u_char diff[4] = { 0 };//x_left x_right y_top y_down
			
			//top
			//*
			//*
			//* (x,y)
			if (y - ship_space + 1 >= 0) {

				diff[0] = x != 0 ? x - 1 : x;
				diff[1] = x + 1 < field_size ? x + 1 : x;
				diff[2] = y - ship_space >= 0 ? y - ship_space : y - ship_space + 1;
				diff[3] = y + 1 < field_size ? y + 1 : y;
				if (check_space(field, ship_space, diff)) {
					possible_sides[0] = 1;
				}
			}
			//down
			//* (x,y)
			//*
			//*
			if (y + ship_space - 1 < field_size) {
				diff[0] = x != 0 ? x - 1 : x;
				diff[1] = x + 1 < field_size ? x + 1 : x;
				diff[2] = y - 1 >= 0 ? y - 1 : y;
				diff[3] = y + ship_space < field_size ? y + ship_space : y + ship_space;
				if (check_space(field, ship_space, diff)) {
					possible_sides[2] = 1;
				}
			}
			//left
			//* * *(x,y)
			if (x - ship_space + 1 >= 0) {
				diff[0] = x - ship_space >= 0 ? x - ship_space : x - ship_space + 1;
				diff[1] = x + 1 < field_size ? x + 1 : x;
				diff[2] = y != 0 > 0 ? y - 1 : y;
				diff[3] = y + 1 < field_size ? y + 1 : y;
				if (check_space(field, ship_space, diff)) {
					possible_sides[3] = 1;
				}
			}
			//right
			//(x,y)* * *
			if (x + ship_space - 1 < field_size) {
				diff[0] = x != 0 ? x - 1 : x;
				diff[1] = x + ship_space < field_size ? x + ship_space : x + ship_space;
				diff[2] = y != 0 > 0 ? y - 1 : y;
				diff[3] = y + 1 < field_size ? y + 1 : y;
				if (check_space(field, ship_space, diff)) {
					possible_sides[1] = 1;
				}
			}

		}

		for (u_char side = 0; side < 4; ++side) {
			if (possible_sides[side]) {
					
					if (side == 0) {
						ship->setPos(x , y - ship_space + 1, x, y);
					}
					else if (side == 1) {
						ship->setPos(x, y, x + ship_space - 1, y);
					}
					else if (side == 2) {
						ship->setPos(x, y, x, y + ship_space - 1);
					}
					else {
						ship->setPos(x - ship_space + 1, y , x, y);
					}
					return;
			}
		}
	}
}

void RandomBot::putShip(u_char ship_space , ships::SHIPS_TYPE ship_type , u_char ship_count ,  GameField& field , ShipsFactory& sh_factory) {
	ships::Ship* ship = nullptr;
	char diff[4];
	for (u_char i = 0; i < ship_count; ++i) {
		ship = sh_factory.get_ship(ship_type);
		setShipPos(ship_space, field, ship);
		diff[0] = ship->getTopXY().first;
		diff[1] = ship->getBottomXY().first;
		diff[2] = ship->getTopXY().second;
		diff[3] = ship->getBottomXY().second;
		field.fillCells(diff, gamerules::cellstate::SHIP, ship);
	}
}


void RandomBot::arrangeShips(GameField& field, ShipsFactory& sh_factory, ships::Ship* ship_set[]) {
	const u_char ships_count = gamerules::SHIPS_SET::_four_deck;
	u_char ship_space = 4;
	putShip(ship_space , ships::SHIPS_TYPE::FOUR_DECK , gamerules::SHIPS_SET::_four_deck , field , sh_factory);

	ship_space = 3;
	putShip(ship_space, ships::SHIPS_TYPE::THREE_DECK, gamerules::SHIPS_SET::_three_deck, field, sh_factory);

	ship_space = 2;
	putShip(ship_space, ships::SHIPS_TYPE::TWO_DECK, gamerules::SHIPS_SET::_two_deck, field, sh_factory);

	ship_space = 1;
	putShip(ship_space, ships::SHIPS_TYPE::ONE_DECK, gamerules::SHIPS_SET::_one_deck, field, sh_factory);
}


std::pair<u_char, u_char> RandomBot::play(GameField* field) {

	u_char field_size = gamerules::FIELD_SIZE;
	if (ship_status_) {
		int sdf = 0;
		while (true) {
			sdf++;
			char x_diff = this->shot_var_[std::rand() % 3];
			char y_diff = this->shot_var_[std::rand() % 3];
			char shotX = static_cast<char>(prev_shotX_) + x_diff;
			char shotY = static_cast<char>(prev_shotY_) + y_diff;
			if ((shotX >= 0) && (shotX < field_size) && (shotY >= 0) && (shotY < field_size)){ 
				u_char status = field->getCell(shotX , shotY)->get_status();
				if (status != gamerules::cellstate::HIT && status != gamerules::cellstate::USED) {
					prev_shotX_ = shotX;
					prev_shotY_ = shotY;
					return std::make_pair(shotX, shotY);
				}
			}
		}
	}
	u_char x = 0;
	u_char y = 0;
	while (true) {
		x = std::rand() % field_size;
		y = std::rand() % field_size;

		u_char status = field->getCell(x, y)->get_status();
		if (status != gamerules::cellstate::HIT && status != gamerules::cellstate::USED) {
			prev_shotX_ = x;
			prev_shotY_ = y;
			return std::make_pair(x, y);
		}
	}
}

RandomBot::~RandomBot()
{
}
