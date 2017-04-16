#pragma once
class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	int Update();
private:

	//TODO: 3.스테이트 패턴을 사용해서 윈도우 간의 전환.
	//TODO: 신관리 라는것이 존재한다.https://github.com/Siv3D/Reference-JP/wiki/%E3%82%B7%E3%83%BC%E3%83%B3%E7%AE%A1%E7%90%86

	//TODO: 1.우선 메인 윈도우 부터
	//구현 실제 체팅이 이루워지는 공간

	
	//TODO: 2.대화방 선택
	//대화방 최대 갯수.


	String chatInput{};
	//TODO:나중에 지울거
	const Font font;
	const Font font2;

};

