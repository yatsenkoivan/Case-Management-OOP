#include "Cases.h"

void welcome() {
    std::cout << "W - to move up\n";
    std::cout << "S - to move down\n";
    std::cout << "SPACE to choose\n\n";
    system("pause");
}

int main()
{
    welcome();
    Manager manager;
    manager.load();
    manager.menu();
}
