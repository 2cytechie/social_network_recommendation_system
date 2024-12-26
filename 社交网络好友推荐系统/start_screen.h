#pragma once

#include "screen.h"
#include "button.h"
// #include "people.h"

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

	// ѡ�����
	void switch_to(ScreenType type);

private:
	Screen* current_screen = nullptr;						// ��ǰ��ʾ�Ľ���

	Button search_friend;									// ���Һ��Ѱ�ť
	Button friends;											// �����б�
	Button add_interests;									// ��Ӱ���
	Button recommendations;									// �鿴�Ƽ�

	const Vector2 BUTTON_FUN_SIZE = Vector2(160, 70);		// ���ܼ���ť��С
	const int BUTTON_FUN_Y = 640;							// ���ܼ���ťY����
};