#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "User.h"
#include "Mail.h"
#include "Board.h"
#include "Viewer.h"
#include "Database.h"


class BoardManager {
	public:
		Database* db = new Database;
		Viewer viewer;
		Board board = Board(this->db);
		User user = User(this->db);
		Mail mail = Mail(this->db);

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

		void viewOnePost(int post_id);

		void viewMail(int index);

		void viewOneMail(int mail_id);
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

	if (input == "/guest") {
		this->viewer.clearScreen();
		this->viewAllBoard(1);
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

	std::string name = this->user.user[0][1]["account"];

	this->mainMenu(1);
}

/// <summary>
/// �D��� �a��J�}�Y�Ӥ�������
/// </summary>
void BoardManager::mainMenu(int index) {
	/* ��o�䪺viewer�D���N�i�H�F*/
	if (this->user.user[0][3]["level"] == "1") {
		viewer.adminMainMenu(index);

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
					index = 6;
				}
				this->mainMenu(index);
				break;
			case 80: //�U
				if (index < 6) {
					index++;
				}
				else if (index == 6)//����Ĥ@��
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
						this->viewInsertPost(1);
						break;
					case 4:
						this->viewEditPost(1);
						break;
					case 5:
						this->viewDeletePost(1);
						break;
					case 6:
						this->viewMail(1);
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
		std::cout << index << '\n';

		this->viewer.printMessage("�@��|������\n");
		this->viewer.printMessage("Announce    \t�i�Ҧ��ݪO�j\n");
		this->viewer.printMessage("WritePost   \t�i�s�W�峹�j\n");
		this->viewer.printMessage("EditPost    \t�i�s��峹�j\n");
		this->viewer.printMessage("DeletePost  \t�i�R���峹�j\n");
		this->viewer.printMessage("Mail        \t�i�H�c�j\n");

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
					index = 6;
				}
				this->mainMenu(index);
				break;
			case 80: //�U
				if (index < 6) {
					index++;
				}
				else if (index == 6)//����Ĥ@��
				{
					index = 1;
				}
				this->mainMenu(index);
				break;
			case 77: //�k
				switch (index)
				{
				case 1:
					this->viewAllBoard(1);
					break;
				case 2:
					this->viewInsertPost(1);
					break;
				case 3:
					this->viewEditPost(1);
					break;
				case 4:
					this->viewDeletePost(1);
					break;
				case 5:
					this->viewMail(1);
					break;
				case 6:
					viewer.clearScreen();
					std::cout << "NOT done yet!";
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

	return;
}

/// <summary>
/// ��ܥ����ݪO
/// </summary>
void BoardManager::viewAllBoard(int index) {
	this->viewer.clearScreen();
	
	std::vector<std::vector<std::map<std::string, std::string>>> allBoard = this->board.getAllBoard();
	std::vector<std::string> boardColumn = this->board.getBoardAllColunm();
	viewer.allBoard(allBoard, boardColumn, index);

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
			this->viewAllPost(std::stoi(allBoard[index-1][0]["id"]), 1);
			break;
		case 75: //��
			system("cls");
			if (this->user.user.size() > 0) {
				this->mainMenu(1);
			}
			else {
				this->loginMenu(0);
			}
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


void BoardManager::viewAllPost(int board_id, int index) {
	this->viewer.clearScreen();
	this->board.addHot(board_id);

	//std::cout << index << '\n';

	std::vector<std::vector<std::map<std::string, std::string>>> allPost = this->board.getAllPost(board_id);
	std::vector<std::string> postColumn = this->board.getPostAllColunm();
	std::vector<bool> isHot;

	for (auto post : allPost) {
		isHot.push_back(this->board.isHot(std::stoi(post[0]["id"])));
	}

	viewer.allpost(allPost, postColumn, isHot, index);
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
			index = allPost.size();
		}
		this->viewAllPost(board_id, index);
		break;
	case 80: //�U
		if (index < allPost.size() ) {
			index++;
		}
		else if (index == allPost.size() )
		{
			index = 1;
		}
		this->viewAllPost(board_id, index);
		break;
	case 77: //�k
		this->viewOnePost(std::stoi(allPost[index - 1][0]["id"]));
		break;
	case 75: //��
		viewer.clearScreen();
		this->viewAllBoard(1);
		break;
	default:
		this->viewAllBoard(1);
		break;
	}
}

void BoardManager::viewInsertPost(int index) {
	this->viewer.clearScreen();

	std::vector<std::vector<std::map<std::string, std::string>>> allBoard = this->board.getAllBoard();
	std::vector<std::string> boardColumn = this->board.getBoardAllColunm();

	viewer.allBoard(allBoard, boardColumn, index);

	std::string title, text;
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
		this->viewInsertPost(index);
		break;
	case 80: //�U
		if (index < allBoard.size()) {
			index++;
		}
		else if (index == allBoard.size())
		{
			index = 1;
		}
		this->viewInsertPost(index);
		break;
	case 77: //�k
		this->viewer.clearScreen();
		
		this->viewer.printMessage("�s�W�峹\n");
		this->viewer.printMessage("��J�峹���D: ");

		std::cin >> title;

		if (title == "/back") {
			system("cls");
			this->viewAllBoard(1);
			return;
		}

		this->viewer.printMessage("\n��J�峹����: ");

		std::cin >> text;

		if (text == "/back") {
			system("cls");
			this->viewAllBoard(1);
			return;
		}

		if (this->board.insertPost(stoi(allBoard[index - 1][0]["id"]), stoi(this->user.user[0][0]["id"]), title, text)) {
			this->viewer.printMessage("\n�s�W�峹���\�A�T�����^�ݪO��");
		}
		else {
			this->viewer.printMessage("\n�s�W�峹�ɵo�Ϳ��~�A�T�����^�ݪO��");
		}

		Sleep(3000);
		system("cls");
		this->viewAllBoard(index);
		return;

		break;
	case 75: //��
		viewer.clearScreen();
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

	std::vector<std::vector<std::map<std::string, std::string>>> userAllPost = this->board.getUserPost(std::stoi(this->user.user[0][0]["id"]));
	std::vector<std::string> boardColumn = this->board.getPostAllColunm();
	std::vector<bool> isHot;

	for (auto post : userAllPost) {
		isHot.push_back(false);
	}

	viewer.allpost(userAllPost, boardColumn, isHot, index);

	std::string title, text;
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
			index = userAllPost.size();
		}
		this->viewEditPost(index);
		break;
	case 80: //�U
		if (index < userAllPost.size()) {
			index++;
		}
		else if (index == userAllPost.size())
		{
			index = 1;
		}
		this->viewEditPost(index);
		break;
	case 77: //�k
		system("cls");
		if (userAllPost[index - 1][5]["isDeleted"] == "1") {
			this->viewer.printMessage("�峹�w�Q�޲z���R���A��]: " + userAllPost[index - 1][4]["text"] + "\n");
			this->viewer.printMessage("���U�������^\n");
			std::cin >> title;
			this->viewer.clearScreen();
			this->mainMenu(1);
			return;
		}

		this->viewer.printMessage("�s��峹�A������J/same\n");
		this->viewer.printMessage("�峹���D: ");
		
		std::cin >> title;

		if (title == "/same") {
			title = userAllPost[index - 1][3]["title"];
		}

		this->viewer.printMessage("\n�峹���e: ");

		std::cin >> text;

		if (text == "/same") {
			text = userAllPost[index - 1][4]["text"];
		}

		if (this->board.updatePost(stoi(userAllPost[index - 1][0]["id"]), title, text)) {
			this->viewer.printMessage("\n�s��峹���\�A�T�����^�ݪO��");
		}
		else {
			this->viewer.printMessage("\n�s��峹�ɵo�Ϳ��~�A�T�����^�ݪO��");
		}

		Sleep(3000);
		system("cls");
		this->viewAllBoard(index);
		return;

		break;
	case 75: //��
		viewer.clearScreen();
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

	std::vector<std::vector<std::map<std::string, std::string>>> userAllPost = this->board.getUserPost(std::stoi(this->user.user[0][0]["id"]));
	std::vector<std::string> boardColumn = this->board.getPostAllColunm();
	std::vector<bool> isHot;

	for (auto post : userAllPost) {
		isHot.push_back(false);
	}

	viewer.allpost(userAllPost, boardColumn, isHot, index);

	std::string confirm;
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
			index = userAllPost.size();
		}
		this->viewDeletePost(index);
		break;
	case 80: //�U
		if (index < userAllPost.size()) {
			index++;
		}
		else if (index == userAllPost.size())
		{
			index = 1;
		}
		this->viewDeletePost(index);
		break;
	case 77: //�k
		if (userAllPost[index - 1][5]["isDeleted"] == "1") {
			this->viewer.printMessage("�峹�w�Q�޲z���R���A��]: " + userAllPost[index - 1][4]["text"] + "\n");
			this->viewer.printMessage("���U�������^\n");
			std::cin >> confirm;
			this->viewer.clearScreen();
			this->mainMenu(1);
			return;
		}

		this->viewer.printMessage("�T�{�O�_�R��: ��J/yes or /no: ");
		std::cin >> confirm;

		if (confirm == "/yes") {
			this->board.deletePost(std::stoi(userAllPost[index - 1][0]["id"]));
			this->viewer.printMessage("\n�R���峹���\�A�T�����^�D���");
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
	case 75: //��
		viewer.clearScreen();
		this->mainMenu(1);
		break;
	default:
		this->viewDeletePost(1);
		break;
	}

	return;
}

