using DataAcsessLayer;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace DataAcsessLayer
{
    public class BankClientDAL
    {
        static string connectionString = "Server=.;Database=BANKDATABASE;Trusted_Connection=True;TrustServerCertificate=True;";
        public BankClient GetClientByAccountNumber(string accountNumber)
        {
            BankClient client = null;
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Clients WHERE AccountNumber = @AccountNumber";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@AccountNumber", accountNumber);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        client = ReadClient(reader);
                    }
                }
            }
            return client;
        }

        public BankClient GetClientByAccountNumberAndPin(string accountNumber, string pin)
        {
            BankClient client = null;
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Clients WHERE AccountNumber = @AccountNumber AND Pin = @Pin";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@AccountNumber", accountNumber);
                cmd.Parameters.AddWithValue("@Pin", pin);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        client = ReadClient(reader);
                    }
                }
            }
            return client;
        }

        // Get all clients
        public List<BankClient> GetClients()
        {
            List<BankClient> clients = new List<BankClient>();
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Clients";
                SqlCommand cmd = new SqlCommand(query, conn);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        clients.Add(ReadClient(reader));
                    }
                }
            }
            return clients;
        }

        // Add new client
        [Obsolete]
        public bool AddClient(BankClient client)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = @"INSERT INTO Clients (FirstName, LastName, Email, Phone, AccountNumber, Pin, Balance, UserName)
                             VALUES (@FirstName, @LastName, @Email, @Phone, @AccountNumber, @Pin, @Balance, @UserName)";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@FirstName", client.FirstName);
                cmd.Parameters.AddWithValue("@LastName", client.LastName);
                cmd.Parameters.AddWithValue("@Email", client.Email);
                cmd.Parameters.AddWithValue("@Phone", client.Phone);
                cmd.Parameters.AddWithValue("@AccountNumber", client.AccountNumber);
                cmd.Parameters.AddWithValue("@Pin", client.PinCode);
                cmd.Parameters.AddWithValue("@Balance", client.Balance);
                cmd.Parameters.AddWithValue("@UserName", client.UserName);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        // Update existing client
        public bool UpdateClient(BankClient client)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = @"UPDATE Clients SET 
                                FirstName = @FirstName,
                                LastName = @LastName,
                                Email = @Email,
                                Phone = @Phone,
                                Pin = @Pin,
                                Balance = @Balance,
                                UserName = @UserName
                             WHERE AccountNumber = @AccountNumber";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@FirstName", client.FirstName);
                cmd.Parameters.AddWithValue("@LastName", client.LastName);
                cmd.Parameters.AddWithValue("@Email", client.Email);
                cmd.Parameters.AddWithValue("@Phone", client.Phone);
                cmd.Parameters.AddWithValue("@Pin", client.PinCode);
                cmd.Parameters.AddWithValue("@Balance", client.Balance);
                cmd.Parameters.AddWithValue("@UserName", client.UserName);
                cmd.Parameters.AddWithValue("@AccountNumber", client.AccountNumber);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        // Delete client
        public bool DeleteClient(string accountNumber)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "DELETE FROM Clients WHERE AccountNumber = @AccountNumber";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@AccountNumber", accountNumber);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        // Update Balance only
        public bool UpdateBalance(string accountNumber, decimal newBalance)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "UPDATE Clients SET Balance = @Balance WHERE AccountNumber = @AccountNumber";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@Balance", newBalance);
                cmd.Parameters.AddWithValue("@AccountNumber", accountNumber);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        // Check if client exists
        public bool IsClientExist(string accountNumber)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT COUNT(*) FROM Clients WHERE AccountNumber = @AccountNumber";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@AccountNumber", accountNumber);
                conn.Open();
                int count = (int)cmd.ExecuteScalar();
                return count > 0;
            }
        }

        // Get total balances
        public decimal GetTotalBalances()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT SUM(Balance) FROM Clients";
                SqlCommand cmd = new SqlCommand(query, conn);
                conn.Open();
                object result = cmd.ExecuteScalar();
                return result == DBNull.Value ? 0 : Convert.ToDecimal(result);
            }
        }

        // Insert Transfer Log
        public bool InsertTransferLog(string transferDateTime, string fromAccount, string toAccount,
                                     decimal amount, decimal fromAccBalance, decimal toAccBalance, string doneBy)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = @"INSERT INTO TransferLog (TransferDateTime, FromAccount, ToAccount, Amount, FromAccountBalance, ToAccountBalance, DoneBy)
                             VALUES (@TransferDateTime, @FromAccount, @ToAccount, @Amount, @FromAccountBalance, @ToAccountBalance, @DoneBy)";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@TransferDateTime", transferDateTime);
                cmd.Parameters.AddWithValue("@FromAccount", fromAccount);
                cmd.Parameters.AddWithValue("@ToAccount", toAccount);
                cmd.Parameters.AddWithValue("@Amount", amount);
                cmd.Parameters.AddWithValue("@FromAccountBalance", fromAccBalance);
                cmd.Parameters.AddWithValue("@ToAccountBalance", toAccBalance);
                cmd.Parameters.AddWithValue("@DoneBy", doneBy);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        // Get all transfer logs
        public List<TransferLogRecord> GetTransferLogs()
        {
            List<TransferLogRecord> logs = new List<TransferLogRecord>();
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM TransferLog ORDER BY TransferID DESC";
                SqlCommand cmd = new SqlCommand(query, conn);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        logs.Add(ReadTransferLog(reader));
                    }
                }
            }
            return logs;
        }

        // ---------------- Helpers ----------------

        private BankClient ReadClient(SqlDataReader reader)
        {
            return new BankClient
            {
                ClientID = (int)reader["ClientID"],
                FirstName = reader["FirstName"].ToString(),
                LastName = reader["LastName"].ToString(),
                Email = reader["Email"].ToString(),
                Phone = reader["Phone"].ToString(),
                AccountNumber = reader["AccountNumber"].ToString(),
                PinCode = reader["Pin"].ToString(),
                Balance = (decimal)reader["Balance"],
                UserName = reader["UserName"].ToString()
            };
        }

        private TransferLogRecord ReadTransferLog(SqlDataReader reader)
        {
            return new TransferLogRecord
            {
                TransferID = (int)reader["TransferID"],
                TransferDateTime = reader["TransferDateTime"].ToString(),
                FromAccount = reader["FromAccount"].ToString(),
                ToAccount = reader["ToAccount"].ToString(),
                Amount = (decimal)reader["Amount"],
                FromAccountBalance = (decimal)reader["FromAccountBalance"],
                ToAccountBalance = (decimal)reader["ToAccountBalance"],
                DoneBy = reader["DoneBy"].ToString()
            };
        }
    }
}