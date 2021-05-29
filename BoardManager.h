#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "User.h"
#include "Board.h"
#include "Viewer.h"
#include "Database.h"


class BoardManager {
	public:
		Database* db = new Database;
		Viewer viewer;
		Board board = Board(this->db);
		User user = User(this->db);

		void loginMenu(int);
		void registerAccount();
		void login(int status);
		void mainMenu(int index);
		void adminManagerBoard(int index);
		void adminInsertBoard();
		void adminEditBoard(int index);
		void adminDeleteBoard(int index);

		void viewAllBoard(int index);

		void viewAllPost(int board_id, int boardIndex);

		void viewInsertPost(int index);

		void viewEditPost(int index);

		void viewDeletePost(int index);
};

void BoardManager::loginMenu(int status/*判斷輸入無效指令*/) {
	this->viewer.LoginMenu(status);
	std::string input;
	std::cin >> input;

	if (input == "/login") {
		system("cls");
		this->login(0);
		return;
	}

	if (input == "/register") {
		this->viewer.clearScreen();
		this->registerAccount();
		return;
	}
	system("cls");
	this->loginMenu(1);
	
	return;
}

void BoardManager::registerAccount() {
	std::string account, password, confirmPassword;

	viewer.signUp();

	this->viewer.printMessage("輸入帳號: ");
	std::cin >> account;

	if (this->user.findUserId(account) != -1) {
		this->viewer.printMessage("\n帳號重複\n");
		this->registerAccount();
		return;
	}

	this->viewer.printMessage("\n輸入密碼: ");
	std::cin >> password;

	this->viewer.printMessage("\n再次確認密碼: ");
	std::cin >> confirmPassword;

	if (password != confirmPassword) {
		this->viewer.printMessage("\n密碼不一致\n");
		this->registerAccount();
		return;
	}

	if (!this->user.insertUser(account, password)) {
		this->viewer.printMessage("\n註冊帳號發生錯誤，請稍後再試\n");
		this->registerAccount();
		return;
	}

	this->viewer.printMessage("\n註冊成功，3秒後跳回登入畫面\n");
	Sleep(3000);
	this->login(0);
	return;
}

/// <summary>
/// 登入 更改viewer地方就好
/// </summary>
void BoardManager::login(int status) {
	if (status == 0)this->viewer.Login();
	else this->viewer.reLogin();

	int isLogin = 0;
	isLogin = this->user.login();

	if (!isLogin) {
		this->viewer.clearScreen();
		this->login(1);
		return;
	}

	this->viewer.clearScreen();
	this->viewer.printMessage("歡迎進入PTT\n");

	std::string name = this->user.user[0][1]["account"];
	this->viewer.printMessage("歡迎 " + name + "\n");

	this->mainMenu(1);
}

/// <summary>
/// 主選單 靠輸入開頭來切換頁面
/// </summary>
void BoardManager::mainMenu(int index) {
	/* 改這邊的viewer主菜單就可以了*/
	if (this->user.user[0][3]["level"] == "1") {
		viewer.adminMainMenu(index);
		/*std::cout << index << '\n';
		this->viewer.printMessage("管理員功能介面\n");
		this->viewer.printMessage("ManagerBoard\t【管理看板】\n");
		this->viewer.printMessage("Announce    \t【所有看板】\n");
		this->viewer.printMessage("WritePost   \t【新增文章】\n");
		this->viewer.printMessage("Mail        \t【信    箱】\n");*/

		char input = _getch();
		input = _getch();
		system("cls");
		switch (input)
		{
			case 72: //上
				if (index > 1) {
					index--;
				}
				else if (index == 1)//跳到最後一行
				{
					index = 6;
				}
				this->mainMenu(index);
				break;
			case 80: //下
				if (index < 7) {
					index++;
				}
				else if (index == 7)//跳到第一行
				{
					index = 1;
				}
				this->mainMenu(index);
				break;
			case 77: //右
				switch (index)
				{
					case 1:
						this->adminManagerBoard(1);
						break;
					case 2:
						this->viewAllBoard(1);
						break;
					case 3:
						this->viewInsertPost(1);
						break;
					case 4:
						this->viewEditPost(1);
						break;
					case 5:
						this->viewDeletePost(1);
						break;
					default:
						this->mainMenu(1);
						break;
				}
				break;
			case 75: //左
				this->loginMenu(0);
				break;
			default:
				this->mainMenu(1);
				break;
		}
	}
	else if(this->user.user[0][3]["level"] == "2"){
		this->viewer.printMessage("一般會員介面\n");
		this->viewer.printMessage("Announce    \t【所有看板】\n");
		this->viewer.printMessage("WritePost   \t【新增文章】\n");
		this->viewer.printMessage("Mail        \t【信箱】\n");

		char input = _getch();
		input = _getch();

	}

	return;
}

/// <summary>
/// 顯示全部看板
/// </summary>
void BoardManager::viewAllBoard(int index) {
	this->viewer.clearScreen();

	//std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> allBoard = this->board.getAllBoard();
	std::vector<std::string> boardColumn = this->board.getBoardAllColunm();
	viewer.allBoard(allBoard, boardColumn, index);
	/*for (auto board : allBoard) {
		for (size_t i = 2; i < boardColumn.size();i++) {
			this->viewer.printMessage(board[i][boardColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}*/

	char input = _getch();
	input = _getch();

	switch (input)
	{
		case 72: //上
			if (index > 1) {
				index--;
			}
			else if (index == 1)
			{
				index = allBoard.size();
			}
			this->viewAllBoard(index);
			break;
		case 80: //下
			if (index < allBoard.size()) {
				index++;
			}
			else if (index == allBoard.size())
			{
				index = 1;
			}
			this->viewAllBoard(index);
			break;
		case 77: //右
			this->viewAllPost(std::stoi(allBoard[index-1][0]["id"]), index);
			break;
		case 75: //左
			system("cls");
			this->mainMenu(1);
			break;
		default:
			this->viewAllBoard(1);
			break;
	}

	return;
}

/// <summary>
/// 管理員管理看板 靠輸入開頭來切換頁面
/// </summary>
void BoardManager::adminManagerBoard(int index) {
	/*改這邊就是管理看板*/
	/*std::cout << index << '\n';
	this->viewer.printMessage("管理看板\n");
	this->viewer.printMessage("InsertBoard\t【新增看板】\n");
	this->viewer.printMessage("EditBoard  \t【編輯看板】\n");
	this->viewer.printMessage("DeleteBoard\t【刪除看板】\n");*/
	viewer.adminManageBoard(index);
	char input = _getch();
	input = _getch();
	system("cls");
	switch (input)
	{
		case 72: //上
			if (index > 1) {
				index--;
			}
			else if (index == 1)
			{
				index = 3;
			}
			this->adminManagerBoard(index);
			break;
		case 80: //下
			if (index < 3) {
				index++;
			}
			else if (index == 3)
			{
				index = 1;
			}
			this->adminManagerBoard(index);
			break;
		case 77: //右
			switch (index)
			{
			case 1:
				this->adminInsertBoard();
				break;
			case 2:
				this->adminEditBoard(0);
				break;
			case 3:
				this->adminDeleteBoard(0);
				break;
			default:
				break;
			}
			break;
		case 75: //左
			system("cls");
			this->mainMenu(1);
			break;
		default:
			this->adminManagerBoard(1);
			break;
	}

	return;
}

