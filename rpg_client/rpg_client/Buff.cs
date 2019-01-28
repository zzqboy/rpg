using System;

/*	
 * ���λ���
 */
public class Buff
{


	private byte[] m_data; // ����������
	private int read_pos;
	private int write_pos;
	private int tol_size;

	// ��ʼ��һ��buff���Ⱥ�ָ��
	public Buff(int size)
	{
		this.m_data = new byte[size];
		this.read_pos = 0;
		this.write_pos = 0;
		this.tol_size = size;
	}

	/************************************************************************/
	// ��д����                          
	/************************************************************************/
	public void write(byte[] send_data, int size)
	{
		// �������� ��Ҫ����
		if (this.GetEmptySize() < size)
		{
			int re_size = this.tol_size * 2;
			this.resize(re_size);
			this.write(send_data, size);
			return;
		}
		if((this.tol_size - this.write_pos) >= size)
		{
			Array.Copy(send_data, 0, this.m_data, this.write_pos, size);
			this.write_pos += size;
		}
		else
		{
			Array.Copy(send_data, 0, this.m_data, this.write_pos, this.tol_size - this.write_pos);
			Array.Copy(send_data, this.tol_size - this.write_pos, this.m_data, 0, size - (this.tol_size - this.write_pos));
			// ���ʱ��дָ���Ƶ���ָ��ǰ��
			this.write_pos = size - (this.tol_size - this.write_pos);
			if (this.write_pos == this.read_pos)
			{ 

			}
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
		// ��ָ����дָ��ǰ��
		if (this.write_pos > this.read_pos)
		{
			Array.Copy(this.m_data, this.read_pos, read_data, 0, size);
			this.read_pos += size;
			if (this.read_pos == this.write_pos) { this.reset(); }
		}
		// ��ָ����дָ�����
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
				Array.Copy(this.m_data, 0, read_data, this.tol_size - this.read_pos, size - (this.tol_size - this.read_pos));
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
		int write_size = this.GetReadableSize();
		if(this.read(new_data, this.GetReadableSize()))
		{
			this.m_data = new_data;
		}
		this.read_pos = 0;
		this.write_pos = write_size;
		this.tol_size = size;
	}
	/************************************************************************/
	// �ж����                          
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
		if (this.write_pos > this.read_pos)
		{
			return this.read_pos + this.tol_size - this.write_pos;
		}
		if(this.read_pos > this.write_pos)
		{
			return this.read_pos - this.write_pos;
		}
		// ����������ָ�붼��һ����λ��
		if (read_pos == 0)
		{
			// λ������ͷ��û���ù�
			return this.tol_size;
		}
		else
		{
			// �Ѿ�д�� ���Ҷ�д���м��ĳһλ��
			return 0;
		}
	}


	public int GetReadableSize()
	{
		return this.tol_size - this.GetEmptySize();
	}

	public byte[] GetBuff()
	{
		return this.m_data;
	}

	public int GetReadPos()
	{
		return this.read_pos;
	}

	public int GetWritePos()
	{
		return this.write_pos;
	}
}
