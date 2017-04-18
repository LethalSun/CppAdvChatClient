#pragma once
namespace chatClient
{
	class ChatMain :public Manager::Scene
	{
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
		int AddTextAndButton(GUI, int , String);
		int AddText(GUI, int, String);

		//방의 리스트
		std::array<String, 7> roomList{};
		//현재 방에 대한 정보
		int m_RoomId{ -1 };
		//showwindow에 표현될 텍스트.
		String m_PresentText{L"입장하셨습니다.\n"};

		//같은 방에 있는 멤버
		std::array<String, 5> memberList{};

		std::array<String, 7> roomIndex{};
		std::array<String, 5> memberIndex{};

		int MakeRoomIndex();
		int MakeMemberIndex();

		//update 에서 버튼의 값을 확인한다.
		int CheckRoomListButton();

		int GetMemberList();
		int SetMemberList();
		int SetGuiText(GUI gui, String textName, String newText);

		int updateTextField();
		//TODO:채팅내용을 표시하기 위해서 스트링 편집을 해야 한다.
		//구분자를 발언자 마다 집어넣고줄을 바꾼다 
		//http://play-siv3d.hateblo.jp/entry/ref/string
	};
}


