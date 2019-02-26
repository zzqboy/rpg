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
			p.id = 1;
			p.name = "hello".PadRight(20, '\0').ToCharArray();
			p.password = "hello".PadRight(20, '\0').ToCharArray();
			byte[] data = Pack.StructToBytes(p);
			byte[] head = BitConverter.GetBytes(data.Length);

			Console.WriteLine("二进制数据： byte({0})", BitConverter.ToString(data));
			s.SyncSend(head);
			s.SyncSend(data);

			int size = int.Parse(Console.ReadLine());
		}
	}
}
