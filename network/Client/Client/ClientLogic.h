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

		//send 함수를 받아오는 함수
		void GetNetworkSendFunc(SendFunc pSendfunc);

		//--++로그인
		
		//로그인 리퀘스트 패킷을 보내는 함수
		int SendPktLogInReq(char* pID, char* pPW);
		
		//옵저버로 부터 큐 받아오는 함수
		int SetLOGIN_IN_RES_Que(LoginPacketQue* pQue);

		//서버에서 로그인 되었는지 확인을 하는 함수.
		bool IsLogin();


		//--++채널 리스트 요청

		//채널 리스트 요청 패킷을 보내는 함수
		int SendPktLobbyListInfo();

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_LIST_RES_Que(LobbyListInfoQue* pQue);

		//채널의 리스트를 확인하는 함수
		ChennelInfo GetLobbyList(int& pIndexCount);


		//--++채널 입장 요청

		//채널 입장 요청 패킷을 보내는 함수
		int SendPktLobbyEnter(short pLobbyId);

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_ENTER_RES_Que(LobbyEnterPacketQue* pQue);

		bool IsLobbyEnterAllowed();

		MaxUserAndRoom GetUserAndRoomCount();
		
		
		//--++입장 공지

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_ENTER_USER_NTF_Que(LobbyNewUserInfoNtfQue* pQue);

		bool IsThereNewUser();
		void GetNewUser(char * pNewUserId);
		
		
		//--++방리스트 요청

		//채널의 방 리스트 요청패킷을 보내는 함수
		int SendPktRoomList(short pStartIndex);

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_ENTER_ROOM_LIST_RES_Que(PktLobbyRoomListResQue* pQue);

		//방의 리스트를 받아오는 함수
		int TryGetRoomList();
		
		//방의 리스트를 복사하는 함수
		RoomRetInfo CopyRoomList();


		//--++채널 유저 리스트 요청

		//채널의 유저 리스트 요청패킷을 보내는 함수
		int SendPktLobbyUserList(short pStartIndex);

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_ENTER_USER_LIST_RES_Que(PktLobbyUserListResQue* pQue);

		//유저의 리스트를 받아오는 함수
		int TryGetUserList();

		UserRetInfo CopyUserList();


		//--++채널 떠나기
		
		//채널 떠나기 요청 패킷 보내는 함수
		int SendPktLobbyLeave();

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_LEAVE_RES_Que(PktLobbyLeaveResQue* pQue);

		bool CanILeave();


		//--++퇴장 공지

		//옵저버로 부터 큐 받아오는 함수
		int SetLOBBY_LEAVE_USER_NTF(PktLobbyLeaveUserInfoNtfQue* pQue);

		bool IsThereLevedUser();

		void GetLevedUser(char * pNewUserId);
		//--++로비 채팅

		//--++방 입장 요청

		//--++방 퇴장 요청

		//--++방 입장 공지

		//--++방 퇴장 공지

		//--++로비 방 정보 공지

		//--++방 채팅

	private:

		//send 함수
		SendFunc m_SendFunc;


		//--++로그인 
		//관련 변수
		char m_ID[MAX_USER_PASSWORD_SIZE + 1]{ 0, };

		char m_Pw[MAX_USER_PASSWORD_SIZE + 1]{ 0, };

		short m_LoginState = 0;

		LoginPacketQue* m_LoginQue;

		//로그인 리스폰스가 왔을때 로직 함수
		void OnLOGIN_IN_RES();


		//--++채널 리스트
		//관련 변수
		ChennelListArr m_ChennelListArr;

		LobbyListInfoQue* m_LobbyListQue;

		short m_lobbyCount = 0;

		//채널 리스트 리스폰스가 왔을 때 로직 함수

		void OnLOBBY_LIST_RES();

		//--++채널 입장
		//관련변수
		bool m_IsLobby = false;

		short m_MaxRoomCount = 0;

		short m_MaxUserCount = 0;

		LobbyEnterPacketQue* m_LobbyEnterQue;
		//채널엔터 리스폰스가 왔을때 로직 함수.

		void OnLOBBY_ENTER_RES();


		//--++입장 공지
		//관련변수
		LobbyNewUserInfoNtfQue* m_LobbyNewUserQue;

		char m_NewUser[MAX_USER_ID_SIZE + 1];
		//함수
		bool OnLOBBY_ENTER_USER_NTF();


		//--++방리스트 요청
		//관련변수
		PktLobbyRoomListResQue* m_LobbyRoomListQue;

		RoomListQue RoomList;

		short LastRoomIndex = 0;

		short LastRoomIndexMemory = 0;
		//함수
		bool OnLOBBY_ENTER_ROOM_LIST_RES();

		//--++채널 유저 리스트 요청
		//관련변수
		PktLobbyUserListResQue* m_LobbyUserListQue;

		UserListQue UserList;

		short LastUserIndex = 0;

		short LastUserListMemory = 0;
		//함수
		bool OnLOBBY_ENTER_USER_LIST_RES();

		//--++채널 떠나기
		//관련 변수
		PktLobbyLeaveResQue* m_LobbyLeaveQue;

		bool IsLeaveLobbyAllowed = false;

		//함수
		void OnLOBBY_LEAVE_RES();


		//--++퇴장 공지
		PktLobbyLeaveUserInfoNtfQue* m_LobbyLeaveNtfQue;

		char m_LeavedUser[MAX_USER_ID_SIZE + 1];

		bool OnLOBBY_LEAVE_USER_NTF();

		//--++로비 채팅

		//--++방 입장 요청

		//--++방 퇴장 요청

		//--++방 입장 공지

		//--++방 퇴장 공지

		//--++로비 방 정보 공지

		//--++방 채팅


	};

}
