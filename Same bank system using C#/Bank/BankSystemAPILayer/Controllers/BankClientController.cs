using BusinessAccsesLayer;
using DataAcsessLayer;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace BankSystemAPI.Controllers
{
    [ApiController]
    [Route("api/BankClient")]
    public class BankClientController : ControllerBase
    {
        private readonly BankClientBAL _bal = new BankClientBAL();

        [HttpGet("GetAllClients")]
        public ActionResult<List<BankClient>> GetAllClients()
        {
            var clients = _bal.GetAllClients();
            return Ok(clients);
        }

        [HttpGet("GetClient/{accountNumber}")]
        public ActionResult<BankClient> GetClient(string accountNumber)
        {
            var client = _bal.FindByAccountNumber(accountNumber);
            if (client == null)
                return NotFound();
            return Ok(client);
        }

        [HttpGet("FindByAccountAndPin")]
        public ActionResult<BankClient> FindByAccountAndPin([FromQuery] string accountNumber, [FromQuery] string pin)
        {
            var client = _bal.FindByAccountAndPin(accountNumber, pin);
            if (client == null)
                return NotFound();
            return Ok(client);
        }

        [HttpPost("AddClient")]
        public ActionResult AddClient([FromBody] BankClient client)
        {
            if (_bal.IsClientExist(client.AccountNumber))
                return BadRequest("Account number already exists.");

            var result = _bal.AddClient(client);
            if (!result) return BadRequest("Failed to add client.");
            return Ok("Client added successfully.");
        }

        [HttpPut("UpdateClient")]
        public ActionResult UpdateClient([FromBody] BankClient client)
        {
            if (!_bal.IsClientExist(client.AccountNumber))
                return NotFound("Client not found.");

            var result = _bal.UpdateClient(client);
            if (!result) return BadRequest("Failed to update client.");
            return Ok("Client updated successfully.");
        }

        [HttpDelete("{accountNumber}")]
        public ActionResult DeleteClient(string accountNumber)
        {
            if (!_bal.IsClientExist(accountNumber))
                return NotFound("Client not found.");

            var result = _bal.DeleteClient(accountNumber);
            if (!result) return BadRequest("Failed to delete client.");
            return Ok("Client deleted successfully.");
        }

        [HttpPost("{accountNumber}/deposit")]
        public ActionResult Deposit(string accountNumber, [FromQuery] decimal amount)
        {
            if( amount <= 0) return BadRequest("Deposit amount must be positive."); 

            var result = _bal.Deposit(accountNumber, amount);
            if (!result) return BadRequest("Failed to deposit amount.");
            return Ok("Deposit successful.");
        }

        [HttpPost("{accountNumber}/withdraw")]
        public ActionResult Withdraw(string accountNumber, [FromQuery] decimal amount)
        {
            if (amount <= 0) return BadRequest("Withdraw amount must be positive.");    
            var result = _bal.Withdraw(accountNumber, amount);
            if (!result) return BadRequest("Failed to withdraw amount. Maybe insufficient balance.");
            return Ok("Withdraw successful.");
        }

        [HttpPost("transfer")]
        public ActionResult Transfer([FromBody] TransferRequest request)
        {
            var result = _bal.Transfer(request.FromAccount, request.ToAccount, request.Amount, request.DoneBy);
            if (!result) return BadRequest("Failed to transfer amount. Check balance or accounts.");
            return Ok("Transfer successful.");
        }

        [HttpGet("GetAllTransfers")]
        public ActionResult<List<TransferLogRecord>> GetAllTransfers()
        {
            var logs = _bal.GetAllTransferLogs();
            return Ok(logs);
        }

        [HttpGet("GetTotalBalances")]
        public ActionResult<decimal> GetTotalBalances()
        {
            var total = _bal.GetTotalBalances();
            return Ok(total);
        }
    }

    public class TransferRequest
    {
        public string  FromAccount { get; set; }
        public string ToAccount { get; set; }
        public decimal Amount { get; set; }
        public string DoneBy { get; set; }
    }
}
