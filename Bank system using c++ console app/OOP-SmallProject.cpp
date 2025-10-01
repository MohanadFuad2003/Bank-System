#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsLoginScreen.h"
#include <iomanip>
#include <windows.h>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void PrintCentered(string text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - text.length()) / 2;

    for (int i = 0; i < padding; ++i) {
        cout << " ";
    }
    cout << text << endl;
}

void ShowLoadingScreen() {
    system("cls");

    SetColor(13); 

    PrintCentered("  ####  ##    ##  ######    ##    ##  ##    ##  ######  ##    ##    ##    ##");
    PrintCentered(" ##  ##  ##    ##  ##   ##   ##    ##  ##    ##  ##   ##  ##    ##   ##    ##");
    PrintCentered(" ##      ##    ##  ##    ##  ##    ##  ##    ##  ##    ##  ##    ##   ##    ##");
    PrintCentered(" ##      ##    ##  ##    ##  ##    ##  ##    ##  ##    ##  ##    ##   ##    ##");
    PrintCentered(" ##      #########  ##    ##  ##    ##  #########  ##    ##  ##    ##   ########");
    PrintCentered(" ##  ##  ##    ##  ##   ##   ##    ##  ##    ##  ##   ##  ##    ##   ##    ##");
    PrintCentered("  ####   ##    ##  ######    ##    ##  ##    ##  ######   ######    ##    ##");
    PrintCentered("\n\t\t\t\t  *****************   BANK SYSTEM   ***************** ");  // Adding Bank System in the center

    SetColor(7);
    SetColor(10);
    cout << "\n\n\n\n" << endl;
    for (int i = 0; i <= 100; i += 10) {
        cout << "\r            \t \t\t \t\t\tLoading " << i << "%";
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    SetColor(7);
    this_thread::sleep_for(chrono::seconds(1));
    system("cls");
    clsLoginScreen::ShowLoginScreen();
}

int main() {
    ShowLoadingScreen();
    return 0;
}
