#pragma once
#include <string>
#include <vector>
#include <map>
#include "Viewer.h"
#include "Database.h"

class Mail {
	public:
		Database* db;

		Mail(Database* db) {
			this->db = db;
		}

		std::vector<std::vector<std::map<std::string, std::string>>> getMail(int user_id);

		std::vector<std::vector<std::map<std::string, std::string>>> getOneMail(int mail_id);

		bool sendMail(int send_id, int recipient_id, std::string title, std::string text);
};

std::vector<std::vector<std::map<std::string, std::string>>> Mail::getMail(int user_id) {
	std::string sql = "select * from `mails` where `recipient_id` = " + std::to_string(user_id);

	auto data = this->db->Select(sql);

	return data;
}

std::vector<std::vector<std::map<std::string, std::string>>> Mail::getOneMail(int mail_id) {
	std::string sql = "select * from `mails` where `id` = " + std::to_string(mail_id);

	auto data = this->db->Select(sql);

	return data;
}

bool Mail::sendMail(int send_id, int recipient_id, std::string title, std::string text) {
	std::vector<std::pair<std::string, std::string>> data;

	data.push_back(std::pair<std::string, std::string>("send_id", std::to_string(send_id)));
	data.push_back(std::pair<std::string, std::string>("recipient_id", std::to_string(recipient_id)));
	data.push_back(std::pair<std::string, std::string>("title", title));
	data.push_back(std::pair<std::string, std::string>("text", text));

	if (this->db->InsertData("mails", data)) {
		return true;
	}

	return false;
}