#include "Game.h"



Game::Game()
{
	left_player_ = nullptr;
	right_player_ = nullptr;


	WSADATA wsData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsData) != 0) {
		std::cout << "Server startupError\n";
		exit(1);
	}

	addr_.sin_addr.s_addr = htonl(INADDR_ANY);// inet_addr("127.0.0.1");

	addr_.sin_port = htons(port_);

	addr_.sin_family = AF_INET;//IPv4 socket

	addrlen_ = sizeof(addr_);


}


u_char Game::defineGamer(Gamer** gamer , u_char type) {
	switch (type) {

	case 'h':
		*gamer = new PersonPlayer();
		return 1;
	case 'o':
		*gamer = new OptimalBot();
		return 0;
	case 'r':
		*gamer = new RandomBot();
		return 0;
	default:
		std::cout << "Type Error\n";
		system("pause");
	}
}



void Game::decodeShipsArrange(char* buf, int buf_diff, ships::Ship** ship_set) {

	int ships_count = gamerules::SHIPS_COUNT;

	for (int ship_n = 0; ship_n < ships_count;++ship_n) {
		int data_i = buf_diff + ship_n;
		char top_x = buf[data_i];
		char top_y = buf[data_i + 1];
		char bot_x = buf[data_i + 2];
		char bot_y = buf[data_i + 3];

		char v_size = top_y - bot_y;
		char g_size = top_x - bot_x;

		int ship_type = v_size > g_size ? v_size : g_size;

		ships::Ship* ship = ship_factory_.get_ship(ships::SHIPS_TYPE(ship_type));
		ship->setPos(top_x, top_y, bot_x, bot_y);
		ship_set[ship_n] = ship;
	}

}


void Game::start() {


	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr_, sizeof(addr_));

	listen(sListen, 1);//SOMAXCONN

	SOCKET sConnect = accept(sListen, (SOCKADDR*)&addr_, &addrlen_);

	if (sConnect == 0) {
		std::cout << "Connection failed\n";
		system("pause");
	}

	int buflen = 82;
	char buf[82];

	recv(sConnect, buf, buflen, 0);
	closesocket(sConnect);


	u_char human_count = 0;
	human_count+=defineGamer(&left_player_, buf[0]);
	human_count+=defineGamer(&right_player_, buf[1]);


	ships::Ship* ship_set[gamerules::SHIPS_COUNT];
	if (human_count) {
		if (human_count == 1) {
			decodeShipsArrange(buf, 42, ship_set);//если игрок один, он всегда справа
		}
		else if (human_count == 2) {
			decodeShipsArrange(buf, 2, ship_set);
			left_player_->arrangeShips(left_field_, ship_factory_, ship_set);

			decodeShipsArrange(buf, 42,  ship_set);
			right_player_->arrangeShips(right_field_, ship_factory_, ship_set);
		}
	}
	else {
		left_player_->arrangeShips(left_field_, ship_factory_, 0);
		right_player_->arrangeShips(right_field_, ship_factory_, 0);
	}
	
	


	


	



	/*std::srand(time(0));
	left_player_ = new RandomBot();
	left_player_->arrangeShips(left_field_, this->ship_factory_);
	right_player_ = new RandomBot();
	right_player_->arrangeShips(right_field_, this->ship_factory_);


	Gamer* first_player = left_player_;
	Gamer* second_player = right_player_;
	GameField* first_field = &left_field_;
	GameField* second_field = &right_field_;
	while (true) {
		Sleep(5000);
		system("cls");
		//left_field_.showField();
		//right_field_.showField();
		
		
		std::pair<u_char , u_char> shot = first_player->play(second_field);
		FieldCell* cell = second_field->getCell(shot.first, shot.second);
		if (cell->get_status() == gamerules::cellstate::SHIP) {
			cell->set_status(gamerules::cellstate::HIT);
			ships::Ship* ship = cell->get_ship();
			bool ship_status = ship->decreaseLife();
			std::cout << "Попал" << std::endl;
			first_player->setExtraShot(ship_status);
			if (!ship_status) {
				std::cout << "Уничтожил" << std::endl;
				char diff[4];
				diff[0] = static_cast<char>(ship->getTopXY().first) - 1;
				diff[1] = static_cast<char>(ship->getBottomXY().first) + 1;
				diff[2] = static_cast<char>(ship->getTopXY().second) - 1;
				diff[3] = static_cast<char>(ship->getBottomXY().second) + 1;
				second_field->fillCells(diff, gamerules::cellstate::USED);
				
				if (!second_player->decreaseShips()) {
					break;
				}
			}
			second_field->showField();
		}
		else {
			std::cout << "Мимо" << std::endl;
			first_player->setExtraShot(false);
			cell->set_status(gamerules::cellstate::USED);

			second_field->showField();


			std::swap(first_player, second_player);
			std::swap(first_field, second_field);
		}
	}
	left_field_.showField();
	right_field_.showField();*/
}


Game::~Game()
{


}
