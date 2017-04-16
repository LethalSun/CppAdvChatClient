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

		int AddTextAndButton(GUI, int , String);

		int AddText(GUI, int, String);

		//���� ����Ʈ
		std::array<String, 7> roomList{};

		//���� �濡 �ִ� ���
		std::array<String, 5> memberList{};

		std::array<String, 7> roomIndex{};
		std::array<String, 5> memberIndex{};

		int MakeRoomIndex();
		int MakeMemberIndex();

		//TODO:ä�ó����� ǥ���ϱ� ���ؼ� ��Ʈ�� ������ �ؾ� �Ѵ�.
		//�����ڸ� �߾��� ���� ����ְ����� �ٲ۴� 
		//http://play-siv3d.hateblo.jp/entry/ref/string
	};
}


