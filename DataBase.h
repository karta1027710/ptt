#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <mysql.h>

class Database {
	public:
		MYSQL mysql;

		bool Connectdatabase();
		void FreeConnect();
		std::vector<std::vector<std::map<std::string, std::string>>> Select(std::string sqlCommand);  //查詢1
		std::vector<std::string> SelectColunm(std::string row);
		bool isExist(std::string row, std::string col, std::string value);																			  //bool QueryDatabase2();
		bool InsertData(std::string row, std::vector<std::pair<std::string,std::string>> data);
		bool UpdateData(std::string row, int id, std::vector<std::pair<std::string, std::string>> data);
		bool DeleteData(std::string row, int id);
		bool query(std::string sql);

		Database() {
			int isConnect = this->Connectdatabase();
			if (!isConnect) {
				this->FreeConnect();
				delete this;
			}
			else {
				mysql_query(&this->mysql, "set names utf8mb4");
			}
		}

		~Database() {
			this->FreeConnect();
		}
};

bool Database::Connectdatabase() {
	mysql_init(&this->mysql);

	if (!(mysql_real_connect(&this->mysql, "localhost", "root", "", "ptt", 0, NULL, 0)))
	{
		//printf("Error connecting to database:%s\n", mysql_error(&this->mysql));
		return false;
	}
	else
	{
		//printf("Connected...\n");
		return true;
	}
}

void Database::FreeConnect() {
	mysql_close(&this->mysql);
}

std::vector<std::vector<std::map<std::string, std::string>>> Database::Select(std::string sqlCommand) {
	MYSQL_FIELD* fd;
	MYSQL_RES* res;
	MYSQL_ROW column;

	std::vector<std::string> str_field;
	std::vector<std::vector<std::map<std::string,std::string>>> response;

	mysql_query(&this->mysql, "set names big5");

	if (mysql_query(&this->mysql, sqlCommand.c_str()))       
	{
		//printf("Query failed (%s)\n", mysql_error(&this->mysql));
		return response;
	}

	if (!(res = mysql_store_result(&this->mysql)))    
	{
		//printf("Couldn't get result from %s\n", mysql_error(&this->mysql));
		return response;
	}

	//打印數據行數
	//printf("number of dataline returned: %d\n", mysql_affected_rows(&this->mysql));

	while (fd = mysql_fetch_field(res)) {
		str_field.push_back(fd->name);
	}

	while (column = mysql_fetch_row(res))
	{
		std::vector<std::map<std::string, std::string>> tmpResponse;

		for (size_t i = 0; i < str_field.size(); i++) {
			std::map<std::string, std::string> tmp;
			tmp.insert(std::pair<std::string,std::string>(str_field[i], (column[i] == NULL) ? "" : column[i]));
			tmpResponse.push_back(tmp);
		}

		response.push_back(tmpResponse);
	}

	mysql_query(&this->mysql, "set names utf8mb4");

	mysql_free_result(res);

	return response;
}

std::vector<std::string> Database::SelectColunm(std::string row) {
	MYSQL_FIELD* fd;
	MYSQL_RES* res;

	std::vector<std::string> str_field;

	std::string sqlCommand = "select * from `" + row + '`';

	if (mysql_query(&this->mysql, sqlCommand.c_str()))
	{
		//printf("Query failed (%s)\n", mysql_error(&this->mysql));
		return str_field;
	}

	if (!(res = mysql_store_result(&this->mysql)))
	{
		//printf("Couldn't get result from %s\n", mysql_error(&this->mysql));
		return str_field;
	}

	while (fd = mysql_fetch_field(res)) {
		str_field.push_back(fd->name);
	}

	mysql_free_result(res);

	return str_field;
}

bool Database::isExist(std::string row, std::string col, std::string value) {
	MYSQL_RES* res;

	std::string sql = "select * from `" + row + "` where `" + col + "` = '" + value + "'";

	if (mysql_query(&this->mysql, sql.c_str()))
	{
		//printf("Query failed (%s)\n", mysql_error(&this->mysql));
		return true;
	}

	if (!(res = mysql_store_result(&this->mysql)))
	{
		//printf("Couldn't get result from %s\n", mysql_error(&this->mysql));
		return true;
	}

	if (mysql_affected_rows(&this->mysql) > 0) {
		return true;
	}

	mysql_free_result(res);

	return false;
}

bool Database::InsertData(std::string row, std::vector<std::pair<std::string, std::string>> data) {
	std::string sql = "insert  `" + row + "` set ";

	mysql_query(&this->mysql, "set names big5");

	for (size_t i = 0; i < data.size(); i++) {
		if (i != data.size() - 1) {
			sql += "`" + data[i].first + "` = '" + data[i].second + "',";
		}
		else {
			sql += "`" + data[i].first + "` = '" + data[i].second + "'";
		}
	}

	if (mysql_query(&this->mysql, sql.c_str())){
		return false;
	}

	mysql_query(&this->mysql, "set names utf8mb4");

	return true;
}

bool Database::UpdateData(std::string row,int id ,std::vector<std::pair<std::string, std::string>> data) {
	std::string sql = "update  `" + row + "` set ";

	mysql_query(&this->mysql, "set names big5");

	for (size_t i = 0; i < data.size(); i++) {
		if (i != data.size() - 1) {
			sql += "`" + data[i].first + "` = '" + data[i].second + "',";
		}
		else {
			sql += "`" + data[i].first + "` = '" + data[i].second + "'";
		}
	}

	sql += " where `id` = " + std::to_string(id);

	if (mysql_query(&this->mysql, sql.c_str())) {
		return false;
	}

	mysql_query(&this->mysql, "set names utf8mb4");

	return true;
}

bool Database::DeleteData(std::string row, int id) {
	std::string sql = "delete from  `" + row + "` where `id` = " + std::to_string(id);

	if (mysql_query(&this->mysql, sql.c_str())) {
		return false;
	}

	return true;
}

bool Database::query(std::string sql) {
	if (mysql_query(&this->mysql, sql.c_str())) {
		return false;
	}

	return true;
}