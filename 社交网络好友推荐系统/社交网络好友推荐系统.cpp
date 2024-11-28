#include<iostream>
#include<string>
#include<graphics.h>
#include<chrono>
#include<thread>

#include "util.h"

#include "start_screen.h"
#include "search_friend_screen.h"

using namespace std;

IMAGE white_screen;							// 空白界面图片

StartScreen start_screen;					// 开始界面
Screen* friends_screen = nullptr;			// 好有列表界面
Screen* search_friend_screen = nullptr;		// 搜索好友界面
Screen* add_interests_screen = nullptr;		// 添加爱好界面
Screen* recommendations_screen = nullptr;	// 查看推荐界面

void load_resources() {
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&white_screen, _T("resources/white.png"));
}

int main() {
	using namespace std::chrono;

	const nanoseconds frame_duration(1000000000 / 144);					// 帧率144
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;

	initgraph(1280, 720);

	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	bool is_running = true;		// 窗口运行

	// 实例化
	search_friend_screen = new SearchFriendScreen();

	BeginBatchDraw();

	load_resources();			// 加载图片资源
	start_screen.on_enter();

	while (is_running) {
		steady_clock::time_point frame_start = steady_clock::now();

		// 数据更新
		while (peekmessage(&msg)) {
			start_screen.on_input(msg);
		}

		// 绘制图像
		putimage(0, 0, &white_screen);
		start_screen.on_drow();

		FlushBatchDraw();

		// 控制刷新率
		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0)) {
			std::this_thread::sleep_for(sleep_duration);
		}
	}
	EndBatchDraw();
	
	return 0;
}