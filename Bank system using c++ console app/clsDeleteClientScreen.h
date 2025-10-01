#pragma once
#include<iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
class clsDeleteClientScreen : protected clsScreen {
private : 
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
	static void ShowDeleteClientScreen() {
		_DrawScreenHeader("\tDelete Client Screen");
		string AccountNumber = clsInputValidate::ReadString("\nEnter Account Number : ");
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number Is Not Exist , Enter Another One : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        if (clsInputValidate::AskToDoYesOrNo("\nAre u Sure you Want To Delete This Client [y/n] ? ")) {
            if (Client.Delete()) {
                cout << "\nClient Deleted Successfuly :) " << endl;
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError , Client Was Not Deleted From File ... " << endl;
            }
       }
	}

};

