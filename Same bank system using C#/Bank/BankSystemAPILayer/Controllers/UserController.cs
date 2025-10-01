using BusinessAccsesLayer;
using DataAcsessLayer.DataAcsessLayer.Models;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;

namespace BankSystemAPI.Controllers
{
    [ApiController]
    [Route("api/users")]
    public class UsersController : ControllerBase
    {
        private readonly UserBAL _bal = new UserBAL();

        [HttpGet]
        public ActionResult<List<User>> GetAllUsers()
        {
            var users = _bal.GetAllUsers();
            return Ok(users);
        }

        [HttpGet("GetUser/{userName}")]
        public ActionResult<User> GetUser(string userName)
        {
            var user = _bal.FindByUserName(userName);
            if (user == null) return NotFound();
            return Ok(user);
        }

        [HttpGet("GetUserByUserNameAndPassword")]
        public ActionResult<User> GetUserByUserNameAndPassword([FromQuery] string userName, [FromQuery] string password)
        {
            var user = _bal.FindByUserNameAndPassword(userName, password);
            if (user == null) return NotFound();
            return Ok(user);
        }

        [HttpPost("AddUser")]
        public ActionResult AddUser([FromBody] User user)
        {
            if (_bal.IsUserExist(user.UserName))
                return BadRequest("UserName already exists.");

            var result = _bal.AddUser(user);
            if (!result) return BadRequest("Failed to add user.");
            return Ok("User added successfully.");
        }

        [HttpPut("UpdateUser")]
        public ActionResult UpdateUser([FromBody] User user)
        {
            if (!_bal.IsUserExist(user.UserName))
                return NotFound("User not found.");

            var result = _bal.UpdateUser(user);
            if (!result) return BadRequest("Failed to update user.");
            return Ok("User updated successfully.");
        }

        [HttpDelete("DeleteUser/{userName}")]
        public ActionResult DeleteUser(string userName)
        {
            if (!_bal.IsUserExist(userName))
                return NotFound("User not found.");

            var result = _bal.DeleteUser(userName);
            if (!result) return BadRequest("Failed to delete user.");
            return Ok("User deleted successfully.");
        }

        [HttpGet("GetUserPermissions/{userName}")]
        public ActionResult<object> GetUserPermissions(string userName)
        {
            var user = _bal.FindByUserName(userName);
            if (user == null) return NotFound();

            var permissions = UserBAL.GetUserPermissions(user);
            return Ok(new { permissions = permissions.ToString(), permissionsValue = (int)permissions });
        }

        [HttpGet("has-permission/{userName}")]
        public ActionResult<object> HasUserPermission(string userName, [FromQuery] UserPermissions permission)
        {
            var user = _bal.FindByUserName(userName);
            if (user == null) return NotFound();

            bool hasPerm = UserBAL.HasPermission(user, permission);
            return Ok(new { hasPermission = hasPerm });
        }
    }
}
