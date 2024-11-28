#pragma once
// �������ѣ��鿴�Ƽ�

#include "screen.h"
#include "util.h"
#include<vector>

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

private:
	wchar_t input_str[MAX_ID_LEN];					// �����ı�
	SearchType search_type;							// ��������
	std::vector<Button*> search_friends_list;		// �������ĺ���
};

