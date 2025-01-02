#include<graphics.h>
#include<chrono>
#include<thread>

#include "start_screen.h"
#include "search_friend_screen.h"
#include "recommendations_screen.h"
#include "add_interests_screen.h"
#include "friends_screen.h"
#include "people.h"

IMAGE white_screen;							// 空白界面图片

People myself("10100001","空白");			// 该用户信息

StartScreen start_screen;					// 开始界面
Screen* friends_screen = nullptr;			// 好有列表界面
Screen* search_friend_screen = nullptr;		// 搜索好友界面
Screen* add_interests_screen = nullptr;		// 添加爱好界面
Screen* recommendations_screen = nullptr;	// 查看推荐界面

void load_people(People &p) {
    std::ifstream file("SocialMediaUsersDataset.csv");

    if (file.is_open()) {
		std::string line;
		// 存储提取的column列数据
		std::vector<std::string> data;
		int id_height = std::stoi(p.get_id()) - 10000000 + 1;
		while (std::getline(file, line)) {
			id_height--;
			if (id_height <= 0) {
				int start_idx = line.find('\"');
				int end_idx = line.find_last_of('\"');
				std::string interests_data = line.substr(start_idx, end_idx - start_idx);
				std::stringstream ss(interests_data);
				std::string cell;
				while (std::getline(ss, cell, ',')) {
					data.push_back(cell.substr(2, cell.size() - 3));
				}
				break;
			}
		}
		// 输出提取的column列数据
		for (const auto& d : data) {
			p.add_interest(d);
		}
        file.close();
    }
}

void load_resources() {
	load_people(myself);

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
	recommendations_screen = new RecommendationsScreen();
	add_interests_screen = new AddInterestsScreen();
	friends_screen = new FriendsScreen();

	BeginBatchDraw();

	load_resources();			// 加载资源
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