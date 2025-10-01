#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsClientListScreen.h";
#include "clsDeleteClientScreen.h";
#include"clsAddNewClientScreen.h";
#include "clsUpdateClientScreen.h";
#include "clsFindClientScreen.h";
#include"clsTransactionsScreen.h";
#include "Global.h";
#include "clsManageUsers.h";
#include "clsShowLoginRegisterScreen.h";
#include "clsDeleteAllUserFromFileLoginRegisterScreen.h";
#include "clsMainMeneuCurrencyScreen.h";
using namespace std;

class clsMainScreen :protected clsScreen {
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8 , eDeleteAllUserFromLoginRegisterFile = 9 , eCurreuncyExchange = 10 , eLogout = 11
    };

    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "{ Choose what do you want to do? [1 to 11] } ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 11, "Enter Number between 1 to 11? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()  {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen() {
        if (clsScreen::CheckAccessRights(CurrentUser.pListClients)) {
            clsClientListScreen::ShowClientsList();
        }
    }

    static void _ShowAddNewClientsScreen() {
        if (clsScreen::CheckAccessRights(CurrentUser.pAddNewClient)) {
            clsAddNewClientScreen::ShowAddNewClientScreen();
        }
    }

    static void _ShowDeleteClientScreen()
    {      
        if (clsScreen::CheckAccessRights(CurrentUser.pDeleteClient)) {
            clsDeleteClientScreen::ShowDeleteClientScreen();
        }
    }

    static void _ShowUpdateClientScreen()
    {
        if (clsScreen::CheckAccessRights(CurrentUser.pUpdateClients)) {
            clsUpdateClientScreen::ShowUpdateClientScreen();
        }
    }

    static void _ShowFindClientScreen()
    {
        if (clsScreen::CheckAccessRights(CurrentUser.pFindClient)) {
            clsFindClientScreen::ShowFindClientScreen();
        }
    }

    static void _ShowTransactionsMenue()
    {
        if (clsScreen::CheckAccessRights(CurrentUser.pTranactions)) {
            clsTransactionsScreen::ShowTransactionsMenue();
        }
    }

    static void _ShowManageUsersMenue()
    {
        if (clsScreen::CheckAccessRights(CurrentUser.pManageUsers)) {
            clsManageUsersScreen::ShowManageUsersMenue();
        }
    }

    static void _ShowLoginRegisterScreen() {
        if (clsScreen::CheckAccessRights(CurrentUser.PLoginRegister)) 
            {
                clsShowLoginRegisterScreen::ShowAllUserTheyOpenedSystem();
            }
    }

    static void _ShowDeleteAllUsersFromLoginRegisterScreen() {
        if (clsScreen::CheckAccessRights(CurrentUser.pDeleteAllUsersFromFileLoginRegisters)){
            clsDeleteAllUserFromFileLoginRegisterScreen::DeleteAllUserFromFileLoginRegisterOperation();
        }
    }

    static void _ShowMainMeneuForCurrencyExchange() {

    }

    static void _Logout() {
        CurrentUser = clsUser::Find("", "");   
    }


    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
        system("cls");
        switch (MainMenueOption) {
        case enMainMenueOptions::eListClients:
        {
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
             
        case enMainMenueOptions::eDeleteClient:
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:

            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLoginRegister:
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteAllUserFromLoginRegisterFile:
            _ShowDeleteAllUsersFromLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurreuncyExchange : {
            clsMainMeneuCurrencyScreen::ShowMainMeneuCurrencyExchange();
            _GoBackToMainMenue();
            break;
            }

        case enMainMenueOptions::eLogout:
            _Logout();
            break;
        }
    }

public:
    static void ShowMainMenue() {
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Delete All Users From Login Register.\n";
        cout << setw(37) << left << "" << "\t[10] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[11] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());   
    }
};
