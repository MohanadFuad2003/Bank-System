using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataAcsessLayer
{
    public class TransferLogRecord
   {
        public int TransferID { get; set; }
        public string TransferDateTime { get; set; }
        public string FromAccount { get; set; }
        public string ToAccount { get; set; }
        public decimal Amount { get; set; }
        public decimal FromAccountBalance { get; set; }
        public decimal ToAccountBalance { get; set; }
        public string DoneBy { get; set; }
    }
}
