using DataAcsessLayer;
using DataAcsessLayer.DataAcsessLayer.Models;
using System.Collections.Generic;


namespace BusinessAccsesLayer
{
    [Flags]
    public enum UserPermissions
    {
        All = -1,
        ListClients = 1,
        AddNewClient = 2,
        DeleteClient = 4,
        UpdateClients = 8,
        FindClient = 16,
        Transactions = 32,
        ManageUsers = 64,
        LoginRegister = 128,
        DeleteAllUsersFromFileLoginRegisters = 256
    }



    public class UserBAL
    {
        private readonly UsersDAL _dal = new UsersDAL();

        public List<User> GetAllUsers()
        {
            return _dal.GetAllUsers();
        }

        public User FindByUserName(string userName)
        {
            return _dal.FindByUserName(userName);
        }

        public User FindByUserNameAndPassword(string userName, string password)
        {
            return _dal.FindByUserNameAndPassword(userName, password);
        }

        public bool IsUserExist(string userName)
        {
            return _dal.IsUserExist(userName);
        }

        public bool IsUserExist(string userName, string password)
        {
            return _dal.IsUserExist(userName, password);
        }

        public bool AddUser(User user)
        {
            if (IsUserExist(user.UserName))
                return false;
            return _dal.AddUser(user);
        }

        public bool UpdateUser(User user)
        {
            if (!IsUserExist(user.UserName))
                return false;
            return _dal.UpdateUser(user);
        }

        public bool DeleteUser(string userName)
        {
            if (!IsUserExist(userName))
                return false;
            return _dal.DeleteUser(userName);
        }

        public static UserPermissions GetUserPermissions(User user)
        {
            return (UserPermissions)user.Result;
        }

        public static bool HasPermission(User user, UserPermissions permission)
        {
            var userPerm = GetUserPermissions(user);
            if (userPerm == UserPermissions.All) return true;
            return (userPerm & permission) == permission;
        }
    }
}
