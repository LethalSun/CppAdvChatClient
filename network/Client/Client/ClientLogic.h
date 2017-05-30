#pragma once

namespace MDNetwork
{
	class SocketNetwork;

	using SendFunc = std::function<int(const short, const short, char*)>;
	
	using LoginPacketQue = concurrency::concurrent_queue<short>;
	
	using LobbyListInfoQue = concurrency::concurrent_queue<PktLobbyListRes>;

	using LobbyEnterPacketQue = concurrency::concurrent_queue<PktLobbyEnterRes>;

	using LobbyNewUserInfoNtfQue = concurrency::concurrent_queue<PktLobbyNewUserInfoNtf>;

	using PktLobbyRoomListResQue = concurrency::concurrent_queue<PktLobbyRoomListRes>;

	using PktLobbyUserListResQue = concurrency::concurrent_queue<PktLobbyUserListRes>;

	using PktLobbyLeaveResQue = concurrency::concurrent_queue<short>;

	using PktLobbyLeaveUserInfoNtfQue = concurrency::concurrent_queue<PktLobbyLeaveUserInfoNtf>;
	
	using ChennelInfo = std::tuple<short, short>;

	using MaxUserAndRoom = std::tuple<short, short>;

	using ChennelListArr = std::array<std::tuple<short, short>, MAX_LOBBY_LIST_COUNT>;

	using RoomListQue = std::deque<RoomSmallInfo>;
		
	using UserListQue = std::deque<UserSmallInfo>;

	using RoomRetInfo = std::tuple<short, short, wchar_t*>;
	
	using UserRetInfo = std::tuple<short, char*>;

	class ClientLogic
	{
	public:

		ClientLogic();

		~ClientLogic();

		//send �Լ��� �޾ƿ��� �Լ�
		void GetNetworkSendFunc(SendFunc pSendfunc);

		//--++�α���
		
		//�α��� ������Ʈ ��Ŷ�� ������ �Լ�
		int SendPktLogInReq(char* pID, char* pPW);
		
		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOGIN_IN_RES_Que(LoginPacketQue* pQue);

		//�������� �α��� �Ǿ����� Ȯ���� �ϴ� �Լ�.
		bool IsLogin();


		//--++ä�� ����Ʈ ��û

		//ä�� ����Ʈ ��û ��Ŷ�� ������ �Լ�
		int SendPktLobbyListInfo();

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_LIST_RES_Que(LobbyListInfoQue* pQue);

		//ä���� ����Ʈ�� Ȯ���ϴ� �Լ�
		ChennelInfo GetLobbyList(int& pIndexCount);


		//--++ä�� ���� ��û

		//ä�� ���� ��û ��Ŷ�� ������ �Լ�
		int SendPktLobbyEnter(short pLobbyId);

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_ENTER_RES_Que(LobbyEnterPacketQue* pQue);

		bool IsLobbyEnterAllowed();

		MaxUserAndRoom GetUserAndRoomCount();
		
		
		//--++���� ����

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_ENTER_USER_NTF_Que(LobbyNewUserInfoNtfQue* pQue);

		bool IsThereNewUser();
		void GetNewUser(char * pNewUserId);
		
		
		//--++�渮��Ʈ ��û

		//ä���� �� ����Ʈ ��û��Ŷ�� ������ �Լ�
		int SendPktRoomList(short pStartIndex);

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_ENTER_ROOM_LIST_RES_Que(PktLobbyRoomListResQue* pQue);

		//���� ����Ʈ�� �޾ƿ��� �Լ�
		int TryGetRoomList();
		
		//���� ����Ʈ�� �����ϴ� �Լ�
		RoomRetInfo CopyRoomList();


		//--++ä�� ���� ����Ʈ ��û

		//ä���� ���� ����Ʈ ��û��Ŷ�� ������ �Լ�
		int SendPktLobbyUserList(short pStartIndex);

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_ENTER_USER_LIST_RES_Que(PktLobbyUserListResQue* pQue);

		//������ ����Ʈ�� �޾ƿ��� �Լ�
		int TryGetUserList();

		UserRetInfo CopyUserList();


		//--++ä�� ������
		
		//ä�� ������ ��û ��Ŷ ������ �Լ�
		int SendPktLobbyLeave();

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_LEAVE_RES_Que(PktLobbyLeaveResQue* pQue);

		bool CanILeave();


		//--++���� ����

		//�������� ���� ť �޾ƿ��� �Լ�
		int SetLOBBY_LEAVE_USER_NTF(PktLobbyLeaveUserInfoNtfQue* pQue);

		bool IsThereLevedUser();

		void GetLevedUser(char * pNewUserId);
		//--++�κ� ä��

		//--++�� ���� ��û

		//--++�� ���� ��û

		//--++�� ���� ����

		//--++�� ���� ����

		//--++�κ� �� ���� ����

		//--++�� ä��

	private:

		//send �Լ�
		SendFunc m_SendFunc;


		//--++�α��� 
		//���� ����
		char m_ID[MAX_USER_PASSWORD_SIZE + 1]{ 0, };

		char m_Pw[MAX_USER_PASSWORD_SIZE + 1]{ 0, };

		short m_LoginState = 0;

		LoginPacketQue* m_LoginQue;

		//�α��� ���������� ������ ���� �Լ�
		void OnLOGIN_IN_RES();


		//--++ä�� ����Ʈ
		//���� ����
		ChennelListArr m_ChennelListArr;

		LobbyListInfoQue* m_LobbyListQue;

		short m_lobbyCount = 0;

		//ä�� ����Ʈ ���������� ���� �� ���� �Լ�

		void OnLOBBY_LIST_RES();

		//--++ä�� ����
		//���ú���
		bool m_IsLobby = false;

		short m_MaxRoomCount = 0;

		short m_MaxUserCount = 0;

		LobbyEnterPacketQue* m_LobbyEnterQue;
		//ä�ο��� ���������� ������ ���� �Լ�.

		void OnLOBBY_ENTER_RES();


		//--++���� ����
		//���ú���
		LobbyNewUserInfoNtfQue* m_LobbyNewUserQue;

		char m_NewUser[MAX_USER_ID_SIZE + 1];
		//�Լ�
		bool OnLOBBY_ENTER_USER_NTF();


		//--++�渮��Ʈ ��û
		//���ú���
		PktLobbyRoomListResQue* m_LobbyRoomListQue;

		RoomListQue RoomList;

		short LastRoomIndex = 0;

		short LastRoomIndexMemory = 0;
		//�Լ�
		bool OnLOBBY_ENTER_ROOM_LIST_RES();

		//--++ä�� ���� ����Ʈ ��û
		//���ú���
		PktLobbyUserListResQue* m_LobbyUserListQue;

		UserListQue UserList;

		short LastUserIndex = 0;

		short LastUserListMemory = 0;
		//�Լ�
		bool OnLOBBY_ENTER_USER_LIST_RES();

		//--++ä�� ������
		//���� ����
		PktLobbyLeaveResQue* m_LobbyLeaveQue;

		bool IsLeaveLobbyAllowed = false;

		//�Լ�
		void OnLOBBY_LEAVE_RES();


		//--++���� ����
		PktLobbyLeaveUserInfoNtfQue* m_LobbyLeaveNtfQue;

		char m_LeavedUser[MAX_USER_ID_SIZE + 1];

		bool OnLOBBY_LEAVE_USER_NTF();

		//--++�κ� ä��

		//--++�� ���� ��û

		//--++�� ���� ��û

		//--++�� ���� ����

		//--++�� ���� ����

		//--++�κ� �� ���� ����

		//--++�� ä��


	};

}
