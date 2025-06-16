#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h> 
#include <thread>    
#include <chrono>     
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsCreateTheFirstUserScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen {
private:
    static void _CreateTheFirstUserIfFileEmpty() {
        clsCreateTheFirstUserScreen::ShowCreateFirstUserScreen();
    }

    static void _Login() {
        string UserName;
        string Password;
        bool flag = false;
        int counter = 3;
        
        do {
            system("cls");
            _DrawScreenHeader("\t LOGIN SCREEN");

            if (flag) {
                cout << "\nInvalid Username/Password!" << "\nYou have [" << counter << "] attempt(s) left.\n\n";
            }
            if (counter == 0)
                break;

            UserName = clsInputValidate::ReadString("\nEnter Username : ");
            Password = clsInputValidate::ReadString("\nEnter Password : ");

            CurrentUser = clsUser::Find(UserName, Password);
            flag = CurrentUser.IsEmpty();

            if (flag)
                counter--;

        } while (flag && counter >= 0);

        if (flag) {
            cout << "\n\n\t\t\t\t You tried [3] times. Access blocked.\n";

            for (int i = 5; i >= 1; --i) {
                cout << "\r\t\t\t Locking workstation in: " << i << "   " << std::flush;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            cout << "\n\n";
            LockWorkStation();
        }
        else {
            CurrentUser.OperationForSaveRegistersToFile();
            clsMainScreen::ShowMainMenue();
        }
    }


public:
    static void ShowLoginScreen() {
        vector<clsUser> StoreUser = clsUser::GetUsersList();

        if (StoreUser.size() == 0) {
            _CreateTheFirstUserIfFileEmpty();
        }

        _Login();
    }
};
