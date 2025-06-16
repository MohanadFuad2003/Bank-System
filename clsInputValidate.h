
#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate {
public:
	static bool IsNumberBetween(short Number, short From, short To) {
		if ((Number >= From && Number <= To) || (Number <= From && Number >= To) )
			return true;
		else
			return false;
	}
	static bool AskToDoYesOrNo(string msg = "", string ErrorMessage = "Invalid input, please enter 'y' or 'n' only.\n") {
		if (msg != "")
			cout << msg;
		char ch = 'n';
		while (true) {
			cin >> ch;

			ch = tolower(ch);

			if (ch == 'y' || ch== 'n') {
				break;  
			}
			else {
				cout << ErrorMessage << endl;
			}
		}
		return (ch) == ('y');
	}

	static bool IsNumberBetween(int Number, int From, int To) {
		if ((Number >= From && Number <= To) || (Number <= From && Number >= To))
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(float Number, float From, float To) {
		if ((Number >= From && Number <= To) || (Number <= From && Number >= To))
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To) {
		if ((Number >= From && Number <= To) || (Number <= From && Number >= To))
			return true;
		else
			return false;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)) 
		&& 
		(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
		{
			return true;
		}

		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
		&&
		(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))) 
		{
			return true;
		}
		return false;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string msg) {
		short Number = ReadShortNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << msg;
			Number = ReadShortNumber();
			cout << endl;
		}
		return Number;
	}

	static bool IsValideDate(clsDate Date) {
		return	clsDate::IsValidDate(Date);
	}

	static string ReadString(string msg = "") {
		string MyString = "";
		cout << msg;
		getline(cin >> ws, MyString);
		return MyString;
	}
};