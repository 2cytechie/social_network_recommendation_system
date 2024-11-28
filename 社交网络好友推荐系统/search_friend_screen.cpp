#include "search_friend_screen.h"

void SearchFriendScreen::on_enter() {
	// 弹窗输入
	InputBox(input_str, MAX_ID_LEN, L"请输入查找信息", L"搜索好友");
	if (iswdigit(*input_str)) {
		search_type = SearchType::id;
	}
	else {
		search_type = SearchType::name;
	}
	search_friends_list = search_friends(input_str);
}

void SearchFriendScreen::on_drow() {
	for (int i = 0; i < search_friends_list.size(); i++) {
		search_friends_list[i]->on_drow();
	}
}

void SearchFriendScreen::on_input(const ExMessage& msg) {
	for (int i = 0; i < search_friends_list.size(); i++) {
		search_friends_list[i]->on_update(msg);
	}
}