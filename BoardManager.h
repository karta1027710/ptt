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

		void viewAllPost(int boardIndex);

		void viewInsertPost(int index);
};

void BoardManager::loginMenu(int status/*�P�_��J�L�ī��O*/) {
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

	this->viewer.printMessage("��J�b��: ");
	std::cin >> account;

	if (this->user.findUserId(account) != -1) {
		this->viewer.printMessage("\n�b������\n");
		this->registerAccount();
		return;
	}

	this->viewer.printMessage("\n��J�K�X: ");
	std::cin >> password;

	this->viewer.printMessage("\n�A���T�{�K�X: ");
	std::cin >> confirmPassword;

	if (password != confirmPassword) {
		this->viewer.printMessage("\n�K�X���@�P\n");
		this->registerAccount();
		return;
	}

	if (!this->user.insertUser(account, password)) {
		this->viewer.printMessage("\n���U�b���o�Ϳ��~�A�еy��A��\n");
		this->registerAccount();
		return;
	}

	this->viewer.printMessage("\n���U���\�A3�����^�n�J�e��\n");
	Sleep(3000);
	this->login(0);
	return;
}

/// <summary>
/// �n�J ���viewer�a��N�n
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
	this->viewer.printMessage("�w��i�JPTT\n");

	std::string name = this->user.user[0][1]["account"];
	this->viewer.printMessage("�w�� " + name + "\n");

	this->mainMenu(1);
}

/// <summary>
/// �D��� �a��J�}�Y�Ӥ�������
/// </summary>
void BoardManager::mainMenu(int index) {
	/* ��o�䪺viewer�D���N�i�H�F*/
	if (this->user.user[0][3]["level"] == "1") {
		viewer.adminMainMenu(index);
		/*std::cout << index << '\n';
		this->viewer.printMessage("�޲z���\�श��\n");
		this->viewer.printMessage("ManagerBoard\t�i�޲z�ݪO�j\n");
		this->viewer.printMessage("Announce    \t�i�Ҧ��ݪO�j\n");
		this->viewer.printMessage("WritePost   \t�i�s�W�峹�j\n");
		this->viewer.printMessage("Mail        \t�i�H    �c�j\n");*/

		char input = _getch();
		input = _getch();
		system("cls");
		switch (input)
		{
			case 72: //�W
				if (index > 1) {
					index--;
				}
				else if (index == 1)//����̫�@��
				{
					index = 4;
				}
				this->mainMenu(index);
				break;
			case 80: //�U
				if (index < 4) {
					index++;
				}
				else if (index == 4)//����Ĥ@��
				{
					index = 1;
				}
				this->mainMenu(index);
				break;
			case 77: //�k
				switch (index)
				{
					case 1:
						this->adminManagerBoard(1);
						break;
					case 2:
						this->viewAllBoard(1);
						break;
					case 3:
						//this->adminManagerBoard(1);
						break;
					default:
						this->mainMenu(1);
						break;
				}
				break;
			case 75: //��
				this->loginMenu(0);
				break;
			default:
				this->mainMenu(1);
				break;
		}
	}
	else if(this->user.user[0][3]["level"] == "2"){
		this->viewer.printMessage("�@��|������\n");
		this->viewer.printMessage("Announce    \t�i�Ҧ��ݪO�j\n");
		this->viewer.printMessage("WritePost   \t�i�s�W�峹�j\n");
		this->viewer.printMessage("Mail        \t�i�H�c�j\n");

		char input = _getch();
		input = _getch();

	}

	return;
}

/// <summary>
/// ��ܥ����ݪO
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
		case 72: //�W
			if (index > 1) {
				index--;
			}
			else if (index == 1)
			{
				index = allBoard.size();
			}
			this->viewAllBoard(index);
			break;
		case 80: //�U
			if (index < allBoard.size()) {
				index++;
			}
			else if (index == allBoard.size())
			{
				index = 1;
			}
			this->viewAllBoard(index);
			break;
		case 77: //�k
			this->viewAllPost(index);
			break;
		case 75: //��
			this->mainMenu(1);
			break;
		default:
			this->viewAllBoard(1);
			break;
	}

	return;
}

/// <summary>
/// �޲z���޲z�ݪO �a��J�}�Y�Ӥ�������
/// </summary>
void BoardManager::adminManagerBoard(int index) {
	/*��o��N�O�޲z�ݪO*/
	/*std::cout << index << '\n';
	this->viewer.printMessage("�޲z�ݪO\n");
	this->viewer.printMessage("InsertBoard\t�i�s�W�ݪO�j\n");
	this->viewer.printMessage("EditBoard  \t�i�s��ݪO�j\n");
	this->viewer.printMessage("DeleteBoard\t�i�R���ݪO�j\n");*/
	viewer.adminManageBoard(index);
	char input = _getch();
	input = _getch();
	system("cls");
	switch (input)
	{
		case 72: //�W
			if (index > 1) {
				index--;
			}
			else if (index == 1)
			{
				index = 3;
			}
			this->adminManagerBoard(index);
			break;
		case 80: //�U
			if (index < 3) {
				index++;
			}
			else if (index == 3)
			{
				index = 1;
			}
			this->adminManagerBoard(index);
			break;
		case 77: //�k
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
		case 75: //��
			this->mainMenu(1);
			break;
		default:
			this->adminManagerBoard(1);
			break;
	}

	return;
}