/// <summary>
/// 管理員新增看板
/// 如果看板名稱重複會繼續迴圈
/// 看板管理員如果沒找到也是繼續迴圈
/// 這邊畫面有錯就刷新
/// 
/// 成功的話3秒會跳回管理員主選單
/// </summary>
void BoardManager::adminInsertBoard() {
	std::string name;
	std::string className;
	std::string title;
	std::string userAccount;
	int user_id = -1;

	this->viewer.clearScreen();
	this->viewer.printMessage("新增看板\n");
	
	while (true) {
		this->viewer.printMessage("返回請輸入/back\n");
		this->viewer.printMessage("輸入看板名稱: ");

		std::cin >> name;

		if (name == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		if (this->board.boardNameIsExist(name)) {
			this->viewer.printMessage("\n看板名稱重複\n");
			continue;
		}

		this->viewer.printMessage("\n輸入看板類別: ");

		std::cin >> className;

		if (className == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		this->viewer.printMessage("\n輸入看板標題: ");

		std::cin >> title;

		if (title == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		this->viewer.printMessage("\n設定看板管理員帳號(若無請輸入 0): ");

		std::cin >> userAccount;

		if (userAccount == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		if (userAccount != "0") {
			user_id = this->user.findUserId(userAccount);

			if (user_id == -1) {
				this->viewer.printMessage("\n查無看板管理員帳號\n");
				continue;
			}
		}

		break;
	}
	
	if (!this->board.insertBoard(name, className, title, user_id)) {
		this->viewer.printMessage("\n新增看板發生錯誤，稍後再試");
		this->adminManagerBoard(1);
		return;
	}

	this->viewer.printMessage("\n新增成功，3秒後跳轉回管理員選單");
	Sleep(3000);
	this->viewer.clearScreen();
	this->adminManagerBoard(1);
	return;
}

/// <summary>
/// 管理員編輯看板
/// </summary>
void BoardManager::adminEditBoard(int index) {
	this->viewer.clearScreen();
	//std::cout << index << '\n';
	std::vector<std::vector<std::map<std::string, std::string>>> allBoard = this->board.getAllBoard();
	std::vector<std::string> boardColumn = this->board.getBoardAllColunm();

	/*for (auto board : allBoard) {
		for (size_t i = 0; i < boardColumn.size(); i++) {
			this->viewer.printMessage(board[i][boardColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}*/
	viewer.allBoard(allBoard, boardColumn, index+1);
	char input = _getch();
	input = _getch();

	std::string name;// = allBoard[index][2][boardColumn[2]];
	std::string className;// = allBoard[index][3][boardColumn[3]];
	std::string title;// = allBoard[index][4][boardColumn[4]];
	std::string userAccount;
	int user_id = -1;// = stoi(allBoard[index][1][boardColumn[1]]);

	switch (input)
	{
		case 72: //上
			if (index > 0) {
				index--;
			}
			else if (index == 0)
			{
				index = allBoard.size();
			}
			this->adminEditBoard(index);
			break;
		case 80: //下
			if (index < allBoard.size() - 1) {
				index++;
			}
			else if (index == allBoard.size()-1)
			{
				index = 0;
			}
			this->adminEditBoard(index);
			break;
		case 77: //右
			while (true) {
				this->viewer.printMessage("返回輸入/back\n\n");
				this->viewer.printMessage("輸入看板名稱: ");

				std::cin >> name;

				if (name == "/same") {
					name = allBoard[index][2][boardColumn[2]];
				}

				if (name == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				if (this->board.boardNameIsExist(name)) {
					this->viewer.printMessage("\n看板名稱重複\n");
					continue;
				}

				this->viewer.printMessage("輸入看板類別: ");

				std::cin >> className;

				if (className == "/same") {
					className = allBoard[index][3][boardColumn[3]];
				}

				if (className == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("輸入看板標題: ");

				std::cin >> title;

				if (title == "/same") {
					title = allBoard[index][4][boardColumn[4]];
				}

				if (title == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("\n設定看板管理員帳號(若無請輸入 0): ");

				std::cin >> userAccount;

				if (userAccount == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				if (userAccount != "0") {
					user_id = this->user.findUserId(userAccount);

					if (user_id == -1) {
						this->viewer.printMessage("\n查無看板管理員帳號\n");
						continue;
					}
				}

				if (!this->board.updateBoard(name, className, title, user_id, stoi(allBoard[index][0][boardColumn[0]]))) {
					this->viewer.printMessage("\n編輯看板發生錯誤，稍後再試");
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("\n編輯成功，3秒後跳轉回管理員選單");
				Sleep(3000);
				this->viewer.clearScreen();
				this->adminManagerBoard(1);
				return;
			}
			break;
		case 75: //左
			viewer.clearScreen();
			this->adminManagerBoard(1);
			break;
		default:
			this->adminEditBoard(1);
			break;
	}
}

/// <summary>
/// 管理員刪除看板
/// </summary>
void BoardManager::adminDeleteBoard(int index) {
	this->viewer.clearScreen();
	//std::cout << index << '\n';
	std::vector<std::vector<std::map<std::string, std::string>>> allBoard = this->board.getAllBoard();
	std::vector<std::string> boardColumn = this->board.getBoardAllColunm();
	viewer.allBoard(allBoard, boardColumn, index + 1);
	/*for (auto board : allBoard) {
		for (size_t i = 0; i < boardColumn.size(); i++) {
			this->viewer.printMessage(board[i][boardColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}*/

	std::string confirm;
	char input = _getch();
	input = _getch();

	switch (input)
	{
		case 72: //上
			if (index > 0) {
				index--;
			}
			else if (index == 0)
			{
				index = allBoard.size();
			}
			this->adminDeleteBoard(index);
			break;
		case 80: //下
			if (index < allBoard.size() - 1) {
				index++;
			}
			else if (index == allBoard.size() - 1)
			{
				index = 0;
			}
			this->adminDeleteBoard(index);
			break;
		case 77: //右
			this->viewer.printMessage("\n確認刪除?輸入 /yes or /no\n");		
			while (true) {
				std::cin >> confirm;
				if (confirm == "/yes") {
					this->board.deleteBoard(stoi(allBoard[index][0][boardColumn[0]]));
					this->viewer.printMessage("\n刪除成功，3秒後跳轉回管理員選單");
					Sleep(3000);
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				if (confirm == "/no") {
					viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("\n請重新輸入\n");
			}
			break;
		case 75: //左
			viewer.clearScreen();
			this->adminManagerBoard(1);
			break;
		default:
			this->adminDeleteBoard(1);
			break;
	}
}


void BoardManager::viewAllPost(int board_id, int index) {
	this->viewer.clearScreen();

	std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> allPost = this->board.getAllPost(board_id);
	std::vector<std::string> postColumn = this->board.getPostAllColunm();

	for (auto board : allPost) {
		for (size_t i = 2; i < postColumn.size(); i++) {
			this->viewer.printMessage(board[i][postColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}

	char input = _getch();
	input = _getch();
}

void BoardManager::viewInsertPost(int index) {
	this->viewer.clearScreen();

	std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> allBoard = this->board.getAllBoard();
	std::vector<std::string> boardColumn = this->board.getBoardAllColunm();

	for (auto board : allBoard) {
		for (size_t i = 2; i < boardColumn.size(); i++) {
			this->viewer.printMessage(board[i][boardColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}

	std::string title, text;
	char input = _getch();
	input = _getch();

	switch (input)
	{
	case 72: //上
		if (index > 1) {
			index--;
		}
		this->viewInsertPost(index);
		break;
	case 80: //下
		if (index < allBoard.size()) {
			index++;
		}
		this->viewInsertPost(index);
		break;
	case 77: //右
		this->viewer.clearScreen();
		
		this->viewer.printMessage("新增文章\n");
		this->viewer.printMessage("輸入文章標題: ");

		std::cin >> title;

		if (title == "/back") {
			system("cls");
			this->viewAllBoard(1);
			return;
		}

		this->viewer.printMessage("\n輸入文章內文: ");

		std::cin >> text;

		if (text == "/back") {
			system("cls");
			this->viewAllBoard(1);
			return;
		}

		if (this->board.insertPost(stoi(allBoard[index - 1][0]["id"]), stoi(this->user.user[0][0]["id"]), title, text)) {
			this->viewer.printMessage("\n新增文章成功，三秒後跳回看板區");
		}
		else {
			this->viewer.printMessage("\n新增文章時發生錯誤，三秒後跳回看板區");
		}

		Sleep(3000);
		system("cls");
		this->viewAllBoard(index);
		return;

		break;
	case 75: //左
		this->mainMenu(1);
		break;
	default:
		this->viewInsertPost(1);
		break;
	}

	return;
}

void BoardManager::viewEditPost(int index) {
	this->viewer.clearScreen();

	std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> userAllPost = this->board.getUserPost(std::stoi(this->user.user[0][0]["id"]));
	std::vector<std::string> boardColumn = this->board.getPostAllColunm();

	for (auto post : userAllPost) {
		for (size_t i = 2; i < boardColumn.size(); i++) {
			this->viewer.printMessage(post[i][boardColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}

	std::string title, text;
	char input = _getch();
	input = _getch();

	switch (input)
	{
	case 72: //上
		if (index > 1) {
			index--;
		}
		this->viewEditPost(index);
		break;
	case 80: //下
		if (index < userAllPost.size()) {
			index++;
		}
		this->viewEditPost(index);
		break;
	case 77: //右
		system("cls");
		this->viewer.printMessage("編輯文章，不更改輸入/same\n");
		this->viewer.printMessage("文章標題: ");
		
		std::cin >> title;

		if (title == "/same") {
			title = userAllPost[index - 1][3]["title"];
		}

		this->viewer.printMessage("\n文章內容: ");

		std::cin >> text;

		if (text == "/same") {
			text = userAllPost[index - 1][4]["text"];
		}

		if (this->board.updatePost(stoi(userAllPost[index - 1][0]["id"]), title, text)) {
			this->viewer.printMessage("\n編輯文章成功，三秒後跳回看板區");
		}
		else {
			this->viewer.printMessage("\n編輯文章時發生錯誤，三秒後跳回看板區");
		}

		Sleep(3000);
		system("cls");
		this->viewAllBoard(index);
		return;

		break;
	case 75: //左
		this->mainMenu(1);
		break;
	default:
		this->viewEditPost(1);
		break;
	}

	return;
}

void BoardManager::viewDeletePost(int index) {
	this->viewer.clearScreen();

	std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> userAllPost = this->board.getUserPost(std::stoi(this->user.user[0][0]["id"]));
	std::vector<std::string> boardColumn = this->board.getPostAllColunm();

	for (auto post : userAllPost) {
		for (size_t i = 2; i < boardColumn.size(); i++) {
			this->viewer.printMessage(post[i][boardColumn[i]] + '\t');
		}
		this->viewer.printMessage("\n");
	}

	std::string confirm;
	char input = _getch();
	input = _getch();

	switch (input)
	{
	case 72: //上
		if (index > 1) {
			index--;
		}
		this->viewDeletePost(index);
		break;
	case 80: //下
		if (index < userAllPost.size()) {
			index++;
		}
		this->viewDeletePost(index);
		break;
	case 77: //右
		this->viewer.printMessage("確認是否刪除: 輸入/yes or /no: ");
		std::cin >> confirm;

		if (confirm == "/yes") {
			this->board.deletePost(std::stoi(userAllPost[index - 1][0]["id"]));
			this->viewer.printMessage("\n刪除文章成功，三秒後跳回主選單");
			Sleep(3000);
			system("cls");
			this->mainMenu(1);
			return;
		}

		if (confirm == "/no") {
			system("cls");
			this->mainMenu(1);
			return;
		}

		break;
	case 75: //左
		this->mainMenu(1);
		break;
	default:
		this->viewDeletePost(1);
		break;
	}

	return;
}