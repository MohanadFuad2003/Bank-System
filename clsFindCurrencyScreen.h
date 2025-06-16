#pragma once
#include "clsCurrency.h";
#include "clsScreen.h";
class clsFindCurrencyScreen : protected clsScreen {
private :
	static void PrintCurrencyRecord(clsCurrency &Currency)
	{
		cout << "\n_______________________________";
		cout << "\nCountry : " << Currency.Country();
		cout << "\nCode : " << Currency.CurrencyCode() << endl;
		cout << "Name : " << Currency.CurrencyName();
		cout << "\nRate : " << Currency.Rate() << endl;
		cout << "_______________________________\n" << endl;
	}
	enum eFindBy { eByCurrencyCode = 1 , eByCountryName = 2};
	static short _ReadFindByCodeOrCountry() {
		cout << "\nFind By : ( [1] Code )   /  ( [2] Country ) ? ";
		short Number = 0;
		Number = clsInputValidate::ReadShortNumber();
		return Number;
	}

	static void _ShowResults(clsCurrency &Currency) {
		if (!Currency.IsEmpty()) {
			cout << "\nCurrency Found :-)\n";
			PrintCurrencyRecord(Currency);
		}
		else { cout << "\nCurrency Was not Found :-(\n"; }
	}


	static void _FindByCurrencyCode() {
		string Code = clsInputValidate::ReadString("\nPlease Enter Currency Code : ");
		clsCurrency CurrencyObject = clsCurrency::FindByCode(Code);
		_ShowResults(CurrencyObject);
	}

	static void _FindByCountry() {
		string Code = clsInputValidate::ReadString("\nPlease Enter Country Name : ");
		clsCurrency CurrencyObject = clsCurrency::FindByCountry(Code);
		_ShowResults(CurrencyObject);
	}

	static void _CheckWhatChooseToFindByCodeOrCountry() {
		eFindBy FinderChoose =static_cast<eFindBy> (_ReadFindByCodeOrCountry());
		switch (FinderChoose) {
		case clsFindCurrencyScreen::eByCurrencyCode: {	_FindByCurrencyCode(); break; }
		case clsFindCurrencyScreen::eByCountryName :  {  _FindByCountry();  break; }
		}}

public :
	static void FindCurrenyScreen() {
	   _DrawScreenHeader("\tFind Currency Screen");
	   _CheckWhatChooseToFindByCodeOrCountry();
	}
};

