#include "start_screen.h"


	// �������
void StartScreen::on_enter() {
		search_friend.set_data(_T("��������"));
		search_friend.set_pos(60, 630);
		search_friend.set_size(160, 80);

		friends.set_data(_T("�����б�"));
		friends.set_pos(380, 630);
		friends.set_size(160, 80);

		add_interests.set_data(_T("��Ӱ���"));
		add_interests.set_pos(700, 630);
		add_interests.set_size(160, 80);

		recommendations.set_data(_T("�鿴�Ƽ�"));
		recommendations.set_pos(1020, 630);
		recommendations.set_size(160, 80);


	}

	// ���ƽ���
void StartScreen::on_drow() {
	//current_screen->on_drow();
	search_friend.on_drow();
	friends.on_drow();
	add_interests.on_drow();
	recommendations.on_drow();
	}
	// ����������
void StartScreen::on_input(const ExMessage& msg) {
	//current_screen->on_input(msg);
	Vector2 mouse_pos(msg.x, msg.y);
	if (search_friend.mouse_in_button(mouse_pos)) {
		search_friend.set_button_state(Button::ButtonState::touch);
		if (msg.message == WM_LBUTTONDOWN) {
			search_friend.set_button_state(Button::ButtonState::press);
			switch_to(ScreenType::search_friend);
		}
	}
	else{
		search_friend.set_button_state(Button::ButtonState::idle);
	}
	if (friends.mouse_in_button(mouse_pos)) {
		friends.set_button_state(Button::ButtonState::touch);
		if (msg.message == WM_LBUTTONDOWN) {
			friends.set_button_state(Button::ButtonState::press);
			switch_to(ScreenType::friends);
		}
	}
	else {
		friends.set_button_state(Button::ButtonState::idle);
	}
	if (add_interests.mouse_in_button(mouse_pos)) {
		add_interests.set_button_state(Button::ButtonState::touch);
		if (msg.message == WM_LBUTTONDOWN) {
			add_interests.set_button_state(Button::ButtonState::press);
			switch_to(ScreenType::add_interests);
		}
	}
	else {
		add_interests.set_button_state(Button::ButtonState::idle);
	}
	if (recommendations.mouse_in_button(mouse_pos)) {
		recommendations.set_button_state(Button::ButtonState::touch);
		if (msg.message == WM_LBUTTONDOWN) {
			recommendations.set_button_state(Button::ButtonState::press);
			switch_to(ScreenType::recommendations);
		}
	}
	else {
		recommendations.set_button_state(Button::ButtonState::idle);
	}
}

void StartScreen::switch_to(ScreenType type) {
	switch (type)
	{
	case StartScreen::ScreenType::friends:
		current_screen = friends_screen;
		break;
	case StartScreen::ScreenType::search_friend:
		current_screen = search_friend_screen;
		break;
	case StartScreen::ScreenType::add_interests:
		current_screen = add_interests_screen;
		break;
	case StartScreen::ScreenType::recommendations:
		current_screen = recommendations_screen;
		break;
	default:
		break;
	}
	current_screen->on_enter();
}
