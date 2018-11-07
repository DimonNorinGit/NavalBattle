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
		int data_i = buf_diff + ship_n * 4;
		char top_x = buf[data_i];
		char top_y = buf[data_i + 1];
		char bot_x = buf[data_i + 2];
		char bot_y = buf[data_i + 3];

		char v_size = std::abs(top_y - bot_y);
		char g_size = std::abs(top_x - bot_x);

		int ship_type = v_size > g_size ? v_size : g_size;

		ships::Ship* ship = ship_factory_.get_ship(ships::SHIPS_TYPE(ship_type));
		ship->setPos(top_x, top_y, bot_x, bot_y);
		ship_set[ship_n] = ship;
	}

}

void Game::setShipSet(ships::Ship** ship_set) {
	u_char ships_count[] = { gamerules::SHIPS_SET::_one_deck,gamerules::SHIPS_SET::_two_deck,
							gamerules::SHIPS_SET::_three_deck, gamerules::SHIPS_SET::_four_deck };
	ships::SHIPS_TYPE ship_type[] = { ships::SHIPS_TYPE::ONE_DECK , ships::SHIPS_TYPE::TWO_DECK ,
							ships::SHIPS_TYPE::THREE_DECK , ships::SHIPS_TYPE::FOUR_DECK };
	u_char diff = 0;
	for (u_char c = 0; c < 4; ++c) {
		for (u_char s = 0; s < ships_count[c]; ++s) {
			ship_set[diff  + s] = ship_factory_.get_ship(ship_type[c]);
		}
		diff+=ships_count[c];
	}
}


void Game::packFieldStates(char* buf, int diff ,  GameField& field) {

	u_char field_size = gamerules::FIELD_SIZE;
	int buf_diff = diff;
	for (u_char x = 0; x < field_size; ++x) {
		for (u_char y = 0; y < field_size; ++y) {
			FieldCell* cell = field.getCell(x, y);
			if (cell->get_status() == gamerules::cellstate::SHIP) {
				buf[buf_diff++] = x;
				buf[buf_diff++] = y;
			}
		}
	}
	std::cout << "??" << buf_diff << "??";
}

void Game::prepareStage() {

	SOCKET sConnect = accept(sListen_, (SOCKADDR*)&addr_, &addrlen_);

	if (sConnect == 0) {
		std::cout << "Connection failed\n";
		system("pause");
	}

	const int rbuf_len = 82;
	char rbuf[rbuf_len];

	recv(sConnect, rbuf, rbuf_len, 0);
	//closesocket(sConnect);

	/*for (int b = 0; b < rbuf_len; ++b) {
		std::cout << int(rbuf[b]) << " ";
	}
	std::cout << std::endl;*/

	//system("pause");

	u_char human_count = 0;
	human_count += defineGamer(&left_player_, rbuf[0]);
	human_count += defineGamer(&right_player_, rbuf[1]);

	//buf->recive:    game_type player_field    (player_field2 or rubish)
	//buf->send:      field1_ship's_cells  field2_ship's_cells
	//                      40 bytes            40 bytes
	ships::Ship* ship_set[gamerules::SHIPS_COUNT];
	if (human_count) {
		if (human_count == 1) {
			decodeShipsArrange(rbuf, 2, ship_set);//���� ����� ����, �� ������ �����
			left_player_->arrangeShips(left_field_, ship_set);
			setShipSet(ship_set);
			right_player_->arrangeShips(right_field_, ship_set);
		}
		else if (human_count == 2) {
			decodeShipsArrange(rbuf, 2, ship_set);
			left_player_->arrangeShips(left_field_, ship_set);

			decodeShipsArrange(rbuf, 42, ship_set);
			right_player_->arrangeShips(right_field_, ship_set);
		}
	}
	else {
		setShipSet(ship_set);
		left_player_->arrangeShips(left_field_, ship_set);
		setShipSet(ship_set);
		right_player_->arrangeShips(right_field_, ship_set);
	}

	const int sbuf_len = 80;
	char sbuf[sbuf_len];
	
	packFieldStates(sbuf, 0, left_field_);
	packFieldStates(sbuf, 40, right_field_);

	left_field_.showField();
	right_field_.showField();

	send(sConnect, sbuf, sbuf_len, 0);
	closesocket(sConnect);
}



void Game::packCells(char* diff, char* buf , GameField& field , int buf_d) {
	u_char field_size = gamerules::FIELD_SIZE;
	u_char cells_count = 0;

	int buf_diff = buf_d;
	for (char x = diff[0]; x <= diff[1]; ++x) {
		for (char y = diff[2]; y <= diff[3]; ++y) {
			if (x >= 0 && x < field_size && y >= 0 && y < field_size) {
				FieldCell* cell = field.getCell(x, y);
				u_char cell_status = cell->get_status();
				if (cell_status == gamerules::cellstate::HIT || cell_status == gamerules::cellstate::USED) {
					continue;
				}
				buf[buf_diff++] = x;
				buf[buf_diff++] = y;
				cells_count++;
				//std::cout << "---" << int(x) << ' ' << int(y) << std::endl;
			}
		}
	}
	buf[5] = cells_count;//for client
	//std::cout << "-----" << int(cells_count) << "-------";
}


void Game::gameStage() {

	const int rbuf_len = 3;
	char rbuf[rbuf_len];
	
	//1 + 1 + 1 + 1 + 1 + 14
	const int sbuf_len = 34;
	char sbuf[sbuf_len];//game_state + ship_state + ship_type + x + y + cells_count + fill_cells 
	

	Gamer* previos_gamer = left_player_;
	GameField* previous_field = &right_field_;

	Gamer* current_gamer = right_player_;
	GameField* current_field = &left_field_;

	bool isGameEnd = false;
	while (!isGameEnd) {

		SOCKET sConnect = accept(sListen_, (SOCKADDR*)&addr_, &addrlen_);

		recv(sConnect , rbuf, rbuf_len , 0);
		std::cout << rbuf;


		std::pair<u_char, u_char> shot = current_gamer->play(current_field, rbuf);

		FieldCell* cell = current_field->getCell(shot.first, shot.second);

		
		//add check for errors 

		//game_state + ship_state + ship_type + x + y + cells_count + fill_cells 

		bool isExtraShot = false;

		sbuf[3] = shot.first;//shot_x
		sbuf[4] = shot.second;//shot_y
		sbuf[0] = 'c';//set game_state: continue game
		sbuf[1] = 'm';//miss
		sbuf[5] = 0;//��� ������ ��� ����������
		if (cell->get_status() == gamerules::cellstate::SHIP) {
			sbuf[1] = 'h';//set ship_state: hit
			isExtraShot = true;
			//current_gamer->setExtraShot(true);
			

			cell->set_status(gamerules::cellstate::HIT);
			ships::Ship* ship = cell->get_ship();
			bool ship_status = ship->decreaseLife();
			std::cout << "�����" << std::endl;

			if (!ship_status) {
				//�������� ���� �� ����������� �������
				sbuf[1] = 'd';//set ship_state: destroy
				current_gamer->setShipStatus(false);

				//////////////////////////////////
				//sbuf[2] = ship->getType()
				//////////////////////////////////

				std::cout << "���������" << std::endl;
				char diff[4];
				diff[0] = static_cast<char>(ship->getTopXY().first) - 1;
				diff[1] = static_cast<char>(ship->getBottomXY().first) + 1;
				diff[2] = static_cast<char>(ship->getTopXY().second) - 1;
				diff[3] = static_cast<char>(ship->getBottomXY().second) + 1;

				packCells(diff, sbuf, *current_field, 6);

				current_field->fillCells(diff, gamerules::cellstate::USED);

				//packCells()


				if (!previos_gamer->decreaseShips()) {
					//end game
					//than add cheker for which player won
					sbuf[0] = 'e';//end game
					isGameEnd = true;
				}
			}
			else {
				current_gamer->setShipStatus(true);
			}
		}
		else {
			std::cout << "����" << std::endl;
			//current_gamer->setExtraShot(false);
			cell->set_status(gamerules::cellstate::USED);
		}


		send(sConnect, sbuf, sbuf_len , 0);//send data

		if (!isExtraShot) {
			std::swap(previos_gamer, current_gamer);
			std::swap(previous_field, current_field);
		}
	}


	delete left_player_;
	delete right_player_;


	}


void Game::initGame() {

}


void Game::start() {

	sListen_ = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen_, (SOCKADDR*)&addr_, sizeof(addr_));

	listen(sListen_, 1);//SOMAXCONN
	const int rbuf_len = 1;
	char rbuf[rbuf_len];

	while (this->isWork_) {
		SOCKET sConnect = accept(sListen_, (SOCKADDR*)&addr_, &addrlen_);
		recv(sListen_, rbuf, rbuf_len, 0);
		if (rbuf[0] == 'b') {

		}
		else if (rbuf[0] == 's') {

		}
		else if (rbuf[0] == 'e') {
			exit(0);
		}
		std::cout << "Connect" << std::endl;

		prepareStage();
		gameStage();




	}

}
	


	//left_field_.showField();

	//right_field_.showField();


	


Game::~Game()
{


}
