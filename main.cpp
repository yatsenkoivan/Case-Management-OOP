#include "Cases.h"

void welcome() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = 0;
    lpCursor.dwSize = 1;
    SetConsoleCursorInfo(console, &lpCursor);
}

int main()
{
    welcome();
    Manager manager;
    manager.load();
    manager.menu();
}
