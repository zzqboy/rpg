using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

using GameClient;

namespace Test
{
	class TestBuff
	{
		Buff test_buff = new Buff(5);

		public void test()
		{
			Console.WriteLine("ring buff test");
			while (true)
			{
				string opr = Console.ReadLine();
				run_opr(opr);
			}

		}

		public void write()
		{
			Console.WriteLine("����������");
			string input_str = Console.ReadLine();
			byte[] write_data = Encoding.UTF8.GetBytes(input_str);

			Console.WriteLine("���������ݣ� byte({0} --> {1})", input_str, BitConverter.ToString(write_data));
			this.test_buff.write(write_data, write_data.Length);
			this.debug();
		}

		public void read()
		{
			Console.WriteLine("�������ȡsize");
			int size = int.Parse(Console.ReadLine());
			byte[] read_data = new byte[size];
			this.test_buff.read(read_data, size);
			Console.WriteLine("��ȡ�� byte({0})", BitConverter.ToString(read_data));
			this.debug();
		}

		public void debug()
		{
			Console.WriteLine("�������ݣ� {0}", BitConverter.ToString(this.test_buff.GetBuff()));
			Console.WriteLine("��ָ�룺 {0} дָ�� : {1} ���ÿռ�: {2}", this.test_buff.GetReadPos(), this.test_buff.GetWritePos(), this.test_buff.GetEmptySize());
		}

		// �������к���
		public object run_opr(string method_name)
		{
			//Type[] ptype = new Type[param.Length];
			//for(int i=0;i<ptype.Length;i++)
			//	ptype[i] = param[i].GetType();
			
			Type p=this.GetType();
			MethodInfo m = p.GetMethod(method_name, new Type[]{});
			if(m != null)
				return m.Invoke(this, new object[]{});
			return null;
		}
	}
}