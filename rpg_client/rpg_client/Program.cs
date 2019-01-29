using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Test;

namespace rpg_client
{
	class Program
	{
		static void Main(string[] args)
		{
			TestSocket s = new TestSocket();
			s.test();
		}
	}
}
