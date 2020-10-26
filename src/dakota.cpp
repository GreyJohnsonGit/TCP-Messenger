#include "Dakota.h"

#include <iostream>

Dakota::Dakota(std::string _name) {
	name = _name;
}

void Dakota::print() {
	std::cout << this->name << std::endl;
}
