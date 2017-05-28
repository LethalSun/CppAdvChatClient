#include "pch.h"
#include "ClientLogic.h"


namespace MDNetwork
{
	//로그인
	ClientLogic::ClientLogic()
	{
		//TODO:샌드 함수를 받아온다.
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

			//TODO:네트워크의 센드 함수를 받아와서 패킷을 보낸다.
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