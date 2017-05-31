#pragma once

namespace MDNetwork
{
	using LOBBY_LIST_RES_Func = std::function<void(PacketBodyPtr)>;
	using LobbyPacketQue = concurrency::concurrent_queue<PktLobbyListRes>;

	using LOBBY_ENTER_RES_Func = std::function<void(PacketBodyPtr)>;
	using LobbyEnterPacketQue = concurrency::concurrent_queue<PktLobbyEnterRes>;

	using LOBBY_ENTER_USER_NTF_Func = std::function<void(PacketBodyPtr)>;
	using LobbyNewUserInfoNtfQue = concurrency::concurrent_queue<PktLobbyNewUserInfoNtf>;

	using LOBBY_ENTER_ROOM_LIST_RES_Func = std::function<void(PacketBodyPtr)>;
	using PktLobbyRoomListResQue = concurrency::concurrent_queue<PktLobbyRoomListRes>;

	using LOBBY_ENTER_USER_LIST_RES_Func = std::function<void(PacketBodyPtr)>;
	using PktLobbyUserListResQue = concurrency::concurrent_queue<PktLobbyUserListRes>;

	using LOBBY_LEAVE_RES_Func = std::function<void(PacketBodyPtr)>;
	using PktLobbyLeaveResQue = concurrency::concurrent_queue<short>;

	using LOBBY_LEAVE_USER_NTF_Func = std::function<void(PacketBodyPtr)>;
	using PktLobbyLeaveUserInfoNtfQue = concurrency::concurrent_queue<PktLobbyLeaveUserInfoNtf>;

	using LOBBY_CHAT_RES_Func = std::function<void(PacketBodyPtr)>;
	using PktLobbyChatResQue = concurrency::concurrent_queue<short>;

	using LOBBY_CHAT_NTF_Func = std::function<void(PacketBodyPtr)>;
	using PktLobbyChatNtfQue = concurrency::concurrent_queue<PktLobbyChatNtf>;

	class LobbyObserver
	{
	public:
		LobbyObserver();
		~LobbyObserver();

		//로비 리스트 요청
		LOBBY_LIST_RES_Func GetLOBBY_LIST_RES_Func();

		LobbyPacketQue* GetLOBBY_LIST_RES_Que();

		//로비 입장 요청
		LOBBY_ENTER_RES_Func GetLOBBY_ENTER_RES_Func();

		LobbyEnterPacketQue* GetLOBBY_ENTER_RES_Que();

		//로비에 새로운 유저 입장
		LOBBY_ENTER_USER_NTF_Func GetLOBBY_ENTER_USER_NTF_Func();

		LobbyNewUserInfoNtfQue* GetLOBBY_ENTER_USER_NTF_Que();

		//로비 방 목록
		LOBBY_ENTER_ROOM_LIST_RES_Func GetLOBBY_ENTER_ROOM_LIST_RES_Func();

		PktLobbyRoomListResQue* GetPktLobbyRoomListResQue();

		//로비 유저 목록
		LOBBY_ENTER_USER_LIST_RES_Func GetLOBBY_ENTER_USER_LIST_RES_Func();

		PktLobbyUserListResQue* GetPktLobbyUserListResQue();

		//로비 나가기
		LOBBY_LEAVE_RES_Func GetLOBBY_LEAVE_RES_Func();

		PktLobbyLeaveResQue* GetPktLobbyLeaveResQue();

		//로비에서 유저 나감
		LOBBY_LEAVE_USER_NTF_Func GetLOBBY_LEAVE_USER_NTF_Func();

		PktLobbyLeaveUserInfoNtfQue* GetPktLobbyLeaveUserInfoNtfQue();

		//로비 채팅
		LOBBY_CHAT_RES_Func GetLOBBY_CHAT_RES_Func();
		PktLobbyChatResQue* GetPktLobbyChatResQue();

		LOBBY_CHAT_NTF_Func GetLOBBY_CHAT_NTF_Func();
		PktLobbyChatNtfQue* GetPktLobbyChatNtfQue();

	private:
		//로비 리스트 요청
		void NotifyLOBBY_LIST_RES(PacketBodyPtr pPacket);

		LobbyPacketQue m_LobbyPacketQue;

		//로비 입장 요청
		void NotifyLOBBY_ENTER_RES(PacketBodyPtr pPacket);

		LobbyEnterPacketQue m_LobbyEnterPacketQue;

		//로비에 새로운 유저 입장
		void NotifyLOBBY_ENTER_USER_NTF(PacketBodyPtr pPacket);

		LobbyNewUserInfoNtfQue m_LobbyNewUserInfoNtfQue;

		//로비 방 목록
		void NotifyLOBBY_ENTER_ROOM_LIST_RES(PacketBodyPtr pPacket);

		PktLobbyRoomListResQue m_LobbyRoomListResQue;

		//로비 유저 목록
		void NotifyLOBBY_ENTER_USER_LIST_RES(PacketBodyPtr pPacket);

		PktLobbyUserListResQue m_LobbyUserListResQue;

		//로비 나가기
		void NotifyLOBBY_LEAVE_RES(PacketBodyPtr pPacket);

		PktLobbyLeaveResQue m_LobbyLeaveResQue;

		//로비에서 유저 나감
		void NotifyLOBBY_LEAVE_USER_NTF(PacketBodyPtr pPacket);

		PktLobbyLeaveUserInfoNtfQue m_LobbyLeaveUserInfoNtfQue;

		//로비 채팅
		void NotifyLOBBY_CHAT_RES(PacketBodyPtr pPacket);

		PktLobbyChatResQue m_LobbyChatResQue;

		void NotifyLOBBY_CHAT_NTF(PacketBodyPtr pPacket);

		PktLobbyChatNtfQue m_LobbyChatNtfQue;
	};
}
