<h1 align="center">🏦 Bank System</h1>

<p align="center">
  The same banking system built twice: first as a <b>C++ console app</b>, then as a layered <b>C# ASP.NET Core Web API</b>.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-OOP-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/C%23-ASP.NET%20Core%20Web%20API-512BD4?style=for-the-badge&logo=dotnet&logoColor=white" alt="ASP.NET Core">
  <img src="https://img.shields.io/badge/SQL%20Server-Database-CC2927?style=for-the-badge" alt="SQL Server">
</p>

---

## 🖥️ Version 1 – C++ console app

A menu-driven console application written with object-oriented C++.

- 🔑 **Login** with an admin account and limited users
- 🛡️ **Permissions** stored as bit flags, so each user only sees the screens they are allowed to use
- 👥 **Clients**: add, update, delete, find and list clients
- 💵 **Transactions**: deposit, withdraw, transfer between clients and view total balances
- 🧾 **Logs**: login history and transfer log with date and time
- 💱 **Currency exchange**: list currencies, update rates and convert amounts
- 🗂️ **Storage**: simple text-file database

## 🌐 Version 2 – C# ASP.NET Core Web API

The same features rebuilt as a REST API with separate layers.

| Layer | Responsibility |
|---|---|
| `BankSystemAPILayer` | Controllers and endpoints |
| `BusinessAccsesLayer` | Business rules |
| `DataAcsessLayer` | SQL Server data access |

| Method | Endpoint |
|---|---|
| `GET` | `/api/BankClient/GetAllClients` |
| `GET` | `/api/BankClient/GetClient/{accountNumber}` |
| `POST` | `/api/BankClient/AddClient` |
| `PUT` | `/api/BankClient/UpdateClient` |
| `DELETE` | `/api/BankClient/{accountNumber}` |
| `POST` | `/api/BankClient/{accountNumber}/deposit` |
| `POST` | `/api/BankClient/{accountNumber}/withdraw` |
| `POST` | `/api/BankClient/transfer` |
| `GET` | `/api/BankClient/GetAllTransfers` |
| `GET` | `/api/BankClient/GetTotalBalances` |

## ▶️ How to run

- **C++ version:** open `OOP-SmallProject.sln` in Visual Studio and press **F5**.
- **C# version:** set the SQL Server connection string, open the solution and run `BankSystemAPILayer`.

---

<p align="center">Built by <a href="https://github.com/MohanadFuad2003">Muhannad Al-Oshaibe</a></p>
