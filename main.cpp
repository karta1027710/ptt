//5/28
#include <iostream>
#include <string>
#include "BoardManager.h"
#include "Database.h"

int main() {
	BoardManager* boardManager = new BoardManager();
	boardManager->loginMenu(0);
	return 0;
}