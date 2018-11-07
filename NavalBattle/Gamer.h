#pragma once
//#include"GameField.h"
#include"GameRules.h"
#include"GameField.h"
#include"ShipsFactory.h"
#include<ctime>

#include<list>
#include<map>

	class Gamer
	{

	protected:
		u_int score_;
		u_char ships_alive_;

		u_char prev_shotX_;
		u_char prev_shotY_;
		std::map<std::string, std::pair<char, char>> shot_var_;
		std::string shot_dir_;
		bool is_shot_{ false }; 
		bool ship_status_{ false };
		u_char first_hitX;
		u_char first_hitY;

	public:
		Gamer();
		virtual void arrangeShips(GameField& field,  ships::Ship* ship_set[]);
		virtual std::pair<u_char, u_char> play(GameField* field , char* data)=0;
		virtual void setExtraShot(bool ship_status);
		void setShipStatus(bool status);

		bool decreaseShips();
	
		~Gamer();



	};
