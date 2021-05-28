#pragma once
#include <iostream>
#include <string>
#include<Windows.h>
#include<vector>
#include<map>
class Viewer {
public:
    void printMessage(std::string);
    void clearScreen();
    void LoginMenu(int);
    void reLogin();
    void board();
    void post();
    void signUp();
    void resignUP();
    void adminMainMenu(int);
    void adminManageBoard(int);
    void allBoard(const std::vector<std::vector<std::map<std::string, std::string>>>, const std::vector<std::string>, int);
    void Login();
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
   std::cout << "■■■      ■■■■■      ■■■■■\n";
   std::cout << "■   ■         ■              ■\n";
   std::cout << "■■■          ■              ■\n";
   std::cout << "■              ■              ■\n";
   std::cout << "■              ■              ■\n";
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

void Viewer::board()
{
}

void Viewer::post()
{

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
    std::cout << "管理員功能介面\n\n";
    if (status == 1)
    {
        std::cout << "-> ManagerBoard\t【管理看板】\n";
    }
    else
    {
        std::cout << "   ManagerBoard\t【管理看板】\n";
    }
    if (status == 2)
    {
        std::cout << "-> Announce    \t【所有看板】\n";
    }
    else
    {
        std::cout << "   Announce    \t【所有看板】\n";
    }
    if (status == 3)
    {
        std::cout << "-> WritePost   \t【新增文章】\n";
    }
    else
    {
        std::cout << "   WritePost   \t【新增文章】\n";
    }
    if (status == 4)
    {
        std::cout << "-> Mail        \t【信    箱】\n\n\n";
    }
    else
    {
        std::cout << "   Mail        \t【信    箱】\n\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}

inline void Viewer::adminManageBoard(int status)
{
    if (status == 1)
    {
        std::cout << "-> InsertBoard\t【新增看板】\n";
    }
    else
    {
        std::cout << "   InsertBoard\t【新增看板】\n";
    }
    if (status == 2)
    {
        std::cout << "-> EditBoard  \t【編輯看板】\n";
    }
    else
    {
        std::cout << "   EditBoard  \t【編輯看板】\n";
    }
    if (status == 3)
    {
        std::cout << "-> DeleteBoard\t【刪除看板】\n\n";
    }
    else
    {
        std::cout << "   DeleteBoard\t【刪除看板】\n\n";
    }
    std::cout << "(↑)(↓) 選擇  (←) 返回  (→) 選定 ";
}

void Viewer::allBoard(std::vector<std::vector<std::map<std::string, std::string>>> allBoard, std::vector<std::string>boardColumn, int status)
{
    for (int k = 0; k < allBoard.size(); k++) {
        if (k + 1 == status) std::cout << "-> ";
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



