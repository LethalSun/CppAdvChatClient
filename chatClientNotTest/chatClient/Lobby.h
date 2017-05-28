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
		
		//MaxLobbyCount = 2
		//TODO:vector �� �ٲ㼭 ������ ������ �κ񰳼��� �����ϰ�

		//ä���� �ε����� �̸�
		std::array<LobbyInfo, 2> m_ChennelList{};

		//� ä���� �����ߴ��� üũ
		int CheckSelectedChannelNum();
		int selectedChannelNum = -1;

		//ü����Ŷ ������ �Լ�
		int GetLobbyListFromServer();
		int SendGetLobbyPacket();
		int timer = 0;
		//ü�� ������Ŷ ������ �Լ�

		int SendEnterLobbyPacket();
		int EnterLobby();

		// ��Ŷ�� �޾ƿ��� �κ� TODO:���߿� ��Ŷ���μ����� �־�� �Һκ�
		int GetPacket();

		//TODO:��� �κ� ������ ����� �޾ƿ��� �κ��� �����ΰ�? 

		bool m_IsAvailable = false;
		Font font;
	};
}

