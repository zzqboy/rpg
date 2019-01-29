using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GameClient;

namespace Test
{
	class TestSocket
	{
		public void test()
		{
			ClientSocket s = new ClientSocket();
			s.Connect();

			Ping p = new Ping();
			p.id = 0;
			p.name = "hello".PadRight(20, '\0').ToCharArray();
			byte[] data = Pack.StructToBytes(p);
			byte[] head = BitConverter.GetBytes(data.Length);

			s.SyncSend(head);
			//s.SyncSend(data);
		}
	}
}
