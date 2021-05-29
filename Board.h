#pragma once
#include <string>
#include <vector>
#include <map>
#include "Viewer.h"
#include "Database.h"


class Board {
	public:
		Database* db;

		Board(Database* db) {
			this->db = db;
		}

		std::vector<std::vector<std::map<std::string, std::string>>> getAllBoard();

		std::vector<std::vector<std::map<std::string, std::string>>> getAllPost();

		std::vector<std::vector<std::map<std::string, std::string>>> getUserPost(int user_id);

		std::vector<std::string> getBoardAllColunm();

		std::vector<std::string> getPostAllColunm();

		bool boardNameIsExist(std::string name);

		bool insertBoard(std::string name, std::string className, std::string title, int boardAdmin);
		
		bool updateBoard(std::string name, std::string className, std::string title, int boardAdmin, int id);
	
		bool deleteBoard(int id);

		bool insertPost(int board_id, int user_id, std::string title, std::string text);

		bool updatePost(int post_id, std::string title, std::string text);

		bool deletePost(int post_id);
};

std::vector<std::vector<std::map<std::string, std::string>>> Board::getAllBoard() {
	return this->db->Select("select * from `boards`");
}

std::vector<std::vector<std::map<std::string, std::string>>> Board::getUserPost(int user_id) {
	auto posts = this->db->Select("select * from `posts` where `user_id` = " + std::to_string(user_id));
	
	for (auto post : posts) {
		post[1]["board_id"] = this->db->Select("select * from `boards` where `id` = " + post[1]["board_id"])[0][2]["name"];
	}

	return posts;
}

std::vector<std::string> Board::getBoardAllColunm() {
	return this->db->SelectColunm("boards");
}

std::vector<std::string> Board::getPostAllColunm() {
	return this->db->SelectColunm("posts");
}

bool Board::boardNameIsExist(std::string name) {
	if (this->db->isExist("boards", "name", name)) {
		return true;
	}
	return false;
}

bool Board::insertBoard(std::string name, std::string className, std::string title, int boardAdmin) {
	std::vector<std::pair<std::string, std::string>> data;
	
	data.push_back(std::pair<std::string, std::string>("name", name));
	data.push_back(std::pair<std::string, std::string>("class", className));
	data.push_back(std::pair<std::string, std::string>("title", title));
	if (boardAdmin != -1) {
		data.push_back(std::pair<std::string, std::string>("user_id",std::to_string(boardAdmin)));
	}

	if (this->db->InsertData("boards", data)) {
		return true;
	}

	return false;
}

bool Board::updateBoard(std::string name, std::string className, std::string title, int boardAdmin,int id) {
	std::vector<std::pair<std::string, std::string>> data;

	data.push_back(std::pair<std::string, std::string>("name", name));
	data.push_back(std::pair<std::string, std::string>("class", className));
	data.push_back(std::pair<std::string, std::string>("title", title));
	if (boardAdmin != -1) {
		data.push_back(std::pair<std::string, std::string>("user_id", std::to_string(boardAdmin)));
	}

	if (this->db->UpdateData("boards",id , data)) {
		return true;
	}

	return false;
}

bool Board::deleteBoard(int id) {
	if (this->db->DeleteData("boards", id)) {
		return true;
	}

	return false;
}

std::vector<std::vector<std::map<std::string, std::string>>> Board::getAllPost() {
	return this->db->Select("select * from `posts`");
}

bool Board::insertPost(int board_id, int user_id, std::string title, std::string text) {
	std::vector<std::pair<std::string, std::string>> data;

	data.push_back(std::pair<std::string, std::string>("board_id", std::to_string(board_id)));
	data.push_back(std::pair<std::string, std::string>("user_id", std::to_string(user_id)));
	data.push_back(std::pair<std::string, std::string>("title", title));
	data.push_back(std::pair<std::string, std::string>("text", text));

	if (this->db->InsertData("posts", data)) {
		return true;
	}

	return false;
}

bool Board::updatePost(int post_id, std::string title, std::string text) {
	std::vector<std::pair<std::string, std::string>> data;

	data.push_back(std::pair<std::string, std::string>("title", title));
	data.push_back(std::pair<std::string, std::string>("text", text));

	if (this->db->UpdateData("posts", post_id, data)) {
		return true;
	}

	return false;
}

bool Board::deletePost(int post_id) {
	if (this->db->DeleteData("posts", post_id)) {
		return true;
	}

	return false;
}