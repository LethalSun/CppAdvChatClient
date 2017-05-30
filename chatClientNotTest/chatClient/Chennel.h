#pragma once

namespace MDNetwork
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

	class Chennel :public Manager::Scene
	{


	public:

		void init() override;
		void update() override;
		void draw() const override;

	private:
		//�κ� ���� ����Ȯ��
		bool CheckNewMenber();
		std::deque<String> m_NewUserId;

		void SetNewUser();

		//�� ����Ʈ Ȯ�� �Լ�
		int GetRoomList();

		//���� ����Ʈ
		std::array<RoomInfo, 5> m_RoomList;

		//�κ��� ���
		std::array<MemberInfo, 20> m_MemberList;

		//������ siv3d�� �ε���
		std::array<String, 5> m_RoomIndex;
		std::array<String, 20> m_MemberIndex;

		//���� ������ �濡 ���� ����
		int m_RoomId{ -1 };

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
		short m_CurRoomIndex = -1;
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

		//������ siv3d�� �ε����� ����� �Լ�
		int MakeRoomIndex(int pNum);
		int MakeMemberIndex(int pNum);

		//showwindow�� ǥ���� �ؽ�Ʈ.
		String m_PresentText{ L"�����ϼ̽��ϴ�.\n" };
	};

}