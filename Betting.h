#pragma once
#include <iostream>
#include <conio.h>
#include <string.h>
#include <string>
#include "User.h"
#include "Database.h"

class Betting
{
public:
	double blueOdds = 0.0;
	double pinkOdds = 0.0;
	int bettingStatus = 0;
	Database* db;
	User* user;

	Betting(Database* db, User* user);
	void startBet();
	void placeBet(char input, int bet); //下注
	void showBetting(); //顯示目前賭盤狀態
	void endBetting(); //封盤
	void oddsCompute();
	void viewBoard();
	double floatControl(std::string input);
	int percentControl(std::string input, double number);
	bool isOpen();
};

bool Betting::isOpen() {
	auto data = this->db->Select("select * from `bettings`");
	
	if (data.size() > 0) {
		return true;
	}
	return false;
}

void Betting::viewBoard() {
	std::cout << "主題 : " << this->db->Select("select * from `bettings`")[0][1]["name"] << std::endl;

	this->oddsCompute();

	std::cout << "\n\n選擇下注方和輸入下注賭金\n";
	std::cout << "【B】lue 藍藍幫\n";
	std::cout << "【P】ink 粉紅幫\n";
	std::cout << "e.g. : B 100 \n";
}

void Betting::startBet()
{
	std::string tmpTheme;
	this->bettingStatus = 0;
	std::cout << "輸入賭盤主題 : ";
	std::cin >> tmpTheme;
	std::vector<std::pair<std::string, std::string>> tmpVector;
	tmpVector.push_back(std::pair<std::string, std::string>(std::string("name"), tmpTheme));

	this->db->InsertData("bettings", tmpVector);
}

Betting::Betting(Database* db,User* user)
{
	this->blueOdds = 0.0;
	this->pinkOdds = 0.0;
	this->db = db;
	this->user = user;
}


void Betting::placeBet(char input, int bet)
{
	if (this->bettingStatus == 0)
	{
		if (input == 'b' || input == 'B')
		{
			//this->blueBet += bet;
			std::vector<std::pair<std::string, std::string>> tmp;
			tmp.push_back(std::pair<std::string, std::string>("user_id", this->user->user[0][0]["id"]));
			tmp.push_back(std::pair<std::string, std::string>("betting_id", this->db->Select("select * from `bettings`")[0][0]["id"]));
			tmp.push_back(std::pair<std::string, std::string>("color", "blue"));
			tmp.push_back(std::pair<std::string, std::string>("bet", std::to_string(bet)));
			
			this->db->InsertData("betting_logs", tmp);
		}
		if (input == 'p' || input == 'P')
		{
			std::vector<std::pair<std::string, std::string>> tmp;
			tmp.push_back(std::pair<std::string, std::string>("user_id", this->user->user[0][0]["id"]));
			tmp.push_back(std::pair<std::string, std::string>("betting_id", this->db->Select("select * from `bettings`")[0][0]["id"]));
			tmp.push_back(std::pair<std::string, std::string>("color", "pink"));
			tmp.push_back(std::pair<std::string, std::string>("bet", std::to_string(bet)));

			this->db->InsertData("betting_logs", tmp);

			//this->pinkBet += bet;
		}

		std::vector<std::pair<std::string, std::string>> tmp;
		tmp.push_back(std::pair<std::string, std::string>("p_point", std::to_string(std::stoi((this->db->Select("select * from `users` where `id` = " + this->user->user[0][0]["id"]))[0][4]["p_point"]) - bet)));
		this->db->UpdateData("users",std::stoi(this->user->user[0][0]["id"]) , tmp);
	}
	else
	{
		std::cout << "已封盤 下次請早\n";
	}
}

