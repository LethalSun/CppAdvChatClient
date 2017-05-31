#include "pch.h"
#include "LobbyObserver.h"

namespace MDNetwork
{
	LobbyObserver::LobbyObserver()
	{
	}

	LobbyObserver::~LobbyObserver()
	{
	}
	
	LOBBY_LIST_RES_Func LobbyObserver::GetLOBBY_LIST_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_LIST_RES( pPacket);
		};
	}
	
	LobbyPacketQue * LobbyObserver::GetLOBBY_LIST_RES_Que()
	{
		return &m_LobbyPacketQue;
	}

	LOBBY_ENTER_RES_Func LobbyObserver::GetLOBBY_ENTER_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_ENTER_RES(pPacket);
		};
	}

	LobbyEnterPacketQue * LobbyObserver::GetLOBBY_ENTER_RES_Que()
	{
		return &m_LobbyEnterPacketQue;
	}

	LOBBY_ENTER_USER_NTF_Func LobbyObserver::GetLOBBY_ENTER_USER_NTF_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_ENTER_USER_NTF(pPacket);
		};
	}

	LobbyNewUserInfoNtfQue * LobbyObserver::GetLOBBY_ENTER_USER_NTF_Que()
	{
		return &m_LobbyNewUserInfoNtfQue;
	}

	LOBBY_ENTER_ROOM_LIST_RES_Func LobbyObserver::GetLOBBY_ENTER_ROOM_LIST_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_ENTER_ROOM_LIST_RES(pPacket);
		};
	}

	PktLobbyRoomListResQue* LobbyObserver::GetPktLobbyRoomListResQue()
	{
		return &m_LobbyRoomListResQue;
	}

	LOBBY_ENTER_USER_LIST_RES_Func LobbyObserver::GetLOBBY_ENTER_USER_LIST_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_ENTER_USER_LIST_RES(pPacket);
		};
	}

	PktLobbyUserListResQue * LobbyObserver::GetPktLobbyUserListResQue()
	{
		return &m_LobbyUserListResQue;
	}

	LOBBY_LEAVE_RES_Func LobbyObserver::GetLOBBY_LEAVE_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_LEAVE_RES(pPacket);
		};
	}

	PktLobbyLeaveResQue * LobbyObserver::GetPktLobbyLeaveResQue()
	{
		return &m_LobbyLeaveResQue;
	}
	
	LOBBY_LEAVE_USER_NTF_Func LobbyObserver::GetLOBBY_LEAVE_USER_NTF_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_LEAVE_USER_NTF(pPacket);
		};
	}

	PktLobbyLeaveUserInfoNtfQue * LobbyObserver::GetPktLobbyLeaveUserInfoNtfQue()
	{
		return &m_LobbyLeaveUserInfoNtfQue;
	}

	LOBBY_CHAT_RES_Func LobbyObserver::GetLOBBY_CHAT_RES_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_CHAT_RES(pPacket);
		};
	}

	PktLobbyChatResQue * LobbyObserver::GetPktLobbyChatResQue()
	{
		return &m_LobbyChatResQue;
	}

	LOBBY_CHAT_NTF_Func LobbyObserver::GetLOBBY_CHAT_NTF_Func()
	{
		return [this](PacketBodyPtr pPacket)
		{
			NotifyLOBBY_CHAT_NTF(pPacket);
		};
	}

	PktLobbyChatNtfQue* LobbyObserver::GetPktLobbyChatNtfQue()
	{
		return &m_LobbyChatNtfQue;
	}

	void LobbyObserver::NotifyLOBBY_LIST_RES(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyListRes*)pPacket->PacketData;
		
		PktLobbyListRes pkt;
		
		pkt.LobbyCount = data->LobbyCount;
		pkt.ErrorCode = data->ErrorCode;
	
		for (int i = 0; i < pkt.LobbyCount; ++i)
		{
			pkt.LobbyList[i].LobbyId = data->LobbyList[i].LobbyId;
			
			pkt.LobbyList[i].LobbyUserCount = data->LobbyList[i].LobbyUserCount;
			
		}
		
		m_LobbyPacketQue.push(pkt);
		
	}

	void LobbyObserver::NotifyLOBBY_ENTER_RES(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyEnterRes*)pPacket->PacketData;

		PktLobbyEnterRes pkt;

		pkt.MaxRoomCount = data->MaxRoomCount;
		pkt.MaxUserCount = data->MaxUserCount;
		pkt.ErrorCode = data->ErrorCode;

		m_LobbyEnterPacketQue.push(pkt);
	}

	void LobbyObserver::NotifyLOBBY_ENTER_USER_NTF(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyNewUserInfoNtf*)pPacket->PacketData;

		PktLobbyNewUserInfoNtf pkt;
		
		memcpy(pkt.UserID, data->UserID,MAX_USER_ID_SIZE);
	
		m_LobbyNewUserInfoNtfQue.push(pkt);
	}

	void LobbyObserver::NotifyLOBBY_ENTER_ROOM_LIST_RES(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyRoomListRes*)pPacket->PacketData;

		PktLobbyRoomListRes pkt;

		pkt.Count = data->Count;
		pkt.IsEnd = data->IsEnd;
		pkt.ErrorCode = data->ErrorCode;

		for (int i = 0; i < 5; ++i)
		{
			pkt.RoomInfo[i].RoomIndex = data->RoomInfo[i].RoomIndex;
			pkt.RoomInfo[i].RoomUserCount = data->RoomInfo[i].RoomUserCount;
			memcpy(
				(char*)pkt.RoomInfo[i].RoomTitle,
				(char*)data->RoomInfo[i].RoomTitle,
				MAX_ROOM_TITLE_SIZE + 1);
		}

		m_LobbyRoomListResQue.push(pkt);
	}

	void LobbyObserver::NotifyLOBBY_ENTER_USER_LIST_RES(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyUserListRes*)pPacket->PacketData;

		PktLobbyUserListRes pkt;

		pkt.Count = data->Count;
		pkt.ErrorCode = data->ErrorCode;
		pkt.IsEnd = data->IsEnd;

		for (int i = 0; i < 20; ++i)
		{
			pkt.UserInfo[i].LobbyUserIndex = data->UserInfo[i].LobbyUserIndex;
			memcpy(
				(char*)pkt.UserInfo[i].UserID,
				(char*)data->UserInfo[i].UserID,
				MAX_USER_ID_SIZE + 1);
		}

		m_LobbyUserListResQue.push(pkt);
	}

	void LobbyObserver::NotifyLOBBY_LEAVE_RES(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyLeaveRes*)pPacket->PacketData;
		
		PktLobbyLeaveRes pkt;

		pkt.ErrorCode = data->ErrorCode;

		m_LobbyLeaveResQue.push(id);
	}

	void LobbyObserver::NotifyLOBBY_LEAVE_USER_NTF(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyLeaveUserInfoNtf*)pPacket->PacketData;

		PktLobbyLeaveUserInfoNtf pkt;

		memcpy(pkt.UserID, data->UserID, MAX_USER_ID_SIZE);

		m_LobbyLeaveUserInfoNtfQue.push(pkt);
	}

	void LobbyObserver::NotifyLOBBY_CHAT_RES(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyChatRes*)pPacket->PacketData;

		m_LobbyChatResQue.push(id);
	}

	void LobbyObserver::NotifyLOBBY_CHAT_NTF(PacketBodyPtr pPacket)
	{
		auto size = pPacket->PacketBodySize;
		auto id = pPacket->PacketId;
		auto data = (MDNetwork::PktLobbyChatNtf*)pPacket->PacketData;

		PktLobbyChatNtf pkt;
		memcpy(pkt.UserID, data->UserID, MAX_USER_ID_SIZE + 1);

		//char buffer[MAX_LOBBY_CHAT_MSG_SIZE + 1];
		//Util::UnicodeToAnsi(data->Msg, MAX_LOBBY_CHAT_MSG_SIZE + 1, buffer);
		//auto msg =  Util::CharToWstring(buffer);
		//memcpy(pkt.Msg, msg.c_str(), MAX_LOBBY_CHAT_MSG_SIZE + 1);
		
		wmemcpy(pkt.Msg, data->Msg, MAX_LOBBY_CHAT_MSG_SIZE + 1);
		m_LobbyChatNtfQue.push(pkt);
	}


}

