#include <cstdlib>
#include <iostream>
#include <ctime>


void criarAvo(int level) {

	std::srand(std::time(nullptr));

	int chance = std::rand() % 10 + 1;

	if(chance <= level) {
		std::cout << "apareceu" << std::endl;
	} else {
		std::cout << "nao apareceu" << std::endl;
	}

}