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

		//�κ� ����Ʈ ��û
		LOBBY_LIST_RES_Func GetLOBBY_LIST_RES_Func();

		LobbyPacketQue* GetLOBBY_LIST_RES_Que();

		//�κ� ���� ��û
		LOBBY_ENTER_RES_Func GetLOBBY_ENTER_RES_Func();

		LobbyEnterPacketQue* GetLOBBY_ENTER_RES_Que();

		//�κ� ���ο� ���� ����
		LOBBY_ENTER_USER_NTF_Func GetLOBBY_ENTER_USER_NTF_Func();

		LobbyNewUserInfoNtfQue* GetLOBBY_ENTER_USER_NTF_Que();

		//�κ� �� ���
		LOBBY_ENTER_ROOM_LIST_RES_Func GetLOBBY_ENTER_ROOM_LIST_RES_Func();

		PktLobbyRoomListResQue* GetPktLobbyRoomListResQue();

		//�κ� ���� ���
		LOBBY_ENTER_USER_LIST_RES_Func GetLOBBY_ENTER_USER_LIST_RES_Func();

		PktLobbyUserListResQue* GetPktLobbyUserListResQue();

		//�κ� ������
		LOBBY_LEAVE_RES_Func GetLOBBY_LEAVE_RES_Func();

		PktLobbyLeaveResQue* GetPktLobbyLeaveResQue();

		//�κ񿡼� ���� ����
		LOBBY_LEAVE_USER_NTF_Func GetLOBBY_LEAVE_USER_NTF_Func();

		PktLobbyLeaveUserInfoNtfQue* GetPktLobbyLeaveUserInfoNtfQue();

		//�κ� ä��
		LOBBY_CHAT_RES_Func GetLOBBY_CHAT_RES_Func();
		PktLobbyChatResQue* GetPktLobbyChatResQue();

		LOBBY_CHAT_NTF_Func GetLOBBY_CHAT_NTF_Func();
		PktLobbyChatNtfQue* GetPktLobbyChatNtfQue();

	private:
		//�κ� ����Ʈ ��û
		void NotifyLOBBY_LIST_RES(PacketBodyPtr pPacket);

		LobbyPacketQue m_LobbyPacketQue;

		//�κ� ���� ��û
		void NotifyLOBBY_ENTER_RES(PacketBodyPtr pPacket);

		LobbyEnterPacketQue m_LobbyEnterPacketQue;

		//�κ� ���ο� ���� ����
		void NotifyLOBBY_ENTER_USER_NTF(PacketBodyPtr pPacket);

		LobbyNewUserInfoNtfQue m_LobbyNewUserInfoNtfQue;

		//�κ� �� ���
		void NotifyLOBBY_ENTER_ROOM_LIST_RES(PacketBodyPtr pPacket);

		PktLobbyRoomListResQue m_LobbyRoomListResQue;

		//�κ� ���� ���
		void NotifyLOBBY_ENTER_USER_LIST_RES(PacketBodyPtr pPacket);

		PktLobbyUserListResQue m_LobbyUserListResQue;

		//�κ� ������
		void NotifyLOBBY_LEAVE_RES(PacketBodyPtr pPacket);

		PktLobbyLeaveResQue m_LobbyLeaveResQue;

		//�κ񿡼� ���� ����
		void NotifyLOBBY_LEAVE_USER_NTF(PacketBodyPtr pPacket);

		PktLobbyLeaveUserInfoNtfQue m_LobbyLeaveUserInfoNtfQue;

		//�κ� ä��
		void NotifyLOBBY_CHAT_RES(PacketBodyPtr pPacket);

		PktLobbyChatResQue m_LobbyChatResQue;

		void NotifyLOBBY_CHAT_NTF(PacketBodyPtr pPacket);

		PktLobbyChatNtfQue m_LobbyChatNtfQue;
	};
}
