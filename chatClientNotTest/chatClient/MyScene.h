#pragma once
namespace MDNetwork
{
	class Network;
	class ClientLogic;
	struct MyScene
	{
	public:
		MyScene() = default;
		~MyScene() = default;

		String loginID{};
		String loginPassWord{};

		short m_LobbyId;
		ClientLogic* m_Logic;

		//TODO:Áö¿ï°Å
		Network* m_Network;
		Font debugFont;
		String str;
	};

}