/// <summary>
/// �޲z���s�W�ݪO
/// �p�G�ݪO�W�٭��Ʒ|�~��j��
/// �ݪO�޲z���p�G�S���]�O�~��j��
/// �o��e�������N��s
/// 
/// ���\����3��|���^�޲z���D���
/// </summary>
void BoardManager::adminInsertBoard() {
	std::string name;
	std::string className;
	std::string title;
	std::string userAccount;
	int user_id = -1;

	this->viewer.clearScreen();
	this->viewer.printMessage("�s�W�ݪO\n");
	
	while (true) {
		this->viewer.printMessage("��^�п�J/back\n");
		this->viewer.printMessage("��J�ݪO�W��: ");

		std::cin >> name;

		if (name == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		if (this->board.boardNameIsExist(name)) {
			this->viewer.printMessage("\n�ݪO�W�٭���\n");
			continue;
		}

		this->viewer.printMessage("\n��J�ݪO���O: ");

		std::cin >> className;

		if (className == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		this->viewer.printMessage("\n��J�ݪO���D: ");

		std::cin >> title;

		if (title == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		this->viewer.printMessage("\n�]�w�ݪO�޲z���b��(�Y�L�п�J 0): ");

		std::cin >> userAccount;

		if (userAccount == "/back") {
			this->viewer.clearScreen();
			this->adminManagerBoard(1);
			return;
		}

		if (userAccount != "0") {
			user_id = this->user.findUserId(userAccount);

			if (user_id == -1) {
				this->viewer.printMessage("\n�d�L�ݪO�޲z���b��\n");
				continue;
			}
		}

		break;
	}
	
	if (!this->board.insertBoard(name, className, title, user_id)) {
		this->viewer.printMessage("\n�s�W�ݪO�o�Ϳ��~�A�y��A��");
		this->adminManagerBoard(1);
		return;
	}

	this->viewer.printMessage("\n�s�W���\�A3������^�޲z�����");
	Sleep(3000);
	this->viewer.clearScreen();
	this->adminManagerBoard(1);
	return;
}

/// <summary>
/// �޲z���s��ݪO
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
		case 72: //�W
			if (index > 0) {
				index--;
			}
			else if (index == 0)
			{
				index = allBoard.size();
			}
			this->adminEditBoard(index);
			break;
		case 80: //�U
			if (index < allBoard.size() - 1) {
				index++;
			}
			else if (index == allBoard.size()-1)
			{
				index = 0;
			}
			this->adminEditBoard(index);
			break;
		case 77: //�k
			while (true) {
				this->viewer.printMessage("��^��J/back\n\n");
				this->viewer.printMessage("��J�ݪO�W��: ");

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
					this->viewer.printMessage("\n�ݪO�W�٭���\n");
					continue;
				}

				this->viewer.printMessage("��J�ݪO���O: ");

				std::cin >> className;

				if (className == "/same") {
					className = allBoard[index][3][boardColumn[3]];
				}

				if (className == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("��J�ݪO���D: ");

				std::cin >> title;

				if (title == "/same") {
					title = allBoard[index][4][boardColumn[4]];
				}

				if (title == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("\n�]�w�ݪO�޲z���b��(�Y�L�п�J 0): ");

				std::cin >> userAccount;

				if (userAccount == "/back") {
					this->viewer.clearScreen();
					this->adminManagerBoard(1);
					return;
				}

				if (userAccount != "0") {
					user_id = this->user.findUserId(userAccount);

					if (user_id == -1) {
						this->viewer.printMessage("\n�d�L�ݪO�޲z���b��\n");
						continue;
					}
				}

				if (!this->board.updateBoard(name, className, title, user_id, stoi(allBoard[index][0][boardColumn[0]]))) {
					this->viewer.printMessage("\n�s��ݪO�o�Ϳ��~�A�y��A��");
					this->adminManagerBoard(1);
					return;
				}

				this->viewer.printMessage("\n�s�覨�\�A3������^�޲z�����");
				Sleep(3000);
				this->viewer.clearScreen();
				this->adminManagerBoard(1);
				return;
			}
			break;
		case 75: //��
			viewer.clearScreen();
			this->adminManagerBoard(1);
			break;
		default:
			this->adminEditBoard(1);
			break;
	}
}

/// <summary>
/// �޲z���R���ݪO
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
		case 72: //�W
			if (index > 0) {
				index--;
			}
			else if (index == 0)
			{
				index = allBoard.size();
			}
			this->adminDeleteBoard(index);
			break;
		case 80: //�U
			if (index < allBoard.size() - 1) {
				index++;
			}
			else if (index == allBoard.size() - 1)
			{
				index = 0;
			}
			this->adminDeleteBoard(index);
			break;
		case 77: //�k
			this->viewer.printMessage("\n�T�{�R��?��J /yes or /no\n");		
			while (true) {
				std::cin >> confirm;
				if (confirm == "/yes") {
					this->board.deleteBoard(stoi(allBoard[index][0][boardColumn[0]]));
					this->viewer.printMessage("\n�R�����\�A3������^�޲z�����");
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

				this->viewer.printMessage("\n�Э��s��J\n");
			}
			break;
		case 75: //��
			viewer.clearScreen();
			this->adminManagerBoard(1);
			break;
		default:
			this->adminDeleteBoard(1);
			break;
	}
}


void BoardManager::viewAllPost(int index) {
	this->viewer.clearScreen();

	std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> allPost = this->board.getAllPost();
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

	char input = _getch();
	input = _getch();

	switch (input)
	{
	case 72: //�W
		if (index > 1) {
			index--;
		}
		this->viewInsertPost(index);
		break;
	case 80: //�U
		if (index < allBoard.size()) {
			index++;
		}
		this->viewInsertPost(index);
		break;
	case 77: //�k
		this->viewer.clearScreen();
		
		break;
	case 75: //��
		this->mainMenu(1);
		break;
	default:
		this->viewInsertPost(1);
		break;
	}

	return;


}