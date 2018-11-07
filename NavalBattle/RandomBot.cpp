#include "RandomBot.h"



RandomBot::RandomBot()
{
	
}

bool RandomBot::checkSpace(GameField& field, char* diff) {
	char field_size = gamerules::FIELD_SIZE;

	u_char status;
	for (char x = diff[0]; x <= diff[1]; ++x) {
		for (char y = diff[2]; y <= diff[3]; ++y) {
			if (!(x >= 0 && x < field_size && y >= 0 && y < field_size)) {
				continue;
			}

			status = field.getCell(x, y)->get_status();
			if (status != gamerules::cellstate::CLEAR) {
				return false;
			}
		}
	}
	return true;
}


bool RandomBot::checkShipSpace(GameField& field, char* diff) {
	char field_size = gamerules::FIELD_SIZE;
	if (diff[0] >= 0 && diff[1] < field_size && diff[2] >= 0 && diff[3] < field_size) {
		return true;
	}
	return false;
}

void changeShipBorder(char* diff , char border) {
	diff[0] -= border;
	diff[1] += border;
	diff[2] -= border;
	diff[3] += border;
}

void RandomBot::setShipPos(GameField& field, ships::Ship* ship) {
	char field_size = gamerules::FIELD_SIZE;

	char ship_len = ship->getLength();


	char x = 0;
	char y = 0;
	char diff[4];
	bool isFree = false;
	//bool possible_sides[2];

	while (true) {
		x = std::rand() % field_size;
		y = std::rand() % field_size;

		u_char status = field.getCell(x, y)->get_status();

		if (status != gamerules::cellstate::CLEAR)continue;

		diff[0] = x;
		diff[1] = x + ship_len - 1;
		diff[2] = y;
		diff[3] = y;

		isFree = checkShipSpace(field, diff);

		changeShipBorder(diff , 1);
		if (isFree && checkSpace(field, diff)) {
			changeShipBorder(diff , -1);
			ship->setPos(diff[0], diff[2], diff[1], diff[3]);
			field.fillCells(diff, gamerules::cellstate::SHIP, ship);
			break;
		}

		diff[0] = x;
		diff[1] = x;
		diff[2] = y - ship_len + 1;
		diff[3] = y;
		isFree = checkShipSpace(field, diff);

		changeShipBorder(diff, 1);
		if (isFree && checkSpace(field, diff)) {
			changeShipBorder(diff, -1);
			ship->setPos(diff[0], diff[2], diff[1], diff[3]);
			field.fillCells(diff, gamerules::cellstate::SHIP, ship);
			break;
		}
	}
}

void RandomBot::arrangeShips(GameField& field, ships::Ship** ship_set) {
	const u_char ships_count = gamerules::SHIPS_COUNT;

	for (u_char s = 0; s < ships_count; ++s) {
		std::cout << "+++++"<< int(ship_set[s]->getLength()) << std::endl;
		setShipPos(field, ship_set[s]);
	}
}

void RandomBot::changeShotDir(std::string& shot_dir) {
	if (shot_dir == "-x") {
		shot_dir = "y";
	}
	else if (shot_dir == "-y") {
		shot_dir = "x";
		prev_shotX_ = first_hitX;
		prev_shotY_ = first_hitY;
	}
	else {
		shot_dir = "-" + shot_dir;
	}
}

std::pair<u_char, u_char> RandomBot::play(GameField* field, char* data) {

	char field_size = gamerules::FIELD_SIZE;

	if (ship_status_) {
		while (true) {
			char shotX = prev_shotX_;
			char shotY = prev_shotY_;
			shotX += shot_var_[shot_dir_].first;
			shotY += shot_var_[shot_dir_].second;


			if ((shotX >= 0) && (shotX < field_size) && (shotY >= 0) && (shotY < field_size)) {
				u_char status = field->getCell(shotX, shotY)->get_status();
				if (status != gamerules::cellstate::HIT && status != gamerules::cellstate::USED) {//можно поставить непосредственный поиск коробля
					if (status == gamerules::cellstate::SHIP) {
						prev_shotX_ = shotX;
						prev_shotY_ = shotY;
					}
					else {
						changeShotDir(shot_dir_);
					}
					return std::make_pair(shotX, shotY);
				}
			}
			else {
				changeShotDir(shot_dir_);
			}

			/*for (auto diff : shot_diff_) {
				if (shot_diff_.size() == 0) {
					prev_shotX_ = first_hitX;
					prev_shotY_ = first_hitY;
					shot_diff_ = shot_var_;
					break;
				}
				shotX += diff.first;
				shotY += diff.second;
				if ((shotX >= 0) && (shotX < field_size) && (shotY >= 0) && (shotY < field_size)) {
					u_char status = field->getCell(shotX, shotY)->get_status();
					if (status != gamerules::cellstate::HIT && status != gamerules::cellstate::USED) {//можно поставить непосредственный поиск коробля
						if (status == gamerules::cellstate::SHIP) {
							prev_shotX_ = shotX;
							prev_shotY_ = shotY;
							shot_diff_ = shot_var_;
						}
						else {
							shot_diff_.remove(diff);
							std::cout << "---" << shot_diff_.size() << std::endl;
						}
						return std::make_pair(shotX, shotY);
					}
				}

			}*/
			/*if (std::rand() % 2) {
				shotX = 1;
			}
			else {
				shotY = 1;
			}
			if (std::rand() % 2) {
				shotX *= (-1);
				shotY *= (-1);
			}*/


		}
	}
	/*if (ship_status_) {
		while (true) {
			char x_diff = this->shot_var_[std::rand() % 3];
			char y_diff = this->shot_var_[std::rand() % 3];
			char shotX = static_cast<char>(prev_shotX_) + x_diff;
			char shotY = static_cast<char>(prev_shotY_) + y_diff;
			if ((shotX >= 0) && (shotX < field_size) && (shotY >= 0) && (shotY < field_size)){ 
				u_char status = field->getCell(shotX , shotY)->get_status();
				if (abs(prev_shotX_ - shotX) + abs(prev_shotY_ - shotY) == 2) {//диагональ
					continue;
				}
				if (status != gamerules::cellstate::HIT && status != gamerules::cellstate::USED) {//можно поставить непосредственный поиск коробля
					if (status == gamerules::cellstate::SHIP) {
						prev_shotX_ = shotX;
						prev_shotY_ = shotY;
					}
					return std::make_pair(shotX, shotY);
				}
			}
		}
	}*/

	u_char x = 0;
	u_char y = 0;
	while (true) {
		x = std::rand() % field_size;
		y = std::rand() % field_size;

		u_char status = field->getCell(x, y)->get_status();
		if (status != gamerules::cellstate::HIT && status != gamerules::cellstate::USED) {
			prev_shotX_ = x;
			prev_shotY_ = y;
			first_hitX = x;
			first_hitY = y;
			return std::make_pair(x, y);
		}
	}
}

RandomBot::~RandomBot()
{
}
