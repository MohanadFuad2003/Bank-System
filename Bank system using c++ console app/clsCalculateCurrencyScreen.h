#pragma once
#include "clsCurrency.h";
#include "clsScreen.h";
#include "clsInputValidate.h";
class clsCalculateCurrencyScreen : protected clsScreen {

private :
	static void _PrintCurrencyRecord(clsCurrency& Currency , string msg = "") {
		cout << msg << endl;
		cout << "\n______________________________\n";
		cout << "\nCountry : " << Currency.Country();
		cout << "\nCode : " << Currency.CurrencyCode() << endl;
		cout << "Name : " << Currency.CurrencyName();
		cout << "\nRate : " << Currency.Rate() << endl;
		cout << "_______________________________\n" << endl;
	}

	static clsCurrency _ReadAllCurrency( string msg = "") {
		string Code = clsInputValidate::ReadString(msg);
		while (!clsCurrency::IsCurrencyExist(Code)) {
			Code = clsInputValidate::ReadString("\nInvalid Currency Code [Not Exist In File] , Try Again : ");
		}
		return clsCurrency::FindByCode(Code);
	}

	static float _ReadAmountToExchange() {
		cout << "\nEnter Amount To Exchange : ";
		float Amount = clsInputValidate::ReadFloatNumber();
		return Amount;
	}

public : 
	static void ShowCalculateCurrencyScreen() {

		_DrawScreenHeader("\tCalculate Currency Screen");
		clsCurrency FirstCurrency = _ReadAllCurrency("\nPlease Enter Currency1 Code : ");
		clsCurrency SecondCurrency = _ReadAllCurrency("\nPlease Enter Currency2 Code : ");
		float Amount = _ReadAmountToExchange();
		_PrintCurrencyRecord(FirstCurrency, "\nConvert From : ");
		if (FirstCurrency.CurrencyCode() == (clsString::UpperAllString("USD"))) {
			cout << Amount << " USD = " << clsCurrency::CalculateCurrencyFromDloarToAnyThings(Amount, SecondCurrency.Rate()) // 100 USD = 
				<< " " << SecondCurrency.CurrencyCode() << endl;
		}
		else if (SecondCurrency.CurrencyCode() == clsString::UpperAllString("USD")) { // first = jod  , usd   , 100
			cout << Amount << " " << FirstCurrency.CurrencyCode() << " = "
				<< clsCurrency::CalculateCurrencyFromAnyThingsToDolar(Amount, FirstCurrency.Rate()) << " USD " << endl;
		}
		else
		{

			cout << Amount << " " << FirstCurrency.CurrencyCode() << " = ";
			float Temper = clsCurrency::CalculateCurrencyFromAnyThingsToDolar(Amount, FirstCurrency.Rate());
			cout << Temper << " USD " << endl << endl;
			cout << "Converting From USD To : " << endl;
			_PrintCurrencyRecord(SecondCurrency, "\nConvert To : ");
			cout << Amount << " " << FirstCurrency.CurrencyCode() << " = " << clsCurrency::CalculateCurrencyFromDloarToAnyThings(Temper, SecondCurrency.Rate()) // 100 USD = 
				<< " " << SecondCurrency.CurrencyCode() << endl;

		}
	}
};

// --- to dolar  = /
// dolar to --- = *