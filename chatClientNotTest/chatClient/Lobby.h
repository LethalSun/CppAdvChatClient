#pragma once
namespace MDNetwork
{
	class Lobby :public Manager::Scene
	{
		//로비 이름은 channel: 숫자 형태
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

		//채널의 인덱스와 이름
		std::array<LobbyInfo, 2> m_ChennelList{};

		//어떤 채널을 선택했는지 체크
		int CheckSelectedChannelNum();

		bool IsChennelSelected();

		int selectedChannelNum = -1;

		int m_NumOfCheckingForIsAllowed = 0;

		//체널 리스트 패킷 보내는 함수
		int GetLobbyListFromServer();

		int refreshTimeForChennelList = 0;

		//체널 입장
		int EnterLobby();

		Font font;
	};
}

