#pragma once
namespace chatClient
{
	class Lobby :public Manager::Scene
	{
	public:
		void init() override;

		void update() override;

		void draw() const override;

	private:
		GUI channelWindow{ GUIStyle::Default };

		int CheckSelectedChannelNum();
		int selectedChannelNum = -1;
	};
}

