#pragma once
#include"Gamer.h"

class RandomBot : public Gamer
{

	bool checkSpace(GameField& field, char* diff);
	bool checkShipSpace(GameField& field, char* diff);
	void setShipPos(GameField& field, ships::Ship* ship);
	void changeShotDir(std::string& shot_dir);
public:

	RandomBot();

	void arrangeShips(GameField& field , ships::Ship* ship_set[]);
	std::pair<u_char, u_char> play(GameField* field, char* data);

	~RandomBot();
};

