#pragma once
// 搜索好友，查看推荐

#include "start_screen.h"
#include "util.h"

extern StartScreen start_screen;					// 开始界面

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
	// 退出界面
	void on_exit();

private:
	wchar_t input_str[MAX_ID_LEN] = _T("");				// 输入文本
	SearchType search_type = SearchType::name;			// 初始化搜索类型为名字
	std::vector<Button*> search_friends_list;			// 搜索到的好友
	std::vector<Button*> button_is_firend;				// 添加/已添加按键
	Button button_back;									// 返回键


	const int MAX_SHOW_SIZE = 9;						// 显示最大用户信息
	const int SHOW_PEOPLE_X = 140;						// 显示用户信息X坐标
	const int SHOW_IS_ADD_X = 1150;						// 显示添加/已添加按钮X坐标
	const Vector2 SHOW_PEOPLE_SIZE = Vector2(1000, 70);	// 显示用户信息大小
	const Vector2 SHOW_IS_ADD_SIZE = Vector2(120, 70);	// 显示添加/已添加按钮大小
};

