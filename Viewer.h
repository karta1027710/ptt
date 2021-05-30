#pragma once
#include <iostream>
#include <string>
#include<Windows.h>
#include<vector>
#include<map>
class Viewer {
private:
    int beforeColor = 15;
    int beforeColorP = 15;
public:
    void printMessage(std::string);
    void clearScreen();
    void LoginMenu(int);
    void reLogin();
    void allpost(std::vector<std::vector<std::map<std::string, std::string>>>, const std::vector<std::string>, int);
    void signUp();
    void resignUP();
    void adminMainMenu(int);
    void adminManageBoard(int);
    void allBoard(std::vector<std::vector<std::map<std::string, std::string>>>, const std::vector<std::string>, int);
    void Login();
    void Color(int);
    void printPTT();
    void printPoint();
};

void Viewer::printMessage(std::string str)
{
    std::cout << str;
}

void Viewer::clearScreen() {
    system("cls");
}

void Viewer::LoginMenu(int status)
{
    printPTT();

    std::cout << "   ◢██████◣　　　　　　         ◢████◣                   \n\n";
    std::cout << "◢◤　　　　　　◥◣　　　　◢◤　　　　◥◣           \n\n";
    std::cout << "◤　　　　　　　　◥◣　　◢◤　　　　　　█         \n\n";
    std::cout << "▎　　　◢█◣　　　◥◣◢◤　　◢█　　　█             \n\n";
    std::cout << "◣　　◢◤　　◥◣　　　　　　◢◣◥◣　◢◤              \n\n";
    std::cout << " ◥██◤ ◢◤ 　　　　　　◥██◤                     \n\n";
    std::cout << "        █　●　　　　　　　●　█                \n\n";
    std::cout << "        █　〃　　　▄　　　〃　█                \n\n";
    std::cout << "         ◥◣　　　╚╩╝　　　◢◤                  \n\n";
    std::cout << "             ◥█▅▃▃　▃▃▅█◤                    \n\n";
    std::cout << "             ◢◤　　　◥◣                       \n\n";
    std::cout << "             █　　　　　█                     \n\n";
    std::cout << "            ◢◤▕　　　▎◥◣                       \n\n";
    std::cout << "          ▕  ▃◣◢▅▅▅◣◢▃                         \n";
    if (status == 0)std::cout << "輸入/login 登入 or /register 註冊帳號:\n";
    else std::cout << "無效指令!!!\n輸入/login 登入 or /register 註冊帳號:\n";
}

void Viewer::reLogin()
{
    std::cout << "┴┬┴┬／￣＼＿／￣＼\n\n";
    std::cout << "┬┴┬┴▏　　▏▔▔▔▔＼\n\n";
    std::cout << "┴┬┴／＼　／　　　　　　﹨\n\n";
    std::cout << "┬┴∕　　　　　　　／　　　）\n\n";
    std::cout << "┴┬▏　　　　　　　　X　　▏\n\n";
    std::cout << "┬┴▏　　　　　　　　　　　▔█◤\n\n";
    std::cout << "┴◢██◣　　　　　　 ＼＿＿／\n\n";
    std::cout << "┬█████◣　　　　　　　／\n\n";
    std::cout << "┴█████████████◣\n\n";
    std::cout << "◢██████████████▆▄\n\n";
    std::cout << "◢████████████\n\n";
    std::cout << "。。。○ 帳號或密碼錯誤!請重新登入!!!\n";
}

