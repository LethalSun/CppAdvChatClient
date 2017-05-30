#pragma once

namespace MDNetwork
{

	class Login : public Manager::Scene
	{
	public:

		void init() override;

		void update() override;


	private:
		GUI loginWindow{ GUIStyle::Default };
		
		int SendLoginPack();

		int LoginProcess();

		int CheckLoginState();

		Font font;
	};

}

