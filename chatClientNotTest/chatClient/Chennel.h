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
		//�κ� ���� ����Ȯ��
		bool CheckNewMenber();
		std::deque<String> m_NewUserId;

		void SetNewUser();

		//�κ� ���� ���� Ȯ��
		bool CheckLeavedMember();
		std::deque<String> m_LeavedUserId;

		void RemoveUser();
		//�� ����Ʈ Ȯ�� �Լ�
		int GetRoomList();

		int SetRoomList();

		//��� ����Ʈ Ȯ�� �Լ�
		int GetUserList();
		int SetUserList();
		int UpdateLobbyMember();
		int UpdateLobbyRoom();


		//�κ� ������

		//�� ����

		//ä��
		void GetTextFromInput();

		int updateTextField();
		//���� ����Ʈ
		std::array<RoomInfo, 5> m_RoomList;

		//�κ��� ���
		std::array<MemberInfo, 20> m_MemberList;

		//���� ������ �濡 ���� ����
		int m_RoomId{ -1 };

		//update ���� ���� ���� �ε����� Ȯ���Ѵ�.
		int CheckRoomListButton();

		int SetGuiText(GUI gui, String textName, String newText);

		//������ siv3d�� �ε���
		std::array<String, 5> m_RoomIndex;
		std::array<String, 20> m_MemberIndex;

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