void Viewer::allpost(std::vector<std::vector<std::map<std::string, std::string>>> allpost, std::vector<std::string>postColumn, int status)
{
    printPTT();

    for (int k = 0; k < allpost.size(); k++) {
        if (k + 1 == status) printPoint();
        else std::cout << "   ";
        for (size_t i = 2; i < postColumn.size(); i++) {
            std::cout << allpost[k][i][postColumn[i]] << '\t';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}



void Viewer::signUp()
{
    std::cout << "       ◢█◣▄▄▅▅▄▄◢█◣　　　　　　　　\n";
    std::cout << "      ◢████████████◣　　　　　　　\n";
    std::cout << "      ███████████████　　　　　　　\n";
    std::cout << "  ██　　　◥██◤　　　██　　　　\n\n";
    std::cout << "◢███　　　　◥◤　　　　██◣\n\n";
    std::cout << "▊▎██◣　　　　　　　　◢█▊▊　　　\n\n";
    std::cout << "▊▎██◤　　●　　●　　◥█▊▊\n\n";
    std::cout << "▊　██　　　　　　　　　　█▊▊\n\n";
    std::cout << "◥▇██　▊　　　　　　▊　█▇◤\n\n";
    std::cout << "█　◥▆▄▄▄▄▆◤　█▊　　　◢▇▇◣\n\n";
    std::cout << "◢██◥◥▆▅▄▂▂▂▂▄▅▆███◣　▊◢　█\n\n";
    std::cout << "█╳　　　　　　　　　　　　　　　╳█　◥◤◢◤\n\n";
    std::cout << "█◣　　　˙　　　　　˙　　　◢█◤ ◢◤　\n\n";
    std::cout << "  ▊　　 　　 █ ◢◤　 　　 　▊　 ◢◤\n\n";
    std::cout << "  ▊　　 　　　　　 　 　　　▊　◢◤\n\n";
    std::cout << "  ▊　　　 　⊕　　　　　　█▇◤　　　\n";
    std::cout << "     ◢█▇▆▆▆▅▅▅▅▆▆▆▇█◣　　　　　　　\n";
    std::cout << "   ▊　▂　▊　　　　　　▊　▂　▊　　　　　　　\n\n";
    std::cout << "    ◥▆▆▆◤　　　　　　◥▆▆▆◤\n\n";
}

void Viewer::resignUP()
{
    std::cout << "       ◢█◣▄▄▅▅▄▄◢█◣　　　　　　　　\n";
    std::cout << "      ◢████████████◣　　　　　　　\n";
    std::cout << "      ███████████████　　　　　　　\n";
    std::cout << "  ██　　　◥██◤　　　██　　　　\n\n";
    std::cout << "◢███　　　　◥◤　　　　██◣\n\n";
    std::cout << "▊▎██◣　　　　　　　　◢█▊▊　　　\n\n";
    std::cout << "▊▎██◤　　X　　X　　◥█▊▊\n\n";
    std::cout << "▊　██　　　　　　　　　　█▊▊\n\n";
    std::cout << "◥▇██　▊　　　　　　▊　█▇◤\n\n";
    std::cout << "█　◥▆▄▄▄▄▆◤　█▊　　　◢▇▇◣\n\n";
    std::cout << "◢██◥◥▆▅▄▂▂▂▂▄▅▆███◣　▊◢　█\n\n";
    std::cout << "█╳　　　　　　　　　　　　　　　╳█　◥◤◢◤\n\n";
    std::cout << "█◣　　　˙　　　　　˙　　　◢█◤ ◢◤　\n\n";
    std::cout << "  ▊　　 　　 █ ◢◤　 　　 　▊　 ◢◤\n\n";
    std::cout << "  ▊　　 　　　　　 　 　　　▊　◢◤\n\n";
    std::cout << "  ▊　　　 　⊕　　　　　　█▇◤　　　\n";
    std::cout << "     ◢█▇▆▆▆▅▅▅▅▆▆▆▇█◣　　　　　　　\n";
    std::cout << "   ▊　▂　▊　　　　　　▊　▂　▊　　　　　　　\n\n";
    std::cout << "    ◥▆▆▆◤　　　　　　◥▆▆▆◤\n\n";
    std::cout << "此帳號已被用過，請重新輸入帳號及密碼 :\n";
}

void Viewer::adminMainMenu(int status)
{
    printPTT();

    std::cout << "管理員功能介面\n\n";
    if (status == 1)
    {
        printPoint();
        std::cout << "ManagerBoard\t【管理看板】\n";
    }
    else
    {
        std::cout << "   ManagerBoard\t【管理看板】\n";
    }
    if (status == 2)
    {
        printPoint();
        std::cout << "Announce    \t【所有看板】\n";
    }
    else
    {
        std::cout << "   Announce    \t【所有看板】\n";
    }
    if (status == 3)
    {
        printPoint();
        std::cout << "WritePost   \t【新增文章】\n";
    }
    else
    {
        std::cout << "   WritePost   \t【新增文章】\n";
    }
    if (status == 4)
    {
        printPoint();
        std::cout << "EditPost    \t【編輯文章】\n";
    }
    else
    {
        std::cout << "   EditPost    \t【編輯文章】\n";
    }
    if (status == 5)
    {
        printPoint();
        std::cout << "DeletePost  \t【刪除文章】\n";
    }
    else
    {
        std::cout << "   DeletePost  \t【刪除文章】\n";
    }
    if (status == 6)
    {
        printPoint();
        std::cout << "Mail        \t【信    箱】\n\n\n";
    }
    else
    {
        std::cout << "   Mail        \t【信    箱】\n\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 登出  (→) 選定 ";
}

inline void Viewer::adminManageBoard(int status)
{
    printPTT();

    if (status == 1)
    {
        printPoint();
        std::cout << "InsertBoard\t【新增看板】\n";
    }
    else
    {
        std::cout << "   InsertBoard\t【新增看板】\n";
    }
    if (status == 2)
    {
        printPoint();
        std::cout << "EditBoard  \t【編輯看板】\n";
    }
    else
    {
        std::cout << "   EditBoard  \t【編輯看板】\n";
    }
    if (status == 3)
    {
        printPoint();
        std::cout << "DeleteBoard\t【刪除看板】\n\n";
    }
    else
    {
        std::cout << "   DeleteBoard\t【刪除看板】\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}

void Viewer::allBoard(std::vector<std::vector<std::map<std::string, std::string>>> allBoard, std::vector<std::string>boardColumn, int status)
{
    printPTT();
    for (int k = 0; k < allBoard.size(); k++) {
        if (k + 1 == status)         printPoint();
        
        else std::cout << "   ";
        for (size_t i = 2; i < boardColumn.size(); i++) {
            std::cout << allBoard[k][i][boardColumn[i]] << '\t';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}

void Viewer::Login()
{
    printPTT();
    std::cout << "┴┬┴┬／￣＼＿／￣＼\n\n";
    std::cout << "┬┴┬┴▏　　▏▔▔▔▔＼\n\n";
    std::cout << "┴┬┴／＼　／　　　　　　﹨\n\n";
    std::cout << "┬┴∕　　　　　　　／　　　）\n\n";
    std::cout << "┴┬▏　　　　　　　　●　　▏\n\n";
    std::cout << "┬┴▏　　　　　　　　　　　▔█◤\n\n";
    std::cout << "┴◢██◣　　　　　　 ＼＿＿／\n\n";
    std::cout << "┬█████◣　　　　　　　／\n\n";
    std::cout << "┴█████████████◣\n\n";
    std::cout << "◢██████████████▆▄\n\n";
    std::cout << "◢████████████\n\n";
    std::cout << "。。。○ 輸入帳號及密碼\n";
}

inline void Viewer::Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void Viewer::printPTT()
{
    srand(time(NULL));
    int i = rand() % 14 + 1;
    while (i == beforeColor)
    {
         i = rand() % 14 + 1;
    }
    beforeColor = i;
    Color(i);
    std::cout << "■■■      ■■■■■      ■■■■■\n";
    std::cout << "■   ■         ■              ■\n";
    std::cout << "■■■          ■              ■\n";
    std::cout << "■              ■              ■\n";
    std::cout << "■              ■              ■\n\n";
    Color(15);
}

inline void Viewer::printPoint()
{
    srand(time(NULL));
    int i = rand() % 14 + 1;
    while (i == beforeColorP)
    {
        i = rand() % 14 + 1;
    }
    beforeColor = i;
    Color(i);
    std::cout << "-> ";
    Color(15);
}


