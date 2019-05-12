using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

using GameClient;

/*
 * 连接socket
 */
namespace GameClient
{
	public class ClientSocket
	{
		private IPAddress connect_ip; // 服务器ip
		private Socket socket = new System.Net.Sockets.Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
		private Buff recv_buff;

		public ClientSocket(string connect_ip = "127.0.0.1")
		{ 
			this.connect_ip = IPAddress.Parse(connect_ip);
		}

		public void Connect()
		{
			this.socket.Connect(new IPEndPoint(connect_ip, 9000));
		}

		public void AsynSend(byte[] data, int size)
		{
			this.socket.BeginSend(data, 0, data.Length, SocketFlags.None, new AsyncCallback(SendCallback), this.socket);
		}

		public void SyncSend(byte[] data)
		{
			this.socket.Send(data);
		}

		public static void SendCallback(IAsyncResult result)
		{
			try
			{
				// Retrieve the socket from the state object.     
				Socket handler = (Socket)result.AsyncState;
				// Complete sending the data to the remote device.     
				int bytesSent = handler.EndSend(result);
				Console.WriteLine("Sent {0} bytes to client.", bytesSent);
			}
			catch (Exception e)
			{
				Console.WriteLine(e.ToString());
			}
		}

		public void close()
		{
			this.socket.Shutdown(SocketShutdown.Both);
			this.socket.Close();
		}
	}
}
