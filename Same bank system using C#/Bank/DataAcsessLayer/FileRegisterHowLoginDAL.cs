using DataAcsessLayer;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace DataAcsessLayer
{


    public class FileRegisterHowLoginDAL
    {
        static string connectionString = "Server=.;Database=BANKDATABASE;Trusted_Connection=True;TrustServerCertificate=True;";

        public bool InsertLoginLog(FileRegisterHowLogin log)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = @"INSERT INTO FileRegisterHowLogin (LogDateTime, UserName, Password, Result)
                             VALUES (@LogDateTime, @UserName, @Password, @Result)";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@LogDateTime", log.LogDateTime);
                cmd.Parameters.AddWithValue("@UserName", log.UserName);
                cmd.Parameters.AddWithValue("@Password", log.Password);
                cmd.Parameters.AddWithValue("@Result", log.Result);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        // Get All Login Logs
        public List<FileRegisterHowLogin> GetAllLoginLogs()
        {
            List<FileRegisterHowLogin> logs = new List<FileRegisterHowLogin>();
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM FileRegisterHowLogin ORDER BY LogID DESC";
                SqlCommand cmd = new SqlCommand(query, conn);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        logs.Add(ReadLoginLog(reader));
                    }
                }
            }
            return logs;
        }

        // Helper to read
        private FileRegisterHowLogin ReadLoginLog(SqlDataReader reader)
        {
            return new FileRegisterHowLogin
            {
                LogID = (int)reader["LogID"],
                LogDateTime = reader["LogDateTime"].ToString(),
                UserName = reader["UserName"].ToString(),
                Password = reader["Password"].ToString(),
                Result = Convert.ToInt32(reader["Result"])
            };
        }

        public List<FileRegisterHowLogin> GetLoginLogsByUser(string userName)
        {
            List<FileRegisterHowLogin> logs = new List<FileRegisterHowLogin>();
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM FileRegisterHowLogin WHERE UserName = @UserName ORDER BY LogID DESC";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@UserName", userName);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        logs.Add(ReadLoginLog(reader));
                    }
                }
            }
            return logs;
        }

    }
}