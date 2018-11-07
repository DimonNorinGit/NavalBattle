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



#include<list>


int main() {
	setlocale(LC_ALL, "Russian");
	std::list<std::pair<char, char>> shot_var_{ { 0 , 1 } ,{ 1 , 0 } ,{ -1 , 0 } ,{ 0 , -1 } };
	std::list<std::pair<char, char>> shot_var_2 = shot_var_;
	for (auto n : shot_var_) {
		std::cout << int(n.first) << ":" << int(n.second) << std::endl;
	}
	shot_var_2.remove(*shot_var_.begin());

	for (auto n : shot_var_) {
		std::cout << int(n.first) << ":" << int(n.second) << std::endl;
	}




	Game game;
	game.start();
	int arr[] = { 1,2,2 };
	std::list<int> l1{ 1,2,2 };
	std::list<int> l(l1);
	
	
	return 0;
}