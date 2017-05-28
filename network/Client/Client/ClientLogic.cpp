#include "pch.h"
#include "ClientLogic.h"


namespace MDNetwork
{
	//�α���
	ClientLogic::ClientLogic()
	{
		//TODO:���� �Լ��� �޾ƿ´�.
	}


	ClientLogic::~ClientLogic()
	{
	}

	int ClientLogic::SendPktLogInReq(char * pID, char * pPW)
	{
		auto returnVal = 0;

		if (m_LoginState == false)
		{


			MDNetwork::PktLogInReq loginPacket{ 0, };
			strncpy_s(loginPacket.szID, MDNetwork::MAX_USER_ID_SIZE + 1, pID, MDNetwork::MAX_USER_ID_SIZE);
			strncpy_s(loginPacket.szPW, MDNetwork::MAX_USER_PASSWORD_SIZE + 1, pPW, MDNetwork::MAX_USER_PASSWORD_SIZE);

			//TODO:��Ʈ��ũ�� ���� �Լ��� �޾ƿͼ� ��Ŷ�� ������.
			returnVal = m_data->m_Network->Send((short)MDNetwork::PACKET_ID::LOGIN_IN_REQ, sizeof(loginPacket), (char*)&loginPacket);
		}

		return returnVal;
	}

	void ClientLogic::OnLOGIN_IN_RES()
	{
		m_LoginState = true;
	}

	bool ClientLogic::IsLogin()
	{
		return m_LoginState;
	}

}