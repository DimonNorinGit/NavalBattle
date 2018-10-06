#pragma once
#include"GameRules.h"
#include"Ship.h"

class FieldCell
{
	u_char state_;
	ships::Ship* ship_;
public:
	FieldCell();

	void set_status(u_char st);
	u_char get_status()const;
	void set_ship(ships::Ship* ship);
	ships::Ship* get_ship()const;
	~FieldCell();
};

