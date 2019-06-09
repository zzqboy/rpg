using System;
using System.Runtime.InteropServices;


namespace GameClient
{
	// 测试
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
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
		public static byte[] PackMsg(object obj)
		{
            // 内容
			int size = Marshal.SizeOf(obj);
			byte[] bytes = new byte[size];
			IntPtr structPtr = Marshal.AllocHGlobal(size);
			Marshal.StructureToPtr(obj, structPtr, false);
			Marshal.Copy(structPtr, bytes, 0, size);
			Marshal.FreeHGlobal(structPtr);

            // 长度
            byte[] head = BitConverter.GetBytes(size);

            byte[] msg = new byte[head.Length + bytes.Length];
            head.CopyTo(msg, 0);
            bytes.CopyTo(msg, head.Length);
            return msg;
		}
	}
}
