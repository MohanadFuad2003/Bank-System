using System;
using System.Collections.Generic;

namespace DataAcsessLayer
{
    namespace DataAcsessLayer.Models
    {
        public class User
        {
            public int UserID { get; set; }
            public string FirstName { get; set; }
            public string LastName { get; set; }
            public string Email { get; set; }
            public string Phone { get; set; }
            public string UserName { get; set; }
            public string Password { get; set; }
            public int Result { get; set; }  
        }
    }

}
