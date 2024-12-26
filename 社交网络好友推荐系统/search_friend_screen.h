#pragma once
// �������ѣ��鿴�Ƽ�

#include "start_screen.h"
#include "util.h"

extern StartScreen start_screen;					// ��ʼ����

class SearchFriendScreen :public Screen {
public:
	enum class SearchType {
		name,
		id
	};

public:
	SearchFriendScreen() = default;
	~SearchFriendScreen() = default;

	// �������
	void on_enter();
	// ���ƽ���
	void on_drow();
	// ����������
	void on_input(const ExMessage& msg);
	// �˳�����
	void on_exit();

private:
	wchar_t input_str[MAX_ID_LEN] = _T("");				// �����ı�
	SearchType search_type = SearchType::name;			// ��ʼ����������Ϊ����
	std::vector<Button*> search_friends_list;			// �������ĺ���
	std::vector<Button*> button_is_firend;				// ���/����Ӱ���
	Button button_back;									// ���ؼ�


	const int MAX_SHOW_SIZE = 9;						// ��ʾ����û���Ϣ
	const int SHOW_PEOPLE_X = 140;						// ��ʾ�û���ϢX����
	const int SHOW_IS_ADD_X = 1150;						// ��ʾ���/����Ӱ�ťX����
	const Vector2 SHOW_PEOPLE_SIZE = Vector2(1000, 70);	// ��ʾ�û���Ϣ��С
	const Vector2 SHOW_IS_ADD_SIZE = Vector2(120, 70);	// ��ʾ���/����Ӱ�ť��С
};

