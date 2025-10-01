using DataAcsessLayer;
using System;
using System.Collections.Generic;


namespace BusinessAccsesLayer
{
    public class FileRegisterHowLoginBAL
    {
        private FileRegisterHowLoginDAL _dal = new FileRegisterHowLoginDAL();

        public bool AddLoginLog(FileRegisterHowLogin log)
        {
            return _dal.InsertLoginLog(log);
        }

        public List<FileRegisterHowLogin> GetAllLoginLogs()
        {
            return _dal.GetAllLoginLogs();
        }

        public List<FileRegisterHowLogin> GetLoginLogsByUser(string userName)
        {
            return _dal.GetLoginLogsByUser(userName);
        }
    }
}
