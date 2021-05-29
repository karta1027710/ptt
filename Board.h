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

		std::vector<std::vector<std::map<std::string, std::string>>> getAllPost(int board_id);

		std::vector<std::vector<std::map<std::string, std::string>>> getUserPost(int user_id);

		std::vector<std::vector<std::map<std::string, std::string>>> getOnePost(int post_id);

		std::vector<std::vector<std::map<std::string, std::string>>> getOnePostComment(int post_id);

		std::vector<std::string> getBoardAllColunm();

		std::vector<std::string> getPostAllColunm();

		int getBoardId(int post_id);

		bool boardNameIsExist(std::string name);

		bool insertBoard(std::string name, std::string className, std::string title, int boardAdmin);
		
		bool updateBoard(std::string name, std::string className, std::string title, int boardAdmin, int id);
	
		bool deleteBoard(int id);

		bool insertPost(int board_id, int user_id, std::string title, std::string text);

		bool updatePost(int post_id, std::string title, std::string text);

		bool deletePost(int post_id);

		bool isLeavedComment(int post_id, int user_id);

		bool insertComment(int post_id, int user_id, int action, std::string text);
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

std::vector<std::vector<std::map<std::string, std::string>>> Board::getOnePost(int post_id) {
	auto post = this->db->Select("select * from `posts` where `id` = " + std::to_string(post_id));

	post[0][1]["board_id"] = this->db->Select("select * from `boards` where `id` = " + post[0][1]["board_id"])[0][2]["name"];

	return post;
}

std::vector<std::vector<std::map<std::string, std::string>>> Board::getOnePostComment(int post_id) {
	auto comments = this->db->Select("select * from `comments` where `post_id` = " + std::to_string(post_id));

	return comments;
}

std::vector<std::string> Board::getBoardAllColunm() {
	return this->db->SelectColunm("boards");
}

std::vector<std::string> Board::getPostAllColunm() {
	return this->db->SelectColunm("posts");
}

int Board::getBoardId(int post_id) {
	auto data = this->db->Select("select * from `posts` where `id` = " + std::to_string(post_id));

	return std::stoi(data[0][1]["board_id"]);
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

std::vector<std::vector<std::map<std::string, std::string>>> Board::getAllPost(int board_id) {
	return this->db->Select("select * from `posts` where `board_id` = " + std::to_string(board_id));
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

bool Board::isLeavedComment(int post_id, int user_id) {
	std::string sql = "select * from `comments` where `post_id` = " + std::to_string(post_id) + " and `user_id` = " + std::to_string(user_id);

	auto data = this->db->Select(sql);

	if (data.size() > 0) {
		return true;
	}

	return false;
}

bool Board::insertComment(int post_id, int user_id, int action, std::string text) {
	std::vector<std::pair<std::string, std::string>> data;

	data.push_back(std::pair<std::string, std::string>("post_id", std::to_string(post_id)));
	data.push_back(std::pair<std::string, std::string>("user_id", std::to_string(user_id)));
	data.push_back(std::pair<std::string, std::string>("action", std::to_string(action)));
	data.push_back(std::pair<std::string, std::string>("text", text));

	if (this->db->InsertData("comments", data)) {
		return true;
	}

	return false;
}