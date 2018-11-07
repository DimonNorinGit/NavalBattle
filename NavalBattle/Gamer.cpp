#include "Gamer.h"



Gamer::Gamer()
{
	ships_alive_ = gamerules::SHIPS_COUNT;
	prev_shotX_ = 0;
	prev_shotY_ = 0;
	ship_status_ = false;
	shot_var_["x"] = std::make_pair(1, 0);
	shot_var_["y"] = std::make_pair(0, 1);
	shot_var_["-x"] = std::make_pair(-1, 0);
	shot_var_["-y"] = std::make_pair(0, -1);
	shot_dir_ = "x";
}


void Gamer::arrangeShips(GameField& field, ships::Ship* ship_set[]) {

}

bool Gamer::decreaseShips() {
	if (ships_alive_ == 0) return false;
	--ships_alive_;
	if (ships_alive_ == 0) {
		//destroy();
		return false;
	}
	return true;
}

void Gamer::setExtraShot(bool status) {
	is_shot_ = status;
}
void Gamer::setShipStatus(bool status) {
	ship_status_ = status;
}


Gamer::~Gamer()
{
}
