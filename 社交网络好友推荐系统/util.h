#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include<graphics.h>

#include "button.h"

const int MAX_ID_LEN = 6;    // id最大长度

inline std::string get_new_id() {
    std::ifstream infile("people_id.txt");    // 打开用户id文件
    std::string line;
    std::string last_line;

    if (infile.is_open()) {
        // 读取最后一行id
        while (std::getline(infile, line)) {
            last_line = line;
        }
        infile.close();
    }
    else {
        return "ERROE";
    }

    // 生成新id
    int id = std::stoi(last_line);
    id++;

    // 使用stringstream格式化输出新ID
    std::stringstream ss;
    ss << std::setw(MAX_ID_LEN) << std::setfill('0') << id;
    std::string new_id = ss.str();

    // 更新ID数据（这里假设是添加新ID到文件末尾作为新的一行）
    std::ofstream outfile("people_id.txt");
    if (outfile.is_open()) {
        outfile << new_id << std::endl;
        outfile.close();
    }
    else {
        return "ERRORwriteIN";
    }
    return new_id;
}

inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putimage_alpha(Vector2 pos, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), (int)pos.x, (int)pos.y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
