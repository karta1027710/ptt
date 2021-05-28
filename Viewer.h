#pragma once
#include <iostream>
#include <string>

class Viewer {
	public:
		void printMessage(std::string);
		void clearScreen();
};

void Viewer::printMessage(std::string str) {
	std::cout << str;
}

void Viewer::clearScreen() {
	system("cls");
}