#include"Game.h"
#include<locale.h>
/*class A {

private:

public:

	virtual void get() {
		std::cout << "Helo";
	}
};

class B : public A {
private:
	int data = 0;
public:
	void get() {
		A::get();
		std::cout << ":" << data;
	}
};*/






int main() {
	setlocale(LC_ALL, "Russian");
	Game game;
	game.start();
	


	system("pause");
	return 0;
}