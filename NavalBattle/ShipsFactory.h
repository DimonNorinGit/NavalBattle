#pragma once
#include"Ship.h"
#include"GameRules.h"

//there is no check for ships limit


class ShipsFactory
{
private:
	ships::OneDeck none_deck_[gamerules::SHIPS_SET::_one_deck * 2];
	u_char cone_;
	ships::TwoDeck ntwo_deck_[gamerules::SHIPS_SET::_two_deck * 2];
	u_char ctwo_;
	ships::ThreeDeck nthree_deck_[gamerules::SHIPS_SET::_three_deck * 2];
	u_char cthree_;
	ships::FourDeck nfour_deck_[gamerules::SHIPS_SET::_four_deck  * 2];
	u_char cfour_;
		
public:
	ShipsFactory();

	ships::Ship* get_ship(ships::SHIPS_TYPE ship_type);

	~ShipsFactory();
};

