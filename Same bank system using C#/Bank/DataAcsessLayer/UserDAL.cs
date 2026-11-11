using DataAcsessLayer.DataAcsessLayer.Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace DataAcsessLayer
{
    public static class PasswordUtil
    {
        public static string Encrypt(string plain)
        {
            return Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(plain));
        }
        public static string Decrypt(string encrypted)
        {
            try
            {
                return System.Text.Encoding.UTF8.GetString(Convert.FromBase64String(encrypted));
            }
            catch { return ""; }
        }
    }

    public class UsersDAL
    {
        static string connectionString = "Server=.;Database=BANKDATABASE;Trusted_Connection=True;TrustServerCertificate=True;";

        public bool AddUser(User user)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = @"INSERT INTO users 
                (FirstName, LastName, Email, Phone, UserName, Password, Result) 
                VALUES (@FirstName, @LastName, @Email, @Phone, @UserName, @Password, @Result)";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@FirstName", user.FirstName);
                cmd.Parameters.AddWithValue("@LastName", user.LastName);
                cmd.Parameters.AddWithValue("@Email", user.Email);
                cmd.Parameters.AddWithValue("@Phone", user.Phone);
                cmd.Parameters.AddWithValue("@UserName", user.UserName);
                cmd.Parameters.AddWithValue("@Password", PasswordUtil.Encrypt(user.Password));
                cmd.Parameters.AddWithValue("@Result", user.Result); 
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        public bool UpdateUser(User user)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = @"UPDATE users SET 
                    FirstName = @FirstName,
                    LastName = @LastName,
                    Email = @Email,
                    Phone = @Phone,
                    Password = @Password,
                    Result = @Result
                    WHERE UserName = @UserName";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@FirstName", user.FirstName);
                cmd.Parameters.AddWithValue("@LastName", user.LastName);
                cmd.Parameters.AddWithValue("@Email", user.Email);
                cmd.Parameters.AddWithValue("@Phone", user.Phone);
                cmd.Parameters.AddWithValue("@Password", PasswordUtil.Encrypt(user.Password));
                cmd.Parameters.AddWithValue("@Result", user.Result);
                cmd.Parameters.AddWithValue("@UserName", user.UserName);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        public bool DeleteUser(string userName)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "DELETE FROM users WHERE UserName = @UserName";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@UserName", userName);
                conn.Open();
                int rows = cmd.ExecuteNonQuery();
                return rows > 0;
            }
        }

        public User FindByUserName(string userName)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM users WHERE UserName = @UserName";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@UserName", userName);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    if (reader.Read())
                        return ReadUser(reader);
                }
            }
            return null;
        }

        public User FindByUserNameAndPassword(string userName, string password)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM users WHERE UserName = @UserName AND Password = @Password";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@UserName", userName);
                cmd.Parameters.AddWithValue("@Password", PasswordUtil.Encrypt(password));
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    if (reader.Read())
                        return ReadUser(reader);
                }
            }
            return null;
        }

        public bool IsUserExist(string userName)
        {
            return FindByUserName(userName) != null;
        }

        public bool IsUserExist(string userName, string password)
        {
            return FindByUserNameAndPassword(userName, password) != null;
        }

        public List<User> GetAllUsers()
        {
            List<User> users = new List<User>();
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM users ORDER BY UserID DESC";
                SqlCommand cmd = new SqlCommand(query, conn);
                conn.Open();
                using (SqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        users.Add(ReadUser(reader));
                    }
                }
            }
            return users;
        }

        private User ReadUser(SqlDataReader reader)
        {
            return new User
            {
                UserID = (int)reader["UserID"],
                FirstName = reader["FirstName"].ToString(),
                LastName = reader["LastName"].ToString(),
                Email = reader["Email"].ToString(),
                Phone = reader["Phone"].ToString(),
                UserName = reader["UserName"].ToString(),
                Password = PasswordUtil.Decrypt(reader["Password"].ToString()),
                Result = Convert.ToInt32(reader["Result"]) // Permissions = Result
            };
        }
    }
}

