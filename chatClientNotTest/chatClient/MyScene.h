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
		//TODO:�����
		Font debugFont;
		String str;
	};

}

