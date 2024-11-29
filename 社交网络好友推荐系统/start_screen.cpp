#include "start_screen.h"


	// 进入界面
void StartScreen::on_enter() {
	const Vector2 BUTTON_FUN_SIZE(160, 70);
	const int BUTTON_FUN_Y = 640;

	search_friend.set_data(_T("搜索好友"));
	search_friend.set_pos(BUTTON_FUN_SIZE.x/2, BUTTON_FUN_Y);
	search_friend.set_size(BUTTON_FUN_SIZE);

	friends.set_data(_T("好友列表"));
	friends.set_pos(BUTTON_FUN_SIZE.x * 5 / 2, BUTTON_FUN_Y);
	friends.set_size(BUTTON_FUN_SIZE);

	add_interests.set_data(_T("添加爱好"));
	add_interests.set_pos(BUTTON_FUN_SIZE.x * 9 / 2, BUTTON_FUN_Y);
	add_interests.set_size(BUTTON_FUN_SIZE);

	recommendations.set_data(_T("查看推荐"));
	recommendations.set_pos(BUTTON_FUN_SIZE.x * 13 / 2, BUTTON_FUN_Y);
	recommendations.set_size(BUTTON_FUN_SIZE);

	}

	// 绘制界面
void StartScreen::on_drow() {
	if (current_screen != nullptr) current_screen->on_drow();

	search_friend.on_drow();
	friends.on_drow();
	add_interests.on_drow();
	recommendations.on_drow();
	}
	// 鼠标键盘输入
void StartScreen::on_input(const ExMessage& msg) {
	if(current_screen != nullptr) current_screen->on_input(msg);

	Vector2 mouse_pos(msg.x, msg.y);

	// 搜索好友
	search_friend.on_update(msg);
	if (search_friend.is_press()) {
		switch_to(ScreenType::search_friend);
	}
	// 好有列表
	friends.on_update(msg);
	if (friends.is_press()) {
		switch_to(ScreenType::friends);
	}
	// 添加爱好
	add_interests.on_update(msg);
	if (add_interests.is_press()) {
		switch_to(ScreenType::add_interests);
	}
	// 查看推荐
	recommendations.on_update(msg);
	if (recommendations.is_press()) {
		switch_to(ScreenType::recommendations);
	}
}

void StartScreen::switch_to(ScreenType type) {
	switch (type)
	{
	case StartScreen::ScreenType::start:
		current_screen = nullptr;
		break;
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
	if (current_screen != nullptr) current_screen->on_enter();
}
