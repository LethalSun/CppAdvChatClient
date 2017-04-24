#pragma once
namespace chatClient
{
	class ChatMain :public Manager::Scene
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

		//�� gui�ʱ�ȭ
		int InitRoomWindow();

		int InitInputWindow();
		int InitShowWindow();
		int InitMemberWindow();


		//������ â��
		GUI showWindow{ GUIStyle::Default };
		GUI inputWindow{ GUIStyle::Default };
		GUI roomWindow{ GUIStyle::Default };
		GUI memberWindow{ GUIStyle::Default };

		// ������ gui �� ��ư�� �ؽ�Ʈ�� �߰����ִ� �Լ�
		int AddTextAndButton(GUI, int , String);
		int AddText(GUI, int, String);


		////TODO:�ƴϸ� �κ�ȿ� �� �ĺ��� �޾ƿ;� �ϴ°�?


		//���� �濡 ���� ����
		int m_RoomId{ -1 };
		//showwindow�� ǥ���� �ؽ�Ʈ.
		String m_PresentText{L"�����ϼ̽��ϴ�.\n"};

		//���� ����Ʈ
		std::array<String, 20> roomList{};

		//���� �濡 �ִ� ���
		std::array<String, 5> memberList{};

		std::array<String, 20> roomIndex{};
		std::array<String, 5> memberIndex{};

		int MakeRoomIndex();
		int MakeMemberIndex();

		//update ���� ��ư�� ���� Ȯ���Ѵ�.
		int CheckRoomListButton();

		int GetMemberList();
		int SetMemberList();
		int SetGuiText(GUI gui, String textName, String newText);

		int updateTextField();
		//TODO:ä�ó����� ǥ���ϱ� ���ؼ� ��Ʈ�� ������ �ؾ� �Ѵ�.
		//�����ڸ� �߾��� ���� ����ְ����� �ٲ۴� 
		//http://play-siv3d.hateblo.jp/entry/ref/string

		//TODO:���߿� ��Ŷ ���μ����� ���� �� �κ�
		int GetPacket();

		//�κ��� ���� ����Ʈ�� �޾ƿ´�.
		int SendGetRoomListPacket();
		short m_RoomIndex = -1;
		bool m_IsRoomListEnd = false;
		short m_timer = 0;
		Font font;
		bool m_IsGeted = true;
		std::array<RoomInfo, 20> roomInfos{0,};

		//�޾ƿ� �渮��Ʈ�� ����.
		int SetRoomList();
		bool IsRoomSeted = false;

		//�κ� ���� ����̶�� �濡 ���߿� ���� ����� ���̵� �޾ƿ´�
		std::array<MemberInfo, 50> m_members;
		int UpdateLobbyMember();

		//ä��
		int SendChat
	};
}


