#pragma once
#include "Global.h";
#include "clsScreen.h";
#include <iostream>
#include "clsInputValidate.h";
class clsCreateTheFirstUserScreen : protected clsScreen {
private :
    static void _ReadUserInfo() {
        cout << "\nEnter FirstName: ";
        CurrentUser.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName: ";
        CurrentUser.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        CurrentUser.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        CurrentUser.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Password: ";
        CurrentUser.Password = clsInputValidate::ReadString();
        CurrentUser.Permissions = -1;
    }

    static void _PrintUser(clsUser User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

public :
	static void ShowCreateFirstUserScreen() {
		_DrawScreenHeader("No Users In File ,Create First User");
        string UserName = clsInputValidate::ReadString("\nEnter UserName : ");
        CurrentUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo();
        clsUser::enSaveResults SaveResult = CurrentUser.Save();
        switch (SaveResult) {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\n\nAdded The First User Is Done , Press Any Key For Back To Login Screen And Try The First User By { UserName And Password }\n";
            _PrintUser(CurrentUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject: {
            cout << "\nError User was not saved because it's Empty";
            break;
        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
        }
        system("pause>0");
	}

};