void BoardManager::viewOnePost(int post_id) {
	system("cls");
	auto post = this->board.getOnePost(post_id);
	auto comments = this->board.getOnePostComment(post_id);

	std::string user = this->user.getUserAccount(std::stoi(post[0][2]["user_id"]));

	for (auto& comment : comments) {
		comment[2]["user_id"] = this->user.getUserAccount(std::stoi(comment[2]["user_id"]));
	}

	this->viewer.printMessage("�ݪO: " + post[0][1]["board_id"] + "\n\n");

	this->viewer.printMessage("�o���: " + user + "\n\n");

	this->viewer.printMessage("���D: " + post[0][3]["title"] + "\n\n");

	//this->viewer.printMessage("�ɶ�: " + post[0][5]["created_at"] + "\n");

	this->viewer.printMessage("�峹: \n" + post[0][4]["text"] + "\n\n\n");

	if(post[0][5]["isDeleted"] == "0"){
		for (auto comment : comments) {
			if (comment[5]["isDeleted"] == "0") {
				if (comment[3]["action"] == "0") {
					this->viewer.printMessage("-> ");
				}
				if (comment[3]["action"] == "1") {
					this->viewer.printMessage("�� ");
				}
				if (comment[3]["action"] == "2") {
					this->viewer.printMessage("�N ");
				}

				this->viewer.printMessage(comment[2]["user_id"] + ": " + comment[4]["text"] + "  " + comment[6]["created_at"] + "\n");
			}else{
				this->viewer.printMessage("-> ");

				this->viewer.printMessage("??????: " + comment[4]["text"] + "  " + comment[6]["created_at"] + "\n");
			}
		}
	}

	int action = 0;
	std::string text;
	std::string adminAction;
	std::string reason;
	std::string commentIndex;
	char input = _getch();
	input = _getch();

	switch (input)
	{
	case 72: //�W
		this->viewOnePost(post_id);
		break;
	case 80: //�U
		this->viewOnePost(post_id);
		break;
	case 77: //�k
		if (this->user.user.size() > 0) {	
			if (!this->board.isLeavedComment(post_id, std::stoi(this->user.user[0][0]["id"]))) {
				this->viewer.printMessage("��J0(�S���߱�) 1(��) 2(�N)��F�A���߱�: ");
				std::cin >> action;
			}

			this->viewer.printMessage("\n��J�d��: ");
			std::cin >> text;

			if (text == "/back") {
				this->viewOnePost(post_id);
				return;
			}

			if (this->board.insertComment(post_id, std::stoi(this->user.user[0][0]["id"]), action, text)) {
				this->viewer.printMessage("\n�s�W�d�����\�A�N���s��s");
			}
			else {
				this->viewer.printMessage("\n�s�W�d���o�Ϳ��~�A�N���s��s");
			}

			Sleep(3000);
			this->viewer.clearScreen();
			this->viewOnePost(post_id);	
			return;
		}

		this->viewOnePost(post_id);
		break;
	case 75: //��
		viewer.clearScreen();
		this->viewAllPost(this->board.getBoardId(post_id), 1);
		break;
	case 'p':
		if (this->user.user[0][3]["level"] == "1") {
			this->viewer.printMessage("\n��J���O: ");
			std::cin >> adminAction;

			if (adminAction == "/post") {
				this->viewer.printMessage("\n��J��]: ");
				std::cin >> reason;
	
				if (this->board.adminDeletePost(post_id, "���峹�w�Q�޲z���R���A��]�G" + reason, "���峹�w�Q�޲z���R���A��]�G" + reason)) {
					this->viewer.printMessage("\n�R���峹���\�A�N���s��s");
				}
				else {
					this->viewer.printMessage("\n�R���峹�o�Ϳ��~�A�N���s��s");
				}

				Sleep(3000);
				this->viewer.clearScreen();
				this->viewOnePost(post_id);
				return;
			}

			if (adminAction == "/comment") {
				this->viewer.printMessage("\n��J�ĴX�ӯd��: ");
				std::cin >> commentIndex;

				this->viewer.printMessage("\n��J��]: ");
				std::cin >> reason;

				if (this->board.adminDeleteComment(std::stoi(comments[std::stoi(commentIndex) - 1][0]["id"]), "���d���w�Q�޲z���R���A��]�G" + reason)) {
					this->viewer.printMessage("\n�R���d�����\�A�N���s��s");
				}
				else {
					this->viewer.printMessage("\n�R���d���o�Ϳ��~�A�N���s��s");
				}

				Sleep(3000);
				this->viewer.clearScreen();
				this->viewOnePost(post_id);
				return;
			}
			this->viewOnePost(post_id);
		}
		break;
	default:
		this->viewOnePost(post_id);
		break;
	}

	return;
}

