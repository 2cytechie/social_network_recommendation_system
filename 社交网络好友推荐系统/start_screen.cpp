#include "start_screen.h"


	// 进入界面
void StartScreen::on_enter() {
		search_friend.set_data(_T("搜索好友"));
		search_friend.set_pos(60, 650);
		search_friend.set_size(160, 80);

		friends.set_data(_T("好友列表"));
		friends.set_pos(380, 650);
		friends.set_size(160, 80);

		add_interests.set_data(_T("添加爱好"));
		add_interests.set_pos(700, 650);
		add_interests.set_size(160, 80);

		recommendations.set_data(_T("查看推荐"));
		recommendations.set_pos(1020, 650);
		recommendations.set_size(160, 80);


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
