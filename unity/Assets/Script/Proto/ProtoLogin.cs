using System;
using System.Runtime.InteropServices;

namespace GameClient
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
	struct ProtoLogin
	{
        [MarshalAs(UnmanagedType.I4, SizeConst = 4)]
        public int id;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string name;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string password;
	};
}
