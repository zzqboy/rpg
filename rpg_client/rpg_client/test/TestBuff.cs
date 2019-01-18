using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Reflection;

namespace Test
{
	class TestBuff
	{
		Buff test_buff = new Buff(1024);
		Dictionary<string, Func<byte[]>> func_dict;


		public void test()
		{
			while(true)
			{
				string opr = Console.ReadLine();
				run_opr(opr);
			}

		}

		//public void run_opr(string fun)
		//{ 
		//	// 利用反射调用相应方法
		//	MethodInfo method = this.m_type.GetMethod(fun, new Type[] { typeof(byte[]) });
		//	object[] parameters = new object[] { };
		//	method.Invoke(this.instance, parameters);
		//}

		public void write()
		{
			Console.WriteLine("请输入");
			string input_str = Console.ReadLine();
			byte[] write_data = Encoding.UTF8.GetBytes(input_str);

			Console.WriteLine("二进制数据： byte({1} --> {2})", input_str, BitConverter.ToString(write_data));
			this.test_buff.write(write_data, write_data.Length);
			this.debug();
		}

		public void read()
		{
			Console.WriteLine("请输入");
			int size = int.Parse(Console.ReadLine());
			byte[] read_data = new byte[size];
			this.test_buff.read(read_data, size);
			Console.WriteLine("读取： byte({1})", BitConverter.ToString(read_data));
			this.debug();
		}

		public void debug()
		{
			Console.WriteLine("缓冲数据： {1}", BitConverter.ToString(this.test_buff.GetBuff()));
			Console.WriteLine("读指针： {1} 写指针 : {2} 有用空间: {3}", this.test_buff.GetReadPos(), this.test_buff.GetWritePos(), this.test_buff.GetEmptySize());
		}
	}
}