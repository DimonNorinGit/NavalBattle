#include "ShipsFactory.h"



ShipsFactory::ShipsFactory()
{
	cone_ = 0;
	ctwo_ = 0;
	cthree_ = 0;
	cfour_ = 0;
}

ships::Ship* ShipsFactory::get_ship(ships::SHIPS_TYPE ship_type)
{
	if (ship_type == ships::SHIPS_TYPE::ONE_DECK) {
		return none_deck_ + cone_++;
	}else if (ship_type == ships::SHIPS_TYPE::TWO_DECK) {
		return ntwo_deck_ + ctwo_++;
	}else if (ship_type == ships::SHIPS_TYPE::THREE_DECK) {
		return nthree_deck_ + cthree_++;
	}else if (ship_type == ships::SHIPS_TYPE::FOUR_DECK) {
		return nfour_deck_ + cfour_++;
	}
}


ShipsFactory::~ShipsFactory()
{
}
