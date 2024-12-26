#include "recommendations_screen.h"

void RecommendationsScreen::on_enter() {
	button_back.set_pos(10, 0);
	button_back.set_size(120, 630);
	button_back.set_data(_T("返回"));

	// 调用外部接口更新搜索列表
	// recommendations_friends_list = recommendations_friends(myself.get_interests());
	recommendations_friends_list = recommendations_friends();

	button_is_firend = is_friend(recommendations_friends_list);

	int max_show = recommendations_friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : recommendations_friends_list.size();
	for (int i = 0; i < max_show; i++) {
		recommendations_friends_list[i]->set_pos(SHOW_PEOPLE_X, i * SHOW_PEOPLE_SIZE.y);
		recommendations_friends_list[i]->set_size(SHOW_PEOPLE_SIZE);
		button_is_firend[i]->set_pos(SHOW_IS_ADD_X, i * SHOW_IS_ADD_SIZE.y);
		button_is_firend[i]->set_size(SHOW_IS_ADD_SIZE);
	}
}

void RecommendationsScreen::on_drow() {
	button_back.on_drow();

	int max_show = recommendations_friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : recommendations_friends_list.size();
	for (int i = 0; i < max_show; i++) {
		recommendations_friends_list[i]->on_drow();
		button_is_firend[i]->on_drow();
	}
}

void RecommendationsScreen::on_input(const ExMessage& msg) {
	button_back.on_update(msg);

	int max_show = recommendations_friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : recommendations_friends_list.size();
	for (int i = 0; i < max_show; i++) {
		recommendations_friends_list[i]->on_update(msg);
		button_is_firend[i]->on_update(msg);
	}

	if (button_back.is_press()) {
		on_exit();
	}
}

void RecommendationsScreen::on_exit() {
	// 释放申请的内存防止内存泄露
	for (int i = 0; i < recommendations_friends_list.size(); i++) {
		delete recommendations_friends_list[i];
	}
	recommendations_friends_list.clear();

	for (int i = 0; i < button_is_firend.size(); i++) {
		delete button_is_firend[i];
	}
	button_is_firend.clear();

	start_screen.switch_to(StartScreen::ScreenType::start);
}