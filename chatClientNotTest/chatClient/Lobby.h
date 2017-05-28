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
		
		//MaxLobbyCount = 2
		//TODO:vector 로 바꿔서 임의의 개수의 로비개수에 대응하게

		//채널의 인덱스와 이름
		std::array<LobbyInfo, 2> m_ChennelList{};

		//어떤 채널을 선택했는지 체크
		int CheckSelectedChannelNum();
		int selectedChannelNum = -1;

		//체널패킷 보내는 함수
		int GetLobbyListFromServer();
		int SendGetLobbyPacket();
		int timer = 0;
		//체널 입장패킷 보내는 함수

		int SendEnterLobbyPacket();
		int EnterLobby();

		// 패킷을 받아오는 부분 TODO:나중에 패킷프로세스에 넣어야 할부분
		int GetPacket();

		//TODO:방금 로비에 입장한 사람을 받아오는 부분은 여기인가? 

		bool m_IsAvailable = false;
		Font font;
	};
}

