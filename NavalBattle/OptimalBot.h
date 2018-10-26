#pragma once

#include"Gamer.h"

class OptimalBot : public Gamer
{
public:
	OptimalBot();


	void arrangeShips(GameField& field, ShipsFactory& sh_factory , ships::Ship* ship_set[]);
	std::pair<u_char, u_char> play(GameField* field);

	~OptimalBot();
};

