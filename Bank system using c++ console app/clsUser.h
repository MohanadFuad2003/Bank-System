#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include "clsUtil.h";
#include <fstream>

using namespace std;
class clsUser : public clsPerson {
private:
    static const short EncryptKey = 153;
    struct _strFileRegister;

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    static _strFileRegister _ConvertLineFromFileRegisterToRecord(string Line, string Seperator = "#//#") {
        vector<string> store = clsString::Split(Line, Seperator);
        _strFileRegister strRegister;
        strRegister.DateTime = store[0];
        strRegister.UserName = store[1];
        strRegister.Password = clsUtil::EncryptText(store[2]);
        strRegister.Permissions = stoi(store[3]);
        return strRegister;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4],clsUtil::DecryptText( vUserData[5] , EncryptKey), stoi(vUserData[6]));
    }
     void _AddDataLineForLoginRegisterFile(string strLine) {
        fstream FileReg;
        FileReg.open("FileRegister.txt", ios::in | ios::app);
        if (FileReg.is_open()) {
            FileReg << strLine << endl;
            FileReg.close();
        }
    }
     string _ConvertAllRegisterLoginToOneLineWithSeperator(string Seperator = "#//#") {
        string Result = clsDate::DateToString(clsDate()) + " - " + clsDate::GetTheLatestTimer();
        Result += Seperator;
        Result += this->UserName + Seperator;
        Result += this->Password + Seperator;
        Result += to_string(this->GetPermissions());
        return Result;
    }
    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += (clsUtil::EncryptText(User.GetPassword() , EncryptKey)) + Seperator;
        UserRecord += to_string(User.Permissions);
        return UserRecord;
    }


    static vector<_strFileRegister> _LoadDataFromRegisterFile() {
        fstream File;
        vector<_strFileRegister> StoreRecord;
        File.open("FileRegister.txt", ios::in);
        if (File.is_open()) {
            string Line;
            while (getline(File, Line)) {
                StoreRecord.push_back(_ConvertLineFromFileRegisterToRecord(Line));
            }
            File.close();
        }
        return StoreRecord;
    }

    static  vector <clsUser> _LoadUsersDataFromFile() {
        vector <clsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite
        string DataLine;
        if (MyFile.is_open())  {
            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew() {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject() {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    //------------------------------------------------------------------------------------------------------------------------

public:
    struct _strFileRegister {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, PLoginRegister = 128 , pDeleteAllUsersFromFileLoginRegisters = 265
    };

    clsUser(enMode Mode, string FirstName, string LastName,string Email, string Phone, string UserName, string Password,  int Permissions) : clsPerson(FirstName, LastName, Email, Phone) {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
    }

    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    static bool IsUserExist(string UserName , string Password) {
        clsUser User = clsUser::Find(UserName , Password); // empty or Full
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

     bool CheckAccessPermission(enPermissions ThePermissions) {
         if (this->Permissions == enPermissions::eAll)
             return true;
         if ((ThePermissions & this->Permissions) != ThePermissions) {
             return false;
         }
         return true;
    }

      void OperationForSaveRegistersToFile() {
         _AddDataLineForLoginRegisterFile(_ConvertAllRegisterLoginToOneLineWithSeperator());
     }

      static vector<_strFileRegister> GetAllUserListFromFileRegister() {
          return _LoadDataFromRegisterFile();
    }

      static void DeleteAllUserFromLoginRegister() {
          fstream FileReg;
          FileReg.open("FileRegister.txt", ios::out);
    }
  
};