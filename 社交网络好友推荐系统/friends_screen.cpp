#include "friends_screen.h"

void FriendsScreen::on_enter() {
	button_back.set_pos(10, 0);
	button_back.set_size(120, 630);
	button_back.set_data(_T("返回"));

	// 调用外部接口更新朋友列表
	friends_list = find_friends();
	button_is_friend = is_friend(friends_list);

	size_t max_show = friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : friends_list.size();
	for (size_t i = 0; i < max_show; i++) {
		friends_list[i]->set_pos(SHOW_PEOPLE_X, i * SHOW_PEOPLE_SIZE.y);
		friends_list[i]->set_size(SHOW_PEOPLE_SIZE);
		button_is_friend[i]->set_pos(SHOW_IS_ADD_X, i * SHOW_IS_ADD_SIZE.y);
		button_is_friend[i]->set_size(SHOW_IS_ADD_SIZE);
	}
}

void FriendsScreen::on_drow() {
	button_back.on_drow();

	size_t max_show = friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : friends_list.size();
	for (size_t i = 0; i < max_show; i++) {
		friends_list[i]->on_drow();
		button_is_friend[i]->on_drow();
	}
}

void FriendsScreen::on_input(const ExMessage& msg) {
	button_back.on_update(msg);

	size_t max_show = friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : friends_list.size();
	for (size_t i = 0; i < max_show; i++) {
		friends_list[i]->on_update(msg);
		button_is_friend[i]->on_update(msg);
	}

	if (button_back.is_press()) {
		on_exit();
	}
}

void FriendsScreen::on_exit() {
	// 释放申请的内存防止内存泄露
	for (int i = 0; i < friends_list.size(); i++) {
		delete friends_list[i];
	}
	friends_list.clear();

	for (int i = 0; i < button_is_friend.size(); i++) {
		delete button_is_friend[i];
	}
	button_is_friend.clear();

	start_screen.switch_to(StartScreen::ScreenType::start);
}