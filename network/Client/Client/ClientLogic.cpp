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

	void ClientLogic::GetNetworkSendFunc(SendFunc pSendfunc)
	{
		m_SendFunc = pSendfunc;
	}

	int ClientLogic::SendPktLogInReq(char * pID, char * pPW)
	{
		auto returnVal = 0;

		if (m_LoginState == false)
		{


			MDNetwork::PktLogInReq loginPacket{ 0, };
			strncpy_s(loginPacket.szID, MDNetwork::MAX_USER_ID_SIZE + 1, pID, MDNetwork::MAX_USER_ID_SIZE);
			strncpy_s(loginPacket.szPW, MDNetwork::MAX_USER_PASSWORD_SIZE + 1, pPW, MDNetwork::MAX_USER_PASSWORD_SIZE);

			returnVal = m_SendFunc((short)MDNetwork::PACKET_ID::LOGIN_IN_REQ, sizeof(loginPacket), (char*)&loginPacket);
		}

		return returnVal;
	}

	int ClientLogic::SetLOGIN_IN_RES_Que(LoginPacketQue * pQue)
	{
		m_LoginQue = pQue;

		return 0;
	}

	void ClientLogic::OnLOGIN_IN_RES()
	{
		short pId{ 0 };

		if (m_LoginQue->try_pop(pId))
		{
			m_LoginState = pId;
		}
	}

	bool ClientLogic::IsLogin()
	{
		OnLOGIN_IN_RES();

		if (m_LoginState == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

}