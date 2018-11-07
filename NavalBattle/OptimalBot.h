#pragma once

#include"Gamer.h"

class OptimalBot : public Gamer
{
public:
	OptimalBot();


	void arrangeShips(GameField& field, ships::Ship* ship_set[]);
	std::pair<u_char, u_char> play(GameField* field, char* data);

	~OptimalBot();
};

