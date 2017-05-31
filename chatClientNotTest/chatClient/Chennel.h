#pragma once

namespace MDNetwork
{
	//struct RoomInfo
	//{
	//	short RoomIndex = -1;
	//	short RoomUserCount = 0;
	//	String RoomTitle = L"empty";
	//};
	//
	struct MemberInfo
	{
		bool IsEmpty = true;
		String MenberId;
	};

	class Chennel :public Manager::Scene
	{


	public:

		void init() override;
		void update() override;
		void draw() const override;

	private:
		//로비 입장 공지확인
		bool CheckNewMenber();
		std::deque<String> m_NewUserId;

		void SetNewUser();

		//로비 퇴장 공지 확인
		bool CheckLeavedMember();
		std::deque<String> m_LeavedUserId;

		void RemoveUser();
		//방 리스트 확인 함수
		int GetRoomList();

		int SetRoomList();

		//멤버 리스트 확인 함수
		int GetUserList();
		int SetUserList();
		int UpdateLobbyMember();
		int UpdateLobbyRoom();


		//로비 나가기

		//방 입장

		//채팅
		void GetTextFromInput();

		int updateTextField();
		//방의 리스트
		std::array<RoomInfo, 5> m_RoomList;

		//로비의 멤버
		std::array<MemberInfo, 20> m_MemberList;

		//현재 입장한 방에 대한 정보
		int m_RoomId{ -1 };

		//update 에서 눌린 방의 인덱스를 확인한다.
		int CheckRoomListButton();

		int SetGuiText(GUI gui, String textName, String newText);

		//각각의 siv3d용 인덱스
		std::array<String, 5> m_RoomIndex;
		std::array<String, 20> m_MemberIndex;

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

		//각각의 siv3d용 인덱스를 만드는 함수
		int MakeRoomIndex(int pNum);
		int MakeMemberIndex(int pNum);

		//showwindow에 표현될 텍스트.
		String m_PresentText{ L"입장하셨습니다.\n" };
	};

}