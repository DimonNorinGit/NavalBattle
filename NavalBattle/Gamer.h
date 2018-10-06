#pragma once
//#include"GameField.h"
#include"GameRules.h"
#include"GameField.h"
#include"ShipsFactory.h"
#include<ctime>
	class Gamer
	{

	public:
		Gamer();
		virtual void arrangeShips(GameField& field , ShipsFactory& sh_factory);
		//virtual std::pair<u_char, u_char> play(const GameField& field);

		~Gamer();
	};
