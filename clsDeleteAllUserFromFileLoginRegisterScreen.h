#pragma once
#include "clsShowLoginRegisterScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";
class clsDeleteAllUserFromFileLoginRegisterScreen : protected clsScreen {
public :
	static void DeleteAllUserFromFileLoginRegisterOperation() {
		clsShowLoginRegisterScreen::ShowAllUserTheyOpenedSystem("\tDelete All User Screen");
		if (clsInputValidate::AskToDoYesOrNo("\n\t\t   Are You Sure You Want To Delete All Users From Login Register File [y/n] ? ")) {
			clsUser::DeleteAllUserFromLoginRegister();
			system("cls");
			clsShowLoginRegisterScreen::ShowAllUserTheyOpenedSystem();
			cout << "\n\n\t\t\t\tAll User Is Deleted Successfully From File Register ... " << endl;
		}
		else
			cout << "\n\n\t\t\tOperation For Deleted All Users From Login Register File Is Canceled .... " << endl;
	}
};

