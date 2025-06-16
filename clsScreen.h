#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h";

using namespace std;

class clsScreen {
private : 
    static void _PrintNameOfUserInAllScreen() {
        cout << "\t\t\t\t\tUser : " << CurrentUser.UserName << endl;
    }
    static void _PrintTheLatestDate() {
        clsDate Date;
        cout << "\t\t\t\t\tDate : "; Date.PrintLatestDate();
    }
protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        _PrintNameOfUserInAllScreen();
        _PrintTheLatestDate();
    }
    
 
    static bool CheckAccessRights(clsUser::enPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }

};