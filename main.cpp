#include <iostream>
#include <string>
#include "BoardManager.h"
#include "Database.h"

int main() {
	BoardManager* boardManager = new BoardManager();
	boardManager->loginMenu();
	return 0;
}