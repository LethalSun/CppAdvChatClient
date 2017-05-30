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
		int AddTextAndButton(GUI gui, int listIndex, String name);
		int AddText(GUI gui, int listIndex, String name);

		//���� ����Ʈ
		std::array<String, 5> roomList{};

		//�κ��� ���
		std::array<String, 20> memberList{};

		//������ siv3d�� �ε���
		std::array<String, 5> roomIndex{};
		std::array<String, 20> memberIndex{};

		//������ siv3d�� �ε����� ����� �Լ�
		int MakeRoomIndex(int pNum);
		int MakeMemberIndex(int pNum);

		//���� ������ �濡 ���� ����
		int m_RoomId{ -1 };

		//showwindow�� ǥ���� �ؽ�Ʈ.
		String m_PresentText{ L"�����ϼ̽��ϴ�.\n" };

		//update ���� ���� ���� �ε����� Ȯ���Ѵ�.
		int CheckRoomListButton();

		//�޾ƿ� ä�ó����� ��� �ִ� �Լ�
		//TODO:ä�ó����� ǥ���ϱ� ���ؼ� ��Ʈ�� ������ �ؾ� �Ѵ�.
		//�����ڸ� �߾��� ���� ����ְ����� �ٲ۴� 
		//http://play-siv3d.hateblo.jp/entry/ref/string
		int updateTextField();


		//TODO:���߿� ��Ŷ ���μ����� ���� �� �κ�
		int GetPacket();

		//�κ��� ���� ����Ʈ�� �޾ƿ´�.
		int SendGetRoomListPacket();
		short m_RoomIndex = -1;
		bool m_IsRoomListEnd = false;
		short m_timer = 0;
		Font font;
		bool m_IsGeted = true;
		std::array<RoomInfo, 20> roomInfos{ 0, };

		//�޾ƿ� �渮��Ʈ�� ����.
		int SetRoomList();
		bool IsRoomSeted = false;

		//�κ��� ��� ����Ʈ�� �������� �����Ѵ�.
		int GetMemberList();
		int SetMemberList();
		int SetGuiText(GUI gui, String textName, String newText);

		//�κ� ���� ����̶�� �濡 ���߿� ���� ����� ���̵� �޾ƿ´�
		std::array<MemberInfo, 50> m_members;
		int UpdateLobbyMember();

		//ä��
		int SendChat;
	};

}