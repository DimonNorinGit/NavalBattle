#include "RandomBot.h"



RandomBot::RandomBot()
{
}


bool check_space(GameField& field, u_char ship_space , u_char* diff) {
	u_char field_size = gamerules::FIELD_SIZE;
	u_char status;
	for (u_char x = diff[0]; x <= diff[1]; ++x) {
			for (u_char y = diff[2]; y <= diff[3]; ++y) {
				status = field.get_cell(x , y )->get_status();
				if (status != gamerules::cellstate::CLEAR) {
					return false;
				}
			}
	}

	return true;
}


void setField(GameField& field , ships::Ship* ship) {
	std::pair<u_char, u_char> _vector1 = ship->getTopXY();
	std::pair<u_char, u_char> _vector2 = ship->getBottomXY();

	for (u_char x = _vector1.first; x <= _vector2.first; ++x) {
		for (u_char y = _vector1.second; y <= _vector2.second; ++y) {
			FieldCell* cell = field.get_cell(x, y);
			cell->set_ship(ship);
			cell->set_status(gamerules::cellstate::SHIP);
		}
	}
}

void setShipPos(u_char ship_space, GameField& field , ships::Ship* ship) {
	//std::rand() % gamerules::FIELD_SIZE;
	u_char x = 0;
	u_char y = 0;
	u_char sides[2] = {0};//right top
	u_char possible_sides[4] = { 0 }; //top->right->down->left
	u_char field_size = gamerules::FIELD_SIZE;
	while (true) {
		x = std::rand() % field_size;
		y = std::rand() % field_size;
		u_char status = field.get_cell(x, y)->get_status();
		//bool find_place = true;
		/*if (status == gamerules::cellstate::CLEAR) {
			if (y - ship_space >= 0) {
				char y_diff = y + 1 < field_size ? -1 : 0;
				for (char x_diff = -1; x_diff < 2; ++x_diff) {
					if (x + x_diff > 0 && x + x_diff < field_size) {
						for (; y_diff < ship_space - 1; ++y_diff) {
							status = field.get_cell(x + x_diff, y - y_diff)->get_status();
							if (status != gamerules::cellstate::CLEAR) {
								find_place = false;
							}
						}
					}
					if (!find_place) {
						break;
					}
				}
				
			}*/
		if (status == gamerules::cellstate::CLEAR) {

			u_char diff[4] = { 0 };//x_left x_right y_top y_down
			
			//top
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

void putShip(u_char ship_space , ships::SHIPS_TYPE ship_type , u_char count ,  GameField& field , ShipsFactory& sh_factory) {
	ships::Ship* ship = nullptr;
	for (u_char i = 0; i < count; ++i) {
		ship = sh_factory.get_ship(ship_type);
		setShipPos(ship_space, field, ship);
		setField(field, ship);
		//field.showField();
	}
}


void RandomBot::arrangeShips(GameField& field, ShipsFactory& sh_factory) {
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


/*std::pair<u_char, u_char> RandomBot::play(const GameField& field) {

}*/

RandomBot::~RandomBot()
{
}
