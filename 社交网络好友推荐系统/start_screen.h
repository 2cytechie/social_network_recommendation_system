#pragma once

#include "screen.h"
#include "button.h"

extern Screen* friends_screen;
extern Screen* search_friend_screen;
extern Screen* add_interests_screen;
extern Screen* recommendations_screen;

class StartScreen : public Screen{
public:
	StartScreen() = default;
	~StartScreen() = default;

	enum class ScreenType {
		start,
		friends,
		search_friend,
		add_interests,
		recommendations
	};

	// �������
	void on_enter();
	// ���ƽ���
	void on_drow();
	// ����������
	void on_input(const ExMessage& msg);

	void set_current_screen(Screen* screen) {
		current_screen = screen;
		current_screen->on_enter();
	}

	void switch_to(ScreenType type);

private:
	Screen* current_screen = nullptr;

	Button search_friend;						// ���Һ��Ѱ�ť
	Button friends;								// �����б�
	Button add_interests;						// ��Ӱ���
	Button recommendations;						// �鿴�Ƽ�

};