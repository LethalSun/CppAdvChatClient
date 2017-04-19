#pragma once
namespace chatClient
{
	class Network;
	struct MyScene
	{
	public:
		MyScene() = default;
		~MyScene() = default;

		String loginID{};
		String loginPassWord{};
		Network* m_Network;
		//TODO:Áö¿ï°Å
		Font debugFont;
		String str;
	};

}

