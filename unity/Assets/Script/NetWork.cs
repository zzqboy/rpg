using System.Net.Sockets;

public class NetWork{

	public Socket socket;
	public Buff read_buff;
	public Buff write_buff;


	void Instance()
	{
		this.socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
	}

	void Connect(string ip, int port)
	{
		this.socket.Connect(ip, port);
	}

	void Send(byte[] msg)
	{
		this.socket.Send(msg);
	}
}
