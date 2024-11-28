#pragma once
// 搜索好友，查看推荐

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

	// 进入界面
	void on_enter();
	// 绘制界面
	void on_drow();
	// 鼠标键盘输入
	void on_input(const ExMessage& msg);

private:
	wchar_t input_str[MAX_ID_LEN];					// 输入文本
	SearchType search_type;							// 搜索类型
	std::vector<Button*> search_friends_list;		// 搜索到的好友
};

