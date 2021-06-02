#pragma once
#include <iostream>
#include <ctime>

class Slot
{
public:
    std::string drums[5];
    int random;
    int bet;
    int price;
    int gameStatus;
    Slot();

    void infomation();
    int Play(int cost);
    void slot();
    int checkLine();
    int startGame(int cost);
};

Slot::Slot()
{
    for (int i = 0; i < 3; i++)
    {
        this->drums[i] = "";
    }

    this->random = 0;
    this->bet = 0;
    this->price = 0;
    this->gameStatus = 0;
}

void Slot::infomation()
{
    std::cout << "◢■■■◤" << "\t" << "◢        " << "\t" << "◢■■■◣" << "\t" << "◢■■■◣" << std::endl;
    std::cout << "■        " << "\t" << "■        " << "\t" << "■      ■" << "\t" << "    ■    " << std::endl;
    std::cout << "◥■■■◣" << "\t" << "■        " << "\t" << "■      ■" << "\t" << "    ■    " << std::endl;
    std::cout << "        ■" << "\t" << "■        " << "\t" << "■      ■" << "\t" << "    ■    " << std::endl;
    std::cout << "◢■■■◤" << "\t" << "◥■■■◤" << "\t" << "◥■■■◤" << "\t" << "    ■    " << std::endl;

    std::cout << std::endl << std::endl;

    std::cout << "規則 : \n";
    std::cout << "沒有連線 : 全輸\n";
    std::cout << "連線 : \n";
    std::cout << "'10' '10' '10' \t: $ x 2\n";
    std::cout << "'J' 'Q' 'K' \t: $ x 3\n";
    std::cout << "'K' 'Q' 'J' \t: $ x 3\n";
    std::cout << "'J' 'J' 'J' \t: $ x 4\n";
    std::cout << "'Q' 'Q' 'Q' \t: $ x 4\n";
    std::cout << "'K' 'K' 'K' \t: $ x 4\n";
    std::cout << "'7' '7' '7' \t: $ x 5\n";

    std::cout << std::endl << std::endl;
}

int Slot::Play(int cost)
{
    char input;
    this->bet = cost;
    std::cout << "投入 $" << this->bet << "為賭金\n";
    std::cout << "【P】開始遊戲\n";
    std::cin >> input;

    if (input == 'p' || input == 'P')
    {
        this->slot();
        return this->checkLine();
    }


}

void Slot::slot()
{
    system("cls");

    srand(time(NULL));

    for (int i = 0; i < 3; i++)
    {
        random = ((rand() % 7) + 1);

        switch (random)
        {
        case (1):
            std::cout << "【10】";
            this->drums[i] = "10";
            break;
        case (2):
            std::cout << "【10】";
            this->drums[i] = "10";
            break;
        case (3):
            std::cout << "【10】";
            this->drums[i] = "10";
            break;
        case (4):
            std::cout << "【J】";
            this->drums[i] = "J";
            break;
        case (5):
            std::cout << "【Q】";
            this->drums[i] = "Q";
            break;
        case (6):
            std::cout << "【K】";
            this->drums[i] = "K";
            break;
        case (7):
            std::cout << "【7】";
            this->drums[i] = "7";
            break;
        default:
            break;
        }
    }

    std::cout << std::endl;
}

int Slot::checkLine()
{
    if (this->drums[0] == this->drums[1] && this->drums[1] == this->drums[2])
    {
        if (this->drums[0] == "10")
        {
            this->price += this->bet * 2;
            this->gameStatus = 2;
        }
        else if (this->drums[0] == "J")
        {
            this->price += this->bet * 4;
            this->gameStatus = 4;
        }
        else if (this->drums[0] == "Q")
        {
            this->price += this->bet * 4;
            this->gameStatus = 4;
        }
        else if (this->drums[0] == "K")
        {
            this->price += this->bet * 4;
            this->gameStatus = 4;
        }
        else if (this->drums[0] == "7")
        {
            this->price += this->bet * 5;
            this->gameStatus = 5;
        }
    }
    else if (this->drums[0] == "J" && this->drums[0] == "Q" && this->drums[0] == "K")
    {
        this->price += this->bet * 3;
        this->gameStatus = 3;
    }
    else if (this->drums[0] == "K" && this->drums[0] == "Q" && this->drums[0] == "J")
    {
        this->price += this->bet * 3;
        this->gameStatus = 3;
    }
    else
    {
        this->price = 0;
        this->gameStatus = 1;
    }

    std::cout << "結果獲得 $ " << price << std::endl;

    return gameStatus;
}

int Slot::startGame(int cost)
{
    this->infomation();
    std::cout << "投入賭金 : ";
    system("cls");

    return this->Play(cost);
}