void Betting::showBetting()
{
	std::cout << "藍藍幫總金額 : " << this->db->Select("select sum(`bet`) from `betting_logs` where `color` = 'blue'")[0][0]["sum(`bet`)"] << std::endl;
	std::cout << "藍藍幫賠率 : " << this->blueOdds << std::endl;
	std::cout << "粉紅幫總金額 : " << this->db->Select("select sum(`bet`) from `betting_logs` where `color` = 'pink'")[0][0]["sum(`bet`)"] << std::endl;
	std::cout << "粉紅幫賠率 : " << this->pinkOdds << std::endl;
}

void Betting::endBetting()
{
	this->bettingStatus = 1;
	this->oddsCompute();
	this->db->DeleteData("bettings", std::stoi(this->db->Select("select * from `bettings`")[0][0]["id"]));
}

void Betting::oddsCompute()
{
	double bluePercent = 0.0, pinkPercent = 0.0;
	std::string blue, pink;

	std::string tmpBlueBet = this->db->Select("select sum(`bet`) from `betting_logs` where `color` = 'blue'")[0][0]["sum(`bet`)"];
	std::string tmpPinkBet = this->db->Select("select sum(`bet`) from `betting_logs` where `color` = 'pink'")[0][0]["sum(`bet`)"];

	int blueBet = std::stoi((tmpBlueBet == "") ? "0" : tmpBlueBet);
	int pinkBet = std::stoi((tmpPinkBet == "") ? "0" : tmpPinkBet);
	int totalBet = blueBet + pinkBet;

	bluePercent = ((double)blueBet / totalBet) * 100.0;
	pinkPercent = ((double)pinkBet / totalBet) * 100.0;

	blue = std::to_string(bluePercent);
	pink = std::to_string(pinkPercent);

	bluePercent = ((double)percentControl(blue, bluePercent) / 100.0);
	pinkPercent = ((double)percentControl(pink, pinkPercent) / 100.0);

	blue = std::to_string(1.0 / bluePercent);
	pink = std::to_string(1.0 / pinkPercent);

	this->blueOdds = floatControl(blue);
	this->pinkOdds = floatControl(pink);

	int whoWin = std::rand() % 2; // 0 = blue win 1 = pink win

	if (this->bettingStatus == 1) {
		std::string betting_id = this->db->Select("select * from `bettings`")[0][0]["id"];
		auto data = this->db->Select("select * from `betting_logs` where `betting_id` = " + betting_id);

		for (auto d : data) {
			std::vector<std::pair<std::string, std::string>> tmp;
			
			if (whoWin == 0) {
				if (d[3]["color"] == "blue") {
					auto targetUser = this->db->Select("select * from `users` where `id` = " + d[1]["user_id"]);
					tmp.push_back(std::pair<std::string, std::string>("p_point", std::to_string((int)(std::stoi(targetUser[0][4]["p_point"]) + (std::stoi(d[4]["bet"]) * blueOdds)))));
					this->db->UpdateData("users", std::stoi(targetUser[0][0]["id"]), tmp);
				}
			}
			
			if (whoWin == 1) {
				if (d[3]["color"] == "pink") {
					auto targetUser = this->db->Select("select * from `users` where `id` = " + d[1]["user_id"]);
					tmp.push_back(std::pair<std::string, std::string>("p_point", std::to_string((int)(std::stoi(targetUser[0][4]["p_point"]) + (std::stoi(d[4]["bet"]) * pinkOdds)))));
					this->db->UpdateData("users", std::stoi(targetUser[0][0]["id"]), tmp);
				}
			}
		}
	}

	this->showBetting();
}

double Betting::floatControl(std::string input)
{
	std::string tmp = "";

	for (int i = 0; i < input.length(); i++)
	{
		tmp.push_back(input[i]);

		if (input[i] == '.')
		{
			tmp.push_back(input[i + 1]);
			tmp.push_back(input[i + 2]);
			break;
		}
	}

	return std::stod(tmp);
}

int Betting::percentControl(std::string input, double number)
{
	int check = 0;

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '.')
		{
			check = (input[i + 1] >= '5' ? 1 : 0);
			break;
		}
	}

	return (int)number + check;
}
    
