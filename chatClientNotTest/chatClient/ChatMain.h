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

		int AddTextAndButton(GUI, int , String);

		int AddText(GUI, int, String);

		//방의 리스트
		std::array<String, 7> roomList{};

		//같은 방에 있는 멤버
		std::array<String, 5> memberList{};

		std::array<String, 7> roomIndex{};
		std::array<String, 5> memberIndex{};

		int MakeRoomIndex();
		int MakeMemberIndex();

		//TODO:채팅내용을 표시하기 위해서 스트링 편집을 해야 한다.
		//구분자를 발언자 마다 집어넣고줄을 바꾼다 
		//http://play-siv3d.hateblo.jp/entry/ref/string
	};
}


