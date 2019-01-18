using System;

/*	
 * 环形缓冲
 */
public class Buff
{


	private byte[] m_data; // 二进制数据
	private int read_pos;
	private int write_pos;
	private int tol_size;

	// 初始化一个buff长度和指针
	public Buff(int size)
	{
		this.m_data = new byte[size];
		this.read_pos = 0;
		this.write_pos = 0;
		this.tol_size = size;
	}

	/************************************************************************/
	// 读写操作                          
	/************************************************************************/
	public void write(byte[] send_data, int size)
	{
		// 容量不足 需要扩容
		if (this.GetEmptySize() < size)
		{
			this.resize(size);
			this.write(send_data, size);
		}
		else
		{
			Array.Copy(send_data, 0, this.m_data, this.write_pos, size);
			this.write_pos += size;
		}
	}

	public bool read(byte[] read_data, int size)
	{
		int can_read_size = this.GetReadableSize();
		if (can_read_size < size)
		{
			read_data = null;
			return false;
		}
		// 读指针在写指针前面
		if (this.write_pos > this.read_pos)
		{
			Array.Copy(this.m_data, this.read_pos, read_data, 0, size);
			this.read_pos += size;
			if (this.read_pos == this.write_pos) { this.reset(); }
		}
		// 读指针在写指针后面
		else
		{
			if ((this.tol_size - this.read_pos) >= size)
			{
				Array.Copy(this.m_data, this.read_pos, read_data, 0, size);
				this.read_pos += size;
				if (this.read_pos == this.tol_size){this.read_pos = 0;}
			}
			else
			{
				Array.Copy(this.m_data, this.read_pos, read_data, 0, this.tol_size - this.read_pos);
				Array.Copy(this.m_data, 0, read_data, this.tol_size - this.read_pos + 1, size - (this.tol_size - this.read_pos));
				this.read_pos = size - (this.tol_size - this.read_pos);
				if (this.read_pos == this.write_pos) { this.reset(); }
			}
		}
		return true;
	}

	public void reset()
	{
		this.read_pos = 0;
		this.write_pos = 0;
	}

	public void clear()
	{
		this.m_data = new byte[this.tol_size];
		this.read_pos = 0;
		this.write_pos = 0;
	}

	public void resize(int size)
	{
		if (size <= this.tol_size) { return; }

		byte[] new_data = new byte[size];
		if(this.read(new_data, this.GetReadableSize()))
		{
			this.m_data = new_data;
		}
		this.read_pos = 0;
		this.write_pos = this.GetReadableSize();
		this.tol_size = size;
	}
	/************************************************************************/
	// 判断相关                          
	/************************************************************************/
	public bool CanWriteSize(int size)
	{
		if (this.GetEmptySize() >= size)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	public int GetEmptySize()
	{
		if (this.write_pos >= this.read_pos)
		{
			return this.read_pos + this.tol_size - this.write_pos;
		}
		else
		{
			return this.read_pos - this.write_pos;
		}
	}


	public int GetReadableSize()
	{
		return this.tol_size - this.GetEmptySize();
	}
}
