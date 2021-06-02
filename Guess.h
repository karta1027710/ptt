
#pragma once
#include"Viewer.h"
#include <iostream>
#include <ctime>
#include <windows.h>
Viewer viewerG;
class Guess
{
public:

	int answer;
	int leftpoint;
	int rightpoint;
	bool gameStatus;
	Guess();
	void startGame();
	void guessing();
private:

};

Guess::Guess()
{
	this->answer = 0;
	this->leftpoint = 1;
	this->rightpoint = 1000;
	this->gameStatus = true;
}

void Guess::startGame()
{
	srand(time(NULL));

	this->answer = ((rand() % 1000) + 1);

	this->guessing();
}

void Guess::guessing()
{
	system("cls");
	viewerG.printPTT();
	int input;

	std::cout << "猜數字 : " << this->leftpoint << " ~ " << this->rightpoint << std::endl;

	std::cout << "輸入 : ";
	std::cin >> input;

	if (input < this->leftpoint || input > this->rightpoint)
	{
		std::cout << "超出範圍，重新輸入\n";
		Sleep(500);
		this->guessing();
	}
	else if (input < this->answer)
	{
		this->leftpoint = input;

		this->guessing();
	}
	else if (input > this->answer)
	{
		this->rightpoint = input;

		this->guessing();
	}
	else
	{
		std::cout << "正解 !!!\n";
		this->gameStatus = false;
	}
}