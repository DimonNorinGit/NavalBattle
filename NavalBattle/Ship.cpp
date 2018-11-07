#include "Ship.h"

using namespace ships;



Ship::Ship(u_char life)
{
	status_ = true;
	life_ = life;
	len = life;
}

std::pair<u_char, u_char> Ship::getTopXY()const {
	return std::make_pair(this->top_x, this->top_y);
}
std::pair<u_char, u_char> Ship::getBottomXY()const {
	return std::make_pair(this->bot_x, this->bot_y);
}

void Ship::setPos(u_char top_x, u_char top_y, u_char bot_x, u_char bot_y) {
	this->top_x = top_x;
	this->top_y = top_y;
	this->bot_x = bot_x;
	this->bot_y = bot_y;
}


u_char Ship::getLength()const {
	return len;
}

void Ship::destroy() {
	//some event
}

bool Ship::decreaseLife() {
	if (life_ == 0) return status_;
	--life_;
	if (life_ == 0) {
		//destroy();
		status_ = false;
	}
	return status_;
}

bool Ship::getStatus()const
{
	return status_;
}

Ship::~Ship()
{
}


OneDeck::OneDeck() : Ship(1)
{

}

TwoDeck::TwoDeck() : Ship(2)
{

}

ThreeDeck::ThreeDeck() : Ship(3)
{

}

FourDeck::FourDeck() : Ship(4)
{

}