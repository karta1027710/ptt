#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Database.h"
#include "Viewer.h"


class User {
	public:
		std::vector<std::vector<std::map<std::string, std::string>>> user;
		Database* db;

		User(Database* db) {
			this->db = db;
		}

		bool login();

		int findUserId(std::string account);

		std::string getUserAccount(int user_id);

		bool insertUser(std::string account, std::string password);
};

bool User::login() {
	std::string account;
	std::string password;
	std::string sql = "select * from `users` where";

	std::cin >> account >> password;

	sql += " `account` = '" + account + "' and `password` = '" + password + "'";

	this->user = this->db->Select(sql);

	if (this->user.size() == 0) {
		return 0;
	}

	return 1;
}

int User::findUserId(std::string account) {
	std::string sql = "select * from `users` where `account` = '" + account + "'";

	auto data = this->db->Select(sql);

	if (data.size() == 0) {
		return -1;
	}

	return stoi(data[0][0]["id"]);
}

std::string User::getUserAccount(int user_id) {
	std::string sql = "select * from `users` where `id` = '" + std::to_string(user_id) + "'";

	auto data = this->db->Select(sql);

	if (data.size() == 0) {
		return "";
	}

	return data[0][1]["account"];
}

bool User::insertUser(std::string account, std::string password) {
	std::vector<std::pair<std::string, std::string>> data;
	data.push_back(std::pair < std::string, std::string >("account", account));
	data.push_back(std::pair < std::string, std::string >("password", password));
	data.push_back(std::pair < std::string, std::string >("level", "2"));

	if (!this->db->InsertData("users", data)) {
		return false;
	}

	return true;
}