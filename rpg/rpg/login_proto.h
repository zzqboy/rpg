/*!
 * \file login_proto.h
 *
 * \author ziquan
 * \date ���� 2019
 *
 * \brief ��¼�ṹ��
 */
#pragma pack(1)

namespace Proto
{
	struct Login
	{
		char name[20];
		char password[20];
	};
}

#pragma pack()