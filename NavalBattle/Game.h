#pragma once
#include"GameField.h"
#include"ShipsFactory.h"
#include"Gamer.h"

//test
#include"RandomBot.h"

class Game
{


	GameField left_field_;
	Gamer* left_player_;

	GameField right_field_;
	Gamer* right_player_;
	ShipsFactory ship_factory_;



	

public:
	Game();
	void start();
	~Game();
};

