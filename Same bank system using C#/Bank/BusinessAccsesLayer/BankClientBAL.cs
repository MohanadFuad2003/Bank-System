using DataAcsessLayer;
using System;
using System.Collections.Generic;

namespace BusinessAccsesLayer
{
    public class BankClientBAL
    {
        private BankClientDAL _dal = new BankClientDAL();

        public bool AddClient(BankClient client)
        {
            if (_dal.IsClientExist(client.AccountNumber))
                return false;
            return _dal.AddClient(client);
        }

        public bool UpdateClient(BankClient client)
        {
            if (!_dal.IsClientExist(client.AccountNumber))
                return false;
            return _dal.UpdateClient(client);
        }

        public bool DeleteClient(string accountNumber)
        {
            return _dal.DeleteClient(accountNumber);
        }

        public BankClient FindByAccountNumber(string accountNumber)
        {
            return _dal.GetClientByAccountNumber(accountNumber);
        }

        public BankClient FindByAccountAndPin(string accountNumber, string pin)
        {
            return _dal.GetClientByAccountNumberAndPin(accountNumber, pin);
        }

        public List<BankClient> GetAllClients()
        {
            return _dal.GetClients();
        }

        public bool IsClientExist(string accountNumber)
        {
            return _dal.IsClientExist(accountNumber);
        }

        public bool Deposit(string accountNumber, decimal amount)
        {
            var client = _dal.GetClientByAccountNumber(accountNumber);
            if (client == null) return false;
            client.Balance += amount;
            return _dal.UpdateBalance(accountNumber, client.Balance);
        }

        public bool Withdraw(string accountNumber, decimal amount)
        {
            var client = _dal.GetClientByAccountNumber(accountNumber);
            if (client == null) return false;
            if (client.Balance < amount) return false;
            client.Balance -= amount;
            return _dal.UpdateBalance(accountNumber, client.Balance);
        }

        public bool Transfer(string fromAccount, string toAccount, decimal amount, string doneBy)
        {
            var fromClient = _dal.GetClientByAccountNumber(fromAccount);
            var toClient = _dal.GetClientByAccountNumber(toAccount);
            if (fromClient == null || toClient == null) return false;
            if (fromClient.Balance < amount) return false;

            decimal newFromBalance = fromClient.Balance - amount;
            decimal newToBalance = toClient.Balance + amount;

            bool update1 = _dal.UpdateBalance(fromAccount, newFromBalance);
            bool update2 = _dal.UpdateBalance(toAccount, newToBalance);

            string transferDateTime = DateTime.Now.ToString("dd/MM/yyyy - HH:mm:ss");
            bool log = _dal.InsertTransferLog(transferDateTime, fromAccount, toAccount, amount, newFromBalance, newToBalance, doneBy);

            return update1 && update2 && log;
        }

        public decimal GetTotalBalances()
        {
            return _dal.GetTotalBalances();
        }

        public List<TransferLogRecord> GetAllTransferLogs()
        {
            return _dal.GetTransferLogs();
        }

        public bool Deposit(BankClient client, decimal amount)
        {
            client.Balance += amount;
            return _dal.UpdateBalance(client.AccountNumber, client.Balance);
        }

        public bool Withdraw(BankClient client, decimal amount)
        {
            if (client.Balance < amount) return false;
            client.Balance -= amount;
            return _dal.UpdateBalance(client.AccountNumber, client.Balance);
        }

        public bool Save(BankClient client, bool isNew)
        {
            if (isNew)
                return AddClient(client);
            else
                return UpdateClient(client);
        }
    }
}
