#pragma once

namespace MDNetwork
{


	class Chennel :public Manager::Scene
	{
		struct RoomInfo
		{
			short RoomIndex;
			short RoomUserCount;
			String RoomTitle = L"empty";
		};

		struct MemberInfo
		{
			bool IsEmpty = true;
			String MenberId;
		};

	public:
		void init() override;
		void update() override;
		void draw() const override;
	private:

		//각 gui초기화
		int InitRoomWindow();
		int InitInputWindow();
		int InitShowWindow();
		int InitMemberWindow();

		//각각의 창들
		GUI showWindow{ GUIStyle::Default };
		GUI inputWindow{ GUIStyle::Default };
		GUI roomWindow{ GUIStyle::Default };
		GUI memberWindow{ GUIStyle::Default };

		// 각각의 gui 에 버튼과 텍스트를 추가해주는 함수 
		int AddTextAndButton(GUI gui, int listIndex, String name);
		int AddText(GUI gui, int listIndex, String name);

		//방의 리스트
		std::array<String, 5> roomList{};

		//로비의 멤버
		std::array<String, 20> memberList{};

		//각각의 siv3d용 인덱스
		std::array<String, 5> roomIndex{};
		std::array<String, 20> memberIndex{};

		//각각의 siv3d용 인덱스를 만드는 함수
		int MakeRoomIndex(int pNum);
		int MakeMemberIndex(int pNum);

		//현재 입장한 방에 대한 정보
		int m_RoomId{ -1 };

		//showwindow에 표현될 텍스트.
		String m_PresentText{ L"입장하셨습니다.\n" };

		//update 에서 눌린 방의 인덱스를 확인한다.
		int CheckRoomListButton();

		//받아온 채팅내용을 띄워 주는 함수
		//TODO:채팅내용을 표시하기 위해서 스트링 편집을 해야 한다.
		//구분자를 발언자 마다 집어넣고줄을 바꾼다 
		//http://play-siv3d.hateblo.jp/entry/ref/string
		int updateTextField();


		//TODO:나중에 패킷 프로세스로 가야 할 부분
		int GetPacket();

		//로비내의 방의 리스트를 받아온다.
		int SendGetRoomListPacket();
		short m_RoomIndex = -1;
		bool m_IsRoomListEnd = false;
		short m_timer = 0;
		Font font;
		bool m_IsGeted = true;
		std::array<RoomInfo, 20> roomInfos{ 0, };

		//받아온 방리스트를 띄운다.
		int SetRoomList();
		bool IsRoomSeted = false;

		//로비의 멤버 리스트를 가져오고 세팅한다.
		int GetMemberList();
		int SetMemberList();
		int SetGuiText(GUI gui, String textName, String newText);

		//로비에 들어온 사람이라면 방에 나중에 들어온 사람의 아이디를 받아온다
		std::array<MemberInfo, 50> m_members;
		int UpdateLobbyMember();

		//채팅
		int SendChat;
	};

}