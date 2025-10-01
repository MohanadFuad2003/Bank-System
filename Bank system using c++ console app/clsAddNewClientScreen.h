#pragma once
#include"clsBankClient.h";
#include"clsScreen.h";
#include "clsInputValidate.h";
#include<iostream>
using namespace std;
class clsAddNewClientScreen :protected clsScreen {
private : 
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

    static void _PrintClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

public : 
	static void ShowAddNewClientScreen() {
		_DrawScreenHeader("\tAdd New Client Screen");
       
		string AccountNumber = clsInputValidate::ReadString("\nEnter Account Number : ");
		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number Is Already Exist , Choose Another One : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::svFaildEmptyObject:  cout << "\nError Account Was Not Saved Because It's Empty";
            break;
        case clsBankClient::svSucceeded: cout << "\nAccount Added Successfuly :)\n";
            _PrintClient(Client);
            break;
        case clsBankClient::svFaildAccountNumberExists:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
	}
};

