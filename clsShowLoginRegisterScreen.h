#pragma once
#include "clsUser.h";
class clsShowLoginRegisterScreen : protected clsScreen
{
private :
    static void PrintLoginRegisterRecordLine(clsUser::_strFileRegister LoginRegisterRecord) {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    }

public :
	static void ShowAllUserTheyOpenedSystem(string Title = "") {
		vector<clsUser::_strFileRegister> strFileRegister = clsUser::GetAllUserListFromFileRegister();
        if (Title.empty()) { Title = "\tLogin Register List Screen"; }

        string SubTitle = "\t\t(" + to_string(strFileRegister.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (strFileRegister.size() == 0)
            cout << "\t\t\t\t    No Logins Available In the System!";
        else

            for (clsUser::_strFileRegister Record : strFileRegister)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}
};

