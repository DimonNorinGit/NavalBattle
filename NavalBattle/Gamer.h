#pragma once
//#include"GameField.h"
#include"GameRules.h"
#include"GameField.h"
#include"ShipsFactory.h"
#include<ctime>
	class Gamer
	{

	protected:
		u_int score_;
		u_char ships_alive_;

		u_char prev_shotX_;
		u_char prev_shotY_;
		char shot_var_[3] = { -1 , 1 , 0};
		bool ship_status_;

	public:
		Gamer();
		virtual void arrangeShips(GameField& field, ShipsFactory& sh_factory, ships::Ship* ship_set[]);
		virtual std::pair<u_char, u_char> play(GameField* field , char* data)=0;
		virtual void setExtraShot(bool  ship_status);
		bool decreaseShips();
	
		~Gamer();



	};
