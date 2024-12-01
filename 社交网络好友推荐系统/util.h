#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include<graphics.h>
#include<vector>

#include "button.h"
// #include "people.h"

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

// ��Ҫ��Button�е�data���и�ֵ
inline std::vector<Button*> search_friends(wchar_t* search_str,bool is_id_search) {
    // �����ļ���ƥ����û�
    std::vector<Button*> search_friends_list;
    for (int i = 0; i < 9; i++) {


        // ����delete
        Button* search_friend = new Button();
        search_friend->set_data(_T("��ţ���أ�����"));

        search_friends_list.push_back(search_friend);
    }
    return search_friends_list;
}

// ��Ҫ��Button�е�data���и�ֵ
inline std::vector<Button*> is_friend(std::vector<Button*> search_friends_list) {
    const LPCTSTR add_str = _T("��Ӻ���");
    const LPCTSTR is_add_str = _T("�����");

    std::vector<Button*> button_is_friend;
    for (int i = 0; i < 9; i++) {
        Button* is_friend = new Button();

        is_friend->set_data(is_add_str);
        button_is_friend.push_back(is_friend);
    }
    
    return button_is_friend;
}

inline std::vector<Button*> recommendations_friends() {


    std::vector<Button*> recommendations_friends_list;
    for (int i = 0; i < 10; i++) {
        Button* recommendations_friend = new Button();
        recommendations_friend->set_data(_T("���Ϻã�"));

        recommendations_friends_list.push_back(recommendations_friend);
    }

    return recommendations_friends_list;
}

inline std::vector<Button*> find_friends() {


    std::vector<Button*> friends_list;
    for (int i = 0; i < 10; i++) {
        Button* Friend = new Button();
        Friend->set_data(_T("�����ѣ�"));

        friends_list.push_back(Friend);
    }

    return friends_list;
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
