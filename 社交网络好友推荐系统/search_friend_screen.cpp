#include "search_friend_screen.h"

void SearchFriendScreen::on_enter() {
	// ��������
	InputBox(input_str, MAX_ID_LEN, L"�����������Ϣ", L"��������");

	button_back.set_pos(10, 0);
	button_back.set_size(120, 630);
	button_back.set_data(_T("����"));
	
	// �ж������ı������ֻ����ַ���
	if (iswdigit(*input_str)) {
		search_type = SearchType::id;
	}
	else {
		search_type = SearchType::name;
	}

	// �����ⲿ�ӿڸ��������б�
	search_friends_list = search_friends(input_str,search_type == SearchType::id);
	button_is_firend = is_friend(search_friends_list);

	int max_show = search_friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : search_friends_list.size();
	for (int i = 0; i < max_show; i++) {
		search_friends_list[i]->set_pos(SHOW_PEOPLE_X, i * SHOW_PEOPLE_SIZE.y);
		search_friends_list[i]->set_size(SHOW_PEOPLE_SIZE);
		button_is_firend[i]->set_pos(SHOW_IS_ADD_X,i* SHOW_IS_ADD_SIZE.y);
		button_is_firend[i]->set_size(SHOW_IS_ADD_SIZE);
	}
}

void SearchFriendScreen::on_drow() {
	button_back.on_drow();

	int max_show = search_friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : search_friends_list.size();
	for (int i = 0; i < max_show; i++) {
		search_friends_list[i]->on_drow();
		button_is_firend[i]->on_drow();
	}
}

void SearchFriendScreen::on_input(const ExMessage& msg) {
	button_back.on_update(msg);

	int max_show = search_friends_list.size() > MAX_SHOW_SIZE ? MAX_SHOW_SIZE : search_friends_list.size();
	for (int i = 0; i < max_show; i++) {
		search_friends_list[i]->on_update(msg);
		button_is_firend[i]->on_update(msg);
	}

	if (button_back.is_press()) {
		on_exit();
	}
}

void SearchFriendScreen::on_exit() {
	// �ͷ�������ڴ��ֹ�ڴ�й¶
	for (int i = 0; i < search_friends_list.size(); i++) {
		delete search_friends_list[i];
	}
	search_friends_list.clear();

	for (int i = 0; i < button_is_firend.size(); i++) {
		delete button_is_firend[i];
	}
	button_is_firend.clear();

	// �˳�����ѡ��ʼ����
	start_screen.switch_to(StartScreen::ScreenType::start);
}