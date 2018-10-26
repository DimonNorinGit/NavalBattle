#pragma once
#include<iostream>


//using unsigned char 

using  u_char = unsigned char;

using u_int = unsigned int;

namespace gamerules{

	const u_int FIELD_SIZE = 10;

	namespace SHIPS_SET {

		const u_char _one_deck = 4;

		const u_char _two_deck = 3;

		const u_char _three_deck = 2;

		const u_char _four_deck = 1;

	}

	const u_char SHIPS_COUNT = 10;




	namespace cellstate {
		const u_char CLEAR = 0;

		const u_char SHIP = 1;

		const u_char USED = 2;

		const u_char HIT = 3;
	}


	const u_int INT_SIZE = sizeof(int);
}


