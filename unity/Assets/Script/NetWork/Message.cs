using System;
using System.Runtime.InteropServices;


namespace GameClient
{
	// 测试
	[StructLayout(LayoutKind.Sequential, Pack = 1)]
	public struct Ping
	{
		[MarshalAs(UnmanagedType.I4, SizeConst = 4)]
		public int id;

		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
		public char[] name;

		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
		public char[] password;
	}

	class Pack
	{
		public static byte[] StructToBytes(object obj)
		{
			int size = Marshal.SizeOf(obj);
			byte[] bytes = new byte[size];
			IntPtr structPtr = Marshal.AllocHGlobal(size);
			Marshal.StructureToPtr(obj, structPtr, false);
			Marshal.Copy(structPtr, bytes, 0, size);
			Marshal.FreeHGlobal(structPtr);

			return bytes;
		}
	}
}
