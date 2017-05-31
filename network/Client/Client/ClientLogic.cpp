#include "pch.h"
#include "ClientLogic.h"


namespace MDNetwork
{
	//·Î±×ÀÎ
	ClientLogic::ClientLogic()
	{

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

		if (m_LoginState == 0)
		{

			MDNetwork::PktLogInReq loginPacket{ 0, };
			strncpy_s(loginPacket.szID, MDNetwork::MAX_USER_ID_SIZE + 1, pID, MDNetwork::MAX_USER_ID_SIZE);
			strncpy_s(loginPacket.szPW, MDNetwork::MAX_USER_PASSWORD_SIZE + 1, pPW, MDNetwork::MAX_USER_PASSWORD_SIZE);



			m_ID = Util::CharToWstring(pID);
			m_Pw = Util::CharToWstring(pPW);
			
			returnVal = m_SendFunc(
				(short)MDNetwork::PACKET_ID::LOGIN_IN_REQ, 
				sizeof(loginPacket), 
				(char*)&loginPacket);
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

	void ClientLogic::OnLOBBY_LIST_RES()
	{
		PktLobbyListRes buffer;
		while (m_LobbyListQue->try_pop(buffer))
		{
			if (buffer.ErrorCode == 0)
			{
				m_lobbyCount = buffer.LobbyCount;
				auto lobbyList = buffer.LobbyList;
				for (int i = 0; i < m_lobbyCount; ++i)
				{
					auto lobbyId = lobbyList[i].LobbyId;
					auto lobbyUserCount = lobbyList[i].LobbyUserCount;
					auto lobbyTuple = std::make_tuple(lobbyId, lobbyUserCount);

					m_ChennelListArr[i] = lobbyTuple;
				}
			}
		}
	}

	void ClientLogic::OnLOBBY_ENTER_RES()
	{
		PktLobbyEnterRes buffer;
		while (m_LobbyEnterQue->try_pop(buffer))
		{
			if (buffer.ErrorCode == 0)
			{
				m_MaxRoomCount = buffer.MaxRoomCount;
				m_MaxUserCount = buffer.MaxUserCount;

				m_IsLobby = true;
			}
		}
	}

	bool ClientLogic::OnLOBBY_ENTER_USER_NTF()
	{
		PktLobbyNewUserInfoNtf buffer;
		if (m_LobbyNewUserQue->try_pop(buffer))
		{
			auto data = buffer.UserID;

			memcpy(m_NewUser, data, MAX_USER_ID_SIZE + 1);

			return true;
		}
		else
		{
			return false;
		}
	}

	

	void ClientLogic::OnLOBBY_LEAVE_RES()
	{
		if (IsLeaveLobbyAllowed == false)
		{
			short pkt;
			if (m_LobbyLeaveQue->try_pop(pkt))
			{
				IsLeaveLobbyAllowed = true;

				return;
			}
		
			return;
		}

		return;
	}

	bool ClientLogic::OnLOBBY_LEAVE_USER_NTF()
	{
		PktLobbyLeaveUserInfoNtf buffer;
		if (m_LobbyLeaveNtfQue->try_pop(buffer))
		{
			auto data = buffer.UserID;

			memcpy(m_LeavedUser, data, MAX_USER_ID_SIZE + 1);

			return true;
		}
		else
		{
			return false;
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

	int ClientLogic::SendPktLobbyListInfo()
	{
		m_SendFunc(
			static_cast<short>(MDNetwork::PACKET_ID::LOBBY_LIST_REQ),
			0, 
			nullptr);

		return 0;
	}

	int ClientLogic::SetLOBBY_LIST_RES_Que(LobbyListInfoQue * pQue)
	{
		m_LobbyListQue = pQue;

		return 0;
	}

	ChennelInfo ClientLogic::GetLobbyList(int& pIndexCount)
	{
		OnLOBBY_LIST_RES();
		if (pIndexCount == -1)
		{
			pIndexCount = m_lobbyCount;
			return ChennelInfo();
		}
		else
		{
			return m_ChennelListArr[pIndexCount];
		}
	}

	int ClientLogic::SendPktLobbyEnter(short pLobbyId)
	{
		auto returnVal = -1;

		if (m_IsLobby == false)
		{
			MDNetwork::PktLobbyEnterReq lobEnterPacket{ 0, };
			
			lobEnterPacket.LobbyId = pLobbyId;

			returnVal = m_SendFunc(
				(short)MDNetwork::PACKET_ID::LOBBY_ENTER_REQ, 
				sizeof(lobEnterPacket), 
				(char*)&lobEnterPacket);
		}

		return returnVal;
	}

	int ClientLogic::SetLOBBY_ENTER_RES_Que(LobbyEnterPacketQue * pQue)
	{
		m_LobbyEnterQue = pQue;
		return 0;
	}

	bool ClientLogic::IsLobbyEnterAllowed()
	{
		OnLOBBY_ENTER_RES();

		return m_IsLobby;
	}

	MaxUserAndRoom ClientLogic::GetUserAndRoomCount()
	{
		auto userAndRoom = std::make_tuple(
			m_MaxUserCount, m_MaxRoomCount);
		return userAndRoom;
	}

	int ClientLogic::SetLOBBY_ENTER_USER_NTF_Que(LobbyNewUserInfoNtfQue * pQue)
	{
		m_LobbyNewUserQue = pQue;
		return 0;
	}

	bool ClientLogic::IsThereNewUser()
	{
		if (OnLOBBY_ENTER_USER_NTF())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ClientLogic::GetNewUser(char * pNewUserId)
	{
		if (m_NewUser[0] == '\0')
		{
			pNewUserId[0] = '\0';
			return;
		}
		else
		{
			memcpy(pNewUserId, m_NewUser, MAX_USER_ID_SIZE + 1);
			m_NewUser[0] = '\0';
			return;
		}
	}

	int ClientLogic::SendPktRoomList(short pStartIndex)
	{
		auto returnVal = -1;
		if (pStartIndex == 0)
		{
			MDNetwork::PktLobbyRoomListReq pkt;

			pkt.StartRoomIndex = pStartIndex;

			returnVal = m_SendFunc(
				static_cast<short>(PACKET_ID::LOBBY_ENTER_ROOM_LIST_REQ),
				sizeof(pkt),
				(char*)&pkt
			);
		}
		else if(pStartIndex>0)
		{
			auto index = pStartIndex + 1;
			MDNetwork::PktLobbyRoomListReq pkt;

			pkt.StartRoomIndex = index;

			returnVal = m_SendFunc(
				static_cast<short>(PACKET_ID::LOBBY_ENTER_ROOM_LIST_REQ),
				sizeof(pkt),
				(char*)&pkt
			);
		}
		else
		{

		}

		return returnVal;
	}

	int ClientLogic::SetLOBBY_ENTER_ROOM_LIST_RES_Que(PktLobbyRoomListResQue * pQue)
	{
		m_LobbyRoomListQue = pQue;
		return 0;
	}

	int ClientLogic::TryGetRoomList()
	{
		while (true)
		{
			if (LastRoomIndex != LastRoomIndexMemory)
			{
				LastRoomIndexMemory = LastRoomIndex;
				SendPktRoomList(LastRoomIndex);
			}

			if (!OnLOBBY_ENTER_ROOM_LIST_RES())
			{
				break;
			}

		}

		return LastRoomIndex;
	}

	RoomRetInfo ClientLogic::CopyRoomList(std::wstring &pBuffer)
	{

		if (RoomList.empty())
		{
			return RoomRetInfo();
		}
		auto room = RoomList.front();
		RoomList.pop_front();

		auto ret = std::make_tuple(room.RoomIndex, room.RoomUserCount);

		char buffer[MAX_ROOM_TITLE_SIZE + 1];

		
		

		pBuffer = room.RoomTitle;

		return ret;

	}

	int ClientLogic::SendPktLobbyUserList(short pStartIndex)
	{
		auto returnVal = -1;
		if (pStartIndex == 0)
		{
			MDNetwork::PktLobbyUserListReq pkt;

			pkt.StartUserIndex = pStartIndex;

			returnVal = m_SendFunc(
				static_cast<short>(PACKET_ID::LOBBY_ENTER_USER_LIST_REQ),
				sizeof(pkt),
				(char*)&pkt
			);
		}
		else if (pStartIndex>0)
		{
			auto index = pStartIndex + 1;
			MDNetwork::PktLobbyUserListReq pkt;

			pkt.StartUserIndex = index;

			returnVal = m_SendFunc(
				static_cast<short>(PACKET_ID::LOBBY_ENTER_USER_LIST_REQ),
				sizeof(pkt),
				(char*)&pkt
			);
		}
		else
		{

		}

		return returnVal;
	}

	int ClientLogic::SetLOBBY_ENTER_USER_LIST_RES_Que(PktLobbyUserListResQue * pQue)
	{
		m_LobbyUserListQue = pQue;
		return 0;
	}

	int ClientLogic::TryGetUserList()
	{
		while (true)
		{
			if (LastUserIndex != LastUserListMemory)
			{
				LastUserListMemory = LastUserIndex;
				SendPktLobbyUserList(LastUserIndex);
			}

			if (!OnLOBBY_ENTER_USER_LIST_RES())
			{
				break;
			}

		}

		return LastRoomIndex;
	}

	short ClientLogic::CopyUserList(std::wstring &pBuffer)
	{
		if (UserList.empty())
		{
			return -1;
		}
		auto user = UserList.front();
		UserList.pop_front();

		pBuffer = user.UserID;

		return user.LobbyUserIndex;
	}

	int ClientLogic::SendPktLobbyLeave()
	{
		auto returnVal = -1;

		if (m_IsLobby == true)
		{
			returnVal = m_SendFunc(
				(short)MDNetwork::PACKET_ID::LOBBY_LEAVE_REQ,
				0,
				nullptr);
		}

		return returnVal;
	}

	int ClientLogic::SetLOBBY_LEAVE_RES_Que(PktLobbyLeaveResQue * pQue)
	{
		m_LobbyLeaveQue = pQue;
		return 0;
	}

	bool ClientLogic::CanILeave()
	{
		OnLOBBY_LEAVE_RES();
		
		return IsLeaveLobbyAllowed;
	}

	bool ClientLogic::OnLOBBY_ENTER_USER_LIST_RES()
	{
		PktLobbyUserListRes pkt;
		if (m_LobbyUserListQue->try_pop(pkt))
		{
			auto error = pkt.ErrorCode;

			if (error != 0)
			{
				return true;
			}

			LastUserIndex = pkt.Count;

			

			for (int i = 0; i < 32; ++i)
			{
				userSmallInfo userInfo;

				userInfo.LobbyUserIndex = pkt.UserInfo[i].LobbyUserIndex;
				userInfo.UserID = Util::CharToWstring(pkt.UserInfo[i].UserID);

				UserList.push_back(userInfo);
			}

		}
		return pkt.IsEnd;
	}

	bool ClientLogic::OnLOBBY_ENTER_ROOM_LIST_RES()
	{
		PktLobbyRoomListRes pkt;
		pkt.IsEnd = false;

		if (m_LobbyRoomListQue->try_pop(pkt))
		{
			auto error = pkt.ErrorCode;
			if (error != 0)
			{
				return true;
			}
			LastRoomIndex = pkt.Count;

			for (int i = 0; i < 12; ++i)
			{
				roomSmallInfo roomInfo;
			
				roomInfo.RoomIndex = pkt.RoomInfo[i].RoomIndex;
				
				roomInfo.RoomUserCount = pkt.RoomInfo[i].RoomUserCount;
			
				roomInfo.RoomTitle = pkt.RoomInfo[i].RoomTitle;

				RoomList.push_back(roomInfo);
			}

		}
		return pkt.IsEnd;
	}



	int ClientLogic::SetLOBBY_LEAVE_USER_NTF(PktLobbyLeaveUserInfoNtfQue* pQue)
	{
		m_LobbyLeaveNtfQue = pQue;
		return 0;
	}

	bool ClientLogic::IsThereLevedUser()
	{
		return false;
	}

	void ClientLogic::GetLevedUser(char * pNewUserId)
	{
		if (m_LeavedUser[0] == '\0')
		{
			pNewUserId[0] = '\0';
			return;
		}
		else
		{
			memcpy(pNewUserId, m_LeavedUser, MAX_USER_ID_SIZE + 1);
			m_LeavedUser[0] = '\0';
			return;
		}
	}

	int ClientLogic::SendPktLobbyChatReq(std::wstring  pMsg)
	{
		int retValue;
		PktLobbyChatReq pkt;

		memcpy(pkt.Msg, pMsg.c_str(), MAX_LOBBY_CHAT_MSG_SIZE);
		
		m_MyMsgQue.push_back(pMsg);

		retValue = m_SendFunc(static_cast<short>(MDNetwork::PACKET_ID::LOBBY_CHAT_REQ),
			sizeof(pkt),
			(char*)&pkt);

		return retValue;
	}

	int ClientLogic::SetLOBBY_CHAT_RES(PktLobbyChatResQue * pQue)
	{
		m_LobbyChatResQue = pQue;

		return 0;
	}

	int ClientLogic::SetLOBBY_CHAT_NTF(PktLobbyChatNtfQue * pQue)
	{
		m_LobbyChatNtfQue = pQue;
		return 0;
	}

	int ClientLogic::GetMsg(std::wstring &pMgs)
	{
		int retValue = 0;

		if (m_MsgQue.empty())
		{
			pMgs[0] = '\0';
			return retValue;
		}

		auto msg = m_MsgQue.front();
		
		m_MsgQue.pop_front();
		
		pMgs = msg;

		retValue = m_MsgQue.size();

		return retValue;
	}

	int ClientLogic::CollectMsg()
	{
		short pktId;
		while (m_LobbyChatResQue->try_pop(pktId))
		{
			if (!m_MyMsgQue.empty())
			{
				auto myMsg = m_MyMsgQue.front();

				std::wstring id = m_ID;
				std::wstring msg = myMsg;
				std::wstring col = L":\n";

				msg = id + col + msg;

				m_MsgQue.push_back(msg);
				m_MyMsgQue.pop_front();
			}	
		}

		PktLobbyChatNtf pkt;

		while (m_LobbyChatNtfQue->try_pop(pkt))
		{

			std::wstring id = Util::CharToWstring(pkt.UserID);;
			std::wstring msg = pkt.Msg;
			std::wstring col = L":\n";
			msg = id + col +msg;

			m_MsgQue.push_back(msg);
		}

		return 0;
	}

}