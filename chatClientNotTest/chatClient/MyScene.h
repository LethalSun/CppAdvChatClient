#pragma once
namespace MDNetwork
{
	class Network;
	class ClientLogic;

	enum class SceneState
	{
		LoginScene = 0,
		LobbyScene = 1,
		ChennelScene = 2,
		RoomScene = 3,
	};

	struct UserInfo
	{
		String UserId;
		bool IsAlive = false;
		short RoomIndex;
	};

	struct RoomInfo
	{
		short RoomIndex;
		short UserCount;
		String Title;
	};

	struct LobbyInfo
	{
		short LobbyId = -1;
		short UserCount = -1;
		short RoomCount = -1;
		String LobbyName;
	};

	struct MyScene
	{
	public:
		MyScene() = default;

		~MyScene() = default;

		String loginID{};

		String loginPassWord{};

		ClientLogic* m_Logic;

		SceneState m_Scene = SceneState::LoginScene;

		std::array<UserInfo, 50> m_UserArray;

		std::array<RoomInfo, 20> m_RoomArray;

		LobbyInfo m_LobbyInfo;

		//TODO:Áö¿ï°Å
		Network* m_Network;
		Font debugFont;
		String str;
	};

}

