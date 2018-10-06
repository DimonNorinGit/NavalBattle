#pragma once
#include"Gamer.h"

class RandomBot : public Gamer
{

	u_int score_;

	u_char ships_alive_;

public:

	RandomBot();

	void arrangeShips(GameField& field , ShipsFactory& sh_factory);
	//std::pair<u_char, u_char> play(const GameField& field); 

	~RandomBot();
};

