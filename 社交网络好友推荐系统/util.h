#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include<graphics.h>
#include<vector>

#include "button.h"

const int MAX_ID_LEN = 8;    // id��󳤶�

inline std::string get_new_id() {
    std::ifstream infile("people_id.txt");    // ���û�id�ļ�
    std::string line;
    std::string last_line;

    if (infile.is_open()) {
        // ��ȡ���һ��id
        while (std::getline(infile, line)) {
            last_line = line;
        }
        infile.close();
    }
    else {
        return "ERROE";
    }

    // ������id
    int id = std::stoi(last_line);
    id++;

    // ʹ��stringstream��ʽ�������ID
    std::string new_id = std::to_string(id);

    // ����ID���ݣ���������������ID���ļ�ĩβ��Ϊ�µ�һ�У�
    std::ofstream outfile("people_id.txt", std::ios_base::app);
    if (outfile.is_open()) {
        outfile << new_id << std::endl;
        outfile.close();
    }
    else {
        return "ERRORwriteIN";
    }
    return new_id;
}

inline std::vector<Button*> search_friends(wchar_t* search_str) {
    // �����ļ���ƥ����û�
    std::vector<Button*> search_friends_list;
    for (int i = 0; i < 10; i++) {


        // ����delete


        Button* search_friend = new Button(10, i * 80, 1100, 80);
        search_friends_list.push_back(search_friend);
    }
    return search_friends_list;
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
