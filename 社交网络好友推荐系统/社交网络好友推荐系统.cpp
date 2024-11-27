#include<iostream>
#include<string>
#include<graphics.h>
#include<chrono>
#include<thread>

#include "util.h"

using namespace std;

IMAGE white_screen;				// 空白界面

Button button1(100, 100);
Button button2(500, 100);
Button button3(1000, 100);

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

	bool is_running = true;

	BeginBatchDraw();

	load_resources();

	while (is_running) {
		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		// 数据更新
		while (peekmessage(&msg)) {

		}


		// 绘制图像
		putimage(0, 0, &white_screen);



		drow_idle_button(button1);
		drow_touch_button(button2);
		drow_press_button(button3);


		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0)) {
			std::this_thread::sleep_for(sleep_duration);
		}
	}
	EndBatchDraw();
	
	return 0;
}