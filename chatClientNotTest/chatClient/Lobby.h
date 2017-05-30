#pragma once
namespace MDNetwork
{
	class Lobby :public Manager::Scene
	{
		//�κ� �̸��� channel: ���� ����
		struct LobbyInfo
		{
			String LobbyName = L"empty";
			short LobbyId = -1;
			short LobbyUserCount = 0;
		};

	public:

		void init() override;

		void update() override;

		void draw() const override;

	private:
		GUI channelWindow{ GUIStyle::Default };

		int AddTextAndButton(GUI gui, int listIndex);

		int RenewChannel() ;

		//ä���� �ε����� �̸�
		std::array<LobbyInfo, 2> m_ChennelList{};

		//� ä���� �����ߴ��� üũ
		int CheckSelectedChannelNum();

		bool IsChennelSelected();

		int selectedChannelNum = -1;

		int m_NumOfCheckingForIsAllowed = 0;

		//ü�� ����Ʈ ��Ŷ ������ �Լ�
		int GetLobbyListFromServer();

		int refreshTimeForChennelList = 0;

		//ü�� ����
		int EnterLobby();

		Font font;
	};
}

