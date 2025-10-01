#pragma once
#include <iomanip>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsCurrenciesListScreen.h";
#include "clsFindCurrencyScreen.h";
#include "clsCalculateCurrencyScreen.h";
#include "clsUpdateCurrencyRateScreen.h";

class clsMainMeneuCurrencyScreen : protected clsScreen
{
private : 
    enum enMainMenueCurrencyOptions {eListCurrencies = 1 , eFindCurrency = 2 , eUpdateRate = 3 , eCurrencyClaculator = 4 , MainMeneu = 5
    };

    static void _GoBackToMainCurrencyScreen() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMeneuCurrencyExchange();
    }
    static short _ReadMainMenueFromCurrencyOption() {
        cout << setw(37) << left << "" << "{ Choose what do you want to do? [1 to 5] } ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _ShowListCurrenciesScreen() {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::FindCurrenyScreen();
    }

    static void _ShowUpdateRateScreen() {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCalculateCurrencyScreen() {
        clsCalculateCurrencyScreen::ShowCalculateCurrencyScreen();
    }


    static void _PerfromMainMenueCurrencyOption(enMainMenueCurrencyOptions MainMenueCurrencyOption) {
        system("cls");
        switch (MainMenueCurrencyOption){

        case clsMainMeneuCurrencyScreen::eListCurrencies: { 
            _ShowListCurrenciesScreen(); _GoBackToMainCurrencyScreen(); break;
        }
           
        case clsMainMeneuCurrencyScreen::eFindCurrency: {
            _ShowFindCurrencyScreen(); _GoBackToMainCurrencyScreen(); break;
        }
          
        case clsMainMeneuCurrencyScreen::eUpdateRate: {
            _ShowUpdateRateScreen(); _GoBackToMainCurrencyScreen(); break;
        }
       
        case clsMainMeneuCurrencyScreen::eCurrencyClaculator: {
            _ShowCalculateCurrencyScreen(); _GoBackToMainCurrencyScreen();  break;
        }
      
        case clsMainMeneuCurrencyScreen::MainMeneu: {
           
        }   
        }
    }

public : 

	static void ShowMainMeneuCurrencyExchange() {
        system("cls");
        _DrawScreenHeader("   Currency Exchange Main Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Meneu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Meneu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromMainMenueCurrencyOption(static_cast<enMainMenueCurrencyOptions>(_ReadMainMenueFromCurrencyOption()));

	}





};

