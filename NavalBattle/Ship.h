#pragma once
#include"GameRules.h"


namespace ships {

	enum class SHIPS_TYPE  : char {ONE_DECK = 0 , TWO_DECK = 1 , THREE_DECK = 2 , FOUR_DECK = 3};


	class Ship
	{
		u_char life_;
		bool status_;

		u_char top_x;
		u_char top_y;
		u_char bot_x;
		u_char bot_y;

		virtual void destroy();

	public:

		Ship(u_char life);

		virtual bool decreaseLife();

		std::pair<u_char, u_char> getTopXY()const;
		std::pair<u_char, u_char> getBottomXY()const;

		void setPos(u_char top_x, u_char top_y, u_char bot_x, u_char bot_y);

		bool getStatus()const;

		~Ship();
	};


	class OneDeck : public Ship {
	public:
		OneDeck();

	};

	class TwoDeck : public Ship {
	public:
		TwoDeck();

	};

	class ThreeDeck : public Ship {
	public:
		ThreeDeck();

	};

	class FourDeck : public Ship {
	public:
		FourDeck();

	};

}