#pragma once
#include"GameField.h"
#pragma comment(lib , "ws2_32.lib")
#include<WinSock2.h>



#include"ShipsFactory.h"
#include"Gamer.h"
#include <Windows.h>

#include <sys/types.h>

//test
#include"RandomBot.h"
#include"PersonPlayer.h"
#include"OptimalBot.h"

class Game
{


	GameField left_field_;
	Gamer* left_player_;

	GameField right_field_;
	Gamer* right_player_;

	ShipsFactory ship_factory_;

	SOCKADDR_IN addr_;
	int addrlen_;
	int port_{9090};
	SOCKET sListen_;

	bool isWork_{ true };

	void initGame();
	u_char defineGamer(Gamer** gamer, u_char type);
	void decodeShipsArrange(char* buf, int buf_diff, ships::Ship** ship_set);
	void setShipSet(ships::Ship** ship_set);
	void packFieldStates(char* buf, int diff, GameField& field);
	void packCells(char* diff, char* buf, GameField& field, int buf_d);
	void prepareStage();
	void gameStage();

public:
	Game();
	void start();
	~Game();
};