void BoardManager::viewMail(int index) {
	this->viewer.clearScreen();
	std::cout << index << '\n';
	auto ownMails = this->mail.getMail(std::stoi(this->user.user[0][0]["id"]));

	for (auto mail : ownMails) {
		this->viewer.printMessage("�H�H�H: " + this->user.getUserAccount(std::stoi(mail[1]["send_id"])) + "\t ���D: " + mail[3]["title"] + "\t �ɶ�: " + mail[5]["created_at"] + "\n");
	}
	
	std::string recipient;
	std::string title;
	std::string text;
	int recipient_id = -1;
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
			index = ownMails.size();
		}
		this->viewMail(index);
		break;
	case 80: //�U
		if (index < ownMails.size()) {
			index++;
		}
		else if (index == ownMails.size())
		{
			index = 1;
		}
		this->viewMail(index);
		break;
	case 77: //�k
		this->viewOneMail(std::stoi(ownMails[index - 1][0]["id"]));
		break;
	case 75: //��
		viewer.clearScreen();
		this->mainMenu(1);
		break;
	case 's':
		while (true) {
			viewer.clearScreen();
			viewer.printMessage("���H�H: ");
			std::cin >> recipient;

			if (recipient == "/back") {
				this->viewMail(1);
				return;
			}

			recipient_id = this->user.findUserId(recipient);

			if (recipient_id == -1) {
				viewer.printMessage("�d�L���H�H�A�Э��s��J\n");
				continue;
			}

			viewer.printMessage("\n���D: ");
			std::cin >> title;

			if (title == "/back") {
				this->viewMail(1);
				return;
			}

			viewer.printMessage("\n���e: ");
			std::cin >> text;

			if (text == "/back") {
				this->viewMail(1);
				return;
			}

			if (this->mail.sendMail(std::stoi(this->user.user[0][0]["id"]), recipient_id, title, text)) {
				viewer.printMessage("\n�H�H���\�A3���^��H�c");			
			}
			else {
				viewer.printMessage("\n�H�H�o�Ϳ��~�A3���^��H�c");
			}

			Sleep(3000);
			this->viewMail(1);
			return;
		}
		break;
	default:
		this->viewMail(index);
		break;
	}
}

void BoardManager::viewOneMail(int mail_id) {
	this->viewer.clearScreen();

	auto mail = this->mail.getOneMail(mail_id);

	this->viewer.printMessage("���D: " + mail[0][3]["title"] + "\n");
	this->viewer.printMessage("�H�H�H: " + this->user.getUserAccount(std::stoi(mail[0][1]["send_id"])) + "\n");
	this->viewer.printMessage("���e: " + mail[0][4]["text"] + "\n");

	char input = _getch();
	input = _getch();

	switch (input)
	{
	case 72: //�W
		this->viewOneMail(mail_id);
		break;
	case 80: //�U
		this->viewOneMail(mail_id);
		break;
	case 77: //�k
		this->viewOneMail(mail_id);
		break;
	case 75: //��
		viewer.clearScreen();
		this->viewMail(1);
		break;
	default:
		this->viewOneMail(mail_id);
		break;
	}
}