#include "Game.h"



Game::Game()
{
	left_player_ = nullptr;
	right_player_ = nullptr;
}



void Game::start() {
	left_player_ = new RandomBot();

	left_player_->arrangeShips(this->left_field_, this->ship_factory_);
	this->left_field_.showField();

	right_player_ = new RandomBot();
	right_player_->arrangeShips(this->right_field_, this->ship_factory_);
	this->right_field_.showField();
}


Game::~Game()
{


}
