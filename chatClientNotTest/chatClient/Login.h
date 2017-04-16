#pragma once
namespace chatClient
{
	class Login : public Manager::Scene
	{
	public:

		void init() override;

		void update() override;


	private:
		GUI loginWindow{ GUIStyle::Default };


	};

}

