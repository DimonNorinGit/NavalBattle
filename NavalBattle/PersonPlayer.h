#pragma once
#include"Gamer.h"

class PersonPlayer:public Gamer
{
public:
	PersonPlayer();

	void arrangeShips(GameField& field, ShipsFactory& sh_factory, ships::Ship* ship_set[]);

	std::pair<u_char, u_char> play(GameField* field);

	~PersonPlayer();
};

