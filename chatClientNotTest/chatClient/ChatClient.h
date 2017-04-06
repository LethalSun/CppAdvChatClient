#pragma once
class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	int Update();
private:
	GUI loginWindow;
	GUI mainWindow;

};

