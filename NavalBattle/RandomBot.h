#pragma once
#include"Gamer.h"

class RandomBot : public Gamer
{

	bool check_space(GameField& field, u_char ship_space, u_char* diff);
	void setShipPos(u_char ship_space, GameField& field, ships::Ship* ship);
	void putShip(u_char ship_space, ships::SHIPS_TYPE ship_type, u_char ship_count, GameField& field, ShipsFactory& sh_factory);
public:

	RandomBot();

	void arrangeShips(GameField& field , ShipsFactory& sh_factory, ships::Ship* ship_set[]);
	std::pair<u_char, u_char> play(GameField* field, char* data);

	~RandomBot();
};

