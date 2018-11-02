#include "Gamer.h"



Gamer::Gamer()
{
	ships_alive_ = gamerules::SHIPS_COUNT;
	prev_shotX_ = 0;
	prev_shotY_ = 0;
	ship_status_ = false;
}


void Gamer::arrangeShips(GameField& field, ShipsFactory& sh_factory, ships::Ship* ship_set[]) {

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

void Gamer::setExtraShot(bool ship_status) {
	ship_status_ = ship_status;
}


Gamer::~Gamer()
{
}
