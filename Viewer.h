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
    void allpost(std::vector<std::vector<std::map<std::string, std::string>>>, const std::vector<std::string>, std::vector<bool>, int);
    void signUp();
    void resignUP();
    void adminMainMenu(int);
    void adminManageBoard(int);
    void allBoard(std::vector<std::vector<std::map<std::string, std::string>>>, const std::vector<std::string>, int);
    void Login();
    void Color(int);
    void printPTT();
    void printPoint();
    void userMenu(int);
    void allMail(std::vector<std::vector<std::map<std::string,std::string>>>,int);
    void allGame(int);
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
    if (status == 0)std::cout << "輸入/login 登入 or /register 註冊帳號 /guest 參觀:\n";
    else std::cout << "無效指令!!!\n輸入/login 登入 or /register 註冊帳號 or /guest 參觀:\n";
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

void Viewer::allpost(std::vector<std::vector<std::map<std::string, std::string>>> allpost, std::vector<std::string>postColumn, std::vector<bool> isHot, int status)
{
    printPTT();

    std::cout << "所有貼文\n\n";

    for (int k = 0; k < allpost.size(); k++) {
        if (k + 1 == status) printPoint();
        else std::cout << "   ";
        for (size_t i = 3; i < postColumn.size(); i++) {
            if (i == 3)
                std::cout << allpost[k][i][postColumn[i]] << "       ";
        }
        if (isHot[k] == true)
        {
            Color(236);
            std::cout << "推爆";
            Color(15);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}



void Viewer::signUp()
{
    printPTT();
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

    Color(2);
    std::cout << "PTT   ███〕▄▄▄▄▄▄\n";
    std::cout << "  ▂▄▅█████▅▄▃▂ 免費都更戰車\n";
    std::cout << "  ██████████████　\n";
    std::cout << " ◥⊙▲⊙▲⊙▲⊙◤\n\n";

    Color(15);
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
        std::cout << "Mail        \t【信    箱】\n";
    }
    else
    {
        std::cout << "   Mail        \t【信    箱】\n";
    }
    if (status == 7)
    {
        printPoint();
        std::cout << "Game        \t【小遊戲區】\n\n\n";
    }
    else
    {
        std::cout << "   Game        \t【小遊戲區】\n\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 登出  (→) 選定 ";
}

inline void Viewer::adminManageBoard(int status)
{
    printPTT();

    

    std::cout << "管理員版面管理\n\n";

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

    std::cout << "所有看板\n\n";
    std::cout << "   版名\t\t分類\t標題\t人氣\n";
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

inline void Viewer::userMenu(int status)
{
    printPTT();
    Color(2);
    std::cout << "PTT   ███〕▄▄▄▄▄▄\n";
    std::cout << "  ▂▄▅█████▅▄▃▂ 免費都更戰車\n";
    std::cout << "  ██████████████　\n";
    std::cout << " ◥⊙▲⊙▲⊙▲⊙◤\n";
    std::cout << "一般使用者介面\n\n";

    Color(15);
    if (status == 1)
    {
        printPoint();
        std::cout << "Announce    \t【所有看板】\n";
    }
    else
    {
        std::cout << "   Announce    \t【所有看板】\n";
    }
    if (status == 2)
    {
        printPoint();
        std::cout << "WritePost   \t【新增文章】\n";
    }
    else
    {
        std::cout << "   WritePost   \t【新增文章】\n";
    }
    if (status == 3)
    {
        printPoint();
        std::cout << "EditPost    \t【編輯文章】\n";
    }
    else
    {
        std::cout << "   EditPost    \t【編輯文章】\n";
    }
    if (status == 4)
    {
        printPoint();
        std::cout << "DeletePost  \t【刪除文章】\n";
    }
    else
    {
        std::cout << "   DeletePost  \t【刪除文章】\n";
    }
    if (status == 5)
    {
        printPoint();
        std::cout << "Mail  \t【信箱】\n";
    }
    else
    {
        std::cout << "   Mail   \t【信箱】\n";
    }
    if (status == 6)
    {
        printPoint();
        std::cout << "Game  \t【小遊戲區】\n\n";
    }
    else
    {
        std::cout << "   Game   \t【小遊戲區】\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";

}

inline void Viewer::allMail(std::vector<std::vector<std::map<std::string, std::string>>> allMail,int status)
{

}

inline void Viewer::allGame(int status)
{
    printPTT();
    if (status == 1)
    {
        printPoint();
        std::cout << "賭盤\n";
    }
    else
    {
        std::cout << "   賭盤\n";
    }
    if (status == 2)
    {
        printPoint();
        std::cout << "拉霸機\n";
    }
    else
    {
        std::cout << "   拉霸機\n";
    }
    if (status == 3)
    {
        printPoint();
        std::cout << "猜數字\n\n";
    }
    else
    {
        std::cout << "   猜數字\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}


