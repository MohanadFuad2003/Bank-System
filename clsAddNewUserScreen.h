#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen {
private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
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

    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer = 'n';
        if (clsInputValidate::AskToDoYesOrNo("\nDo you want to give full access? y/n? "))
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

     
        if (clsInputValidate::AskToDoYesOrNo("\nShow Client List? [y/n] ? "))
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        if (clsInputValidate::AskToDoYesOrNo("\nAdd New Client? [y/n] ? "))
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        if (clsInputValidate::AskToDoYesOrNo("\nDelete Client? [y/n] ? "))
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

    
     
        if (clsInputValidate::AskToDoYesOrNo("\nUpdate Client? [y/n] ? "))
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        if (clsInputValidate::AskToDoYesOrNo("\nFind Client? [y/n] ? "))
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        if (clsInputValidate::AskToDoYesOrNo("\nTransactions? y/n? "))
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        if (clsInputValidate::AskToDoYesOrNo("\nManage Users? y/n? "))
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        if (clsInputValidate::AskToDoYesOrNo("\nLogin Register Screen ? [y/n] ? "))
        {
            Permissions += clsUser::enPermissions::PLoginRegister;
        }

        return Permissions;

    }

public:

    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
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
    }
};

