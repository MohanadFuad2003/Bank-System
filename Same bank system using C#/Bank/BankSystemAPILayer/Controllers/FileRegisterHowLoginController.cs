using BusinessAccsesLayer;
using DataAcsessLayer;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace BankSystemAPI.Controllers
{
    [ApiController]
    [Route("api/FileRegisterHowLogin")]
    public class FileRegisterHowLoginController : ControllerBase
    {
        private readonly FileRegisterHowLoginBAL _bal = new FileRegisterHowLoginBAL();

        [HttpPost("AddLoginLog")]
        public ActionResult AddLoginLog([FromBody] FileRegisterHowLogin log)
        {
            var result = _bal.AddLoginLog(log);
            if (!result) return BadRequest("Failed to add login log.");
            return Ok("Login log added successfully.");
        }

        [HttpGet("GetAllLoginLogs")]
        public ActionResult<List<FileRegisterHowLogin>> GetAllLoginLogs()
        {
            var logs = _bal.GetAllLoginLogs();
            return Ok(logs);
        }

        [HttpGet("GetLoginLogsByUser")]
        public ActionResult<List<FileRegisterHowLogin>> GetLoginLogsByUser([FromQuery] string userName)
        {
            var logs = _bal.GetLoginLogsByUser(userName);
            return Ok(logs);
        }
    }
}
