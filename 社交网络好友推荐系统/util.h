#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <graphics.h>
#include <vector>

#include "button.h"
#include "people.h"

const int MAX_ID_LEN = 8;                   // id最大长度
const int MAX_BUTTON_SIZE = 9;              // 能显示的最大长度
const int ERROR_ID = 10000000;
extern People myself;

// 去某id的兴趣点
inline std::vector<std::string> get_interests(std::string id) {
    std::ifstream file("SocialMediaUsersDataset.csv");
    if (file.is_open()) {
        // 存储表头信息
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;
        // 解析表头，获取列名
        while (std::getline(ssHeader, headerCell, ',')) {
            headers.push_back(headerCell);
        }

        // 兴趣列索引
        int idx = -1;
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == "Interests") {
                idx = i;
                break;
            }
        }

        if (idx != -1) {
            std::string line;

            // 存储提取的column列数据
            std::vector<std::string> data;

            // 行号用于取出第id_height行
            int id_height = std::stoi(id) - 10000000;
            while (std::getline(file, line)) {
                id_height--;
                if (id_height == 0) {
                    // 以"分割字符串
                    int start_idx = line.find('\"');
                    int end_idx = line.find_last_of('\"');

                    // 取""中间的字符串
                    std::string interests_data = line.substr(start_idx, end_idx - start_idx);
                    std::stringstream ss(interests_data);
                    std::string cell;

                    // 将兴趣保存到data中
                    while (std::getline(ss, cell, ',')) {
                        data.push_back(cell.substr(2, cell.size() - 3));
                    }
                    break;
                }
            }
            return data;
        }

        file.close();
    }
}

// 主要对Button中的data进行赋值
inline std::vector<Button*> search_friends(wchar_t* search_wch,bool is_id_search) {
    // 转换类型
    std::string search_str;
    if (search_wch == nullptr) {
        search_str = "";
    }
    else {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wstr(search_wch);
        search_str = converter.to_bytes(wstr);
        if (is_id_search) {
            search_str = std::to_string((std::stoi(search_str) - ERROR_ID) > 0 ? (std::stoi(search_str) - ERROR_ID) : std::stoi(search_str));
        }
    }

    // 搜索文件中匹配的用户
    std::vector<Button*> search_friends_list;

    std::ifstream file("SocialMediaUsersDataset.csv");
    if (file.is_open()) {
        // 存储表头信息
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;

        // 解析表头，获取列名
        while (std::getline(ssHeader, headerCell, ',')) {
            headers.push_back(headerCell);
        }

        // id名字列号
        int idx = -1;
        int id_idx = -1, name_idx = -1;
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == "UserID") {
                id_idx = i;
            }
            if (headers[i] == "Name") {
                name_idx = i;
            }
        }

        // 根据是否是id搜索给idx赋值
        idx = is_id_search ? id_idx : name_idx;

        if (idx != -1) {
            int max_button_size = MAX_BUTTON_SIZE;
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string cell;

                // 找到含serch_str的一行
                if (line.find(search_str) != std::string::npos) {
                    int currentColumnIndex = 0;

                    // 按，分割数据
                    std::vector<std::string> data;

                    while (std::getline(ss, cell, ',')) {
                        // 先把ID放入
                        data.push_back(cell);
                        if (currentColumnIndex == idx) {
                            if (is_id_search) {
                                cell = std::to_string(std::stoi(cell) + ERROR_ID);
                            }

                            while (std::getline(ss, cell, ',')) {
                                data.push_back(cell);
                            }

                            Button* search_friend = new Button();

                            // 将ID和名字传入button类型的data中方便进行渲染
                            std::string button_data = std::to_string(std::stoi(data[id_idx]) + ERROR_ID) + "    " + data[name_idx];

                            // 数据靠左渲染
                            search_friend->set_button_type(Button::TextType::left);
                            search_friend->set_data(button_data);
                            search_friends_list.push_back(search_friend);

                            // 尽量优化性能，只检索max_button_size即9个匹配的数据
                            max_button_size--;
                            if (max_button_size == 0) {
                                break;
                            }
                        }
                        currentColumnIndex++;
                    }
                }
            }
        }

        file.close();
    }

    return search_friends_list;
}

// 主要对Button中的data进行赋值
inline std::vector<Button*> is_friend(std::vector<Button*> search_friends_list) {
    const LPCTSTR add_str = _T("添加好友");
    const LPCTSTR is_add_str = _T("已添加");

    std::vector<Button*> button_is_friend;
    std::vector<std::string> friend_id_list = myself.get_friends();

    // 查找是否已经是好友
    for (int i = 0; i < search_friends_list.size(); i++) {
        Button* button_friend = new Button();
        button_friend->set_data(add_str);
        for (int j = 0; j < friend_id_list.size(); j++) {
            if (search_friends_list[i]->get_data().substr(0, MAX_ID_LEN) == friend_id_list[j]) {
                button_friend->set_data(is_add_str);
            }
        }
        button_is_friend.push_back(button_friend);
    }
    
    return button_is_friend;
}

// 兴趣相似度
inline double similar(Interests myInter, Interests otherInter) {
    double same_inter = 0;
    for (int i = 0; i < myInter.size(); i++) {
        for (int j = 0; j < otherInter.size(); j++) {
            if (myInter[i].interest == otherInter[j].interest) {
                same_inter += otherInter[i].number;
            }
        }
    }

    return same_inter / myInter.get_interests_num();
}

// 推荐的好友
inline std::vector<Button*> recommendations_friends() {
    std::vector<Button*> recommendations_friends_list;

    std::ifstream file("SocialMediaUsersDataset.csv");

    if (file.is_open()) {
        // 存储表头信息
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;

        // 解析表头，获取列名
        while (std::getline(ssHeader, headerCell, ',')) {
            headers.push_back(headerCell);
        }

        // 找到ID和name列号
        int id_idx = -1, name_idx = -1;
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == "UserID") {
                id_idx = i;
            }
            if (headers[i] == "Name") {
                name_idx = i;
            }
        }

        int max_button_size = MAX_BUTTON_SIZE;

        std::string line;

        while (std::getline(file, line)) {
            // 存储提取的interests列数据
            std::vector<std::string> interestsdata;

            // 以"分割字符串
            int start_idx = line.find('\"');
            int end_idx = line.find_last_of('\"');

            // 取出""中的数据
            std::string interests_data = line.substr(start_idx, end_idx - start_idx);
            std::stringstream ss(interests_data);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                interestsdata.push_back(cell.substr(2, cell.size() - 3));
            }

            // 输出提取的兴趣数据并存入otherInter中
            Interests otherInter;
            for (const auto& inter : interestsdata) {
                otherInter.add_interest(inter);
            }

            if (similar(myself.get_interests(), otherInter) > 0.01) {
                // 按，分割数据
                std::vector<std::string> data;

                std::stringstream ss(line);
                std::string cell;
                while (std::getline(ss, cell, ',')) {
                    data.push_back(cell);
                }

                // 将ID和名字传入button类型的data中方便进行渲染
                std::string button_data = std::to_string(std::stoi(data[id_idx]) + ERROR_ID) + "    " + data[name_idx];

                Button* recommendations_friend = new Button();
                recommendations_friend->set_data(button_data);

                // 数据靠左渲染
                recommendations_friend->set_button_type(Button::TextType::left);

                recommendations_friends_list.push_back(recommendations_friend);

                // 尽量优化性能，只检索max_button_size即9个匹配的数据
                max_button_size--;
                if (max_button_size <= 0) {
                    break;
                }
            }
        }

    file.close();
    }

    return recommendations_friends_list;
}

inline std::vector<Button*> find_friends() {
    std::vector<Button*> friends_list;

    int max_button_size = myself.get_friends().size() < MAX_BUTTON_SIZE ? myself.get_friends().size() : MAX_BUTTON_SIZE;
    std::ifstream file("SocialMediaUsersDataset.csv");

    if (file.is_open()) {
        // 存储表头信息
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;

        // 解析表头，获取列名
        while (std::getline(ssHeader, headerCell, ',')) {
            headers.push_back(headerCell);
        }

        int idx = -1;
        int id_idx = -1, name_idx = -1;
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == "UserID") {
                id_idx = i;
            }
            if (headers[i] == "Name") {
                name_idx = i;
            }
        }
        file.close();

        for (int i = 0; i < max_button_size; i++) {
            std::ifstream datafile("SocialMediaUsersDataset.csv");

            // 计算出具体行数
            int idx = std::stoi(myself.get_friends()[i]) - ERROR_ID;
            std::string line;

            while (std::getline(datafile, line) && idx > 0) {
                idx--;
            }

            // 按，分割数据
            std::vector<std::string> data;

            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                data.push_back(cell);
            }

            std::string button_data = std::to_string(std::stoi(data[id_idx]) + ERROR_ID) + "    " + data[name_idx];

            Button* Friend = new Button();
            Friend->set_data(button_data);
            Friend->set_button_type(Button::TextType::left);

            friends_list.push_back(Friend);

            datafile.close();
        }
    }

    return friends_list;
}

inline void add_interest(wchar_t* search_wch) {
    std::string str;
    if (search_wch == nullptr) {
        return;
    }
    //LPCTSTR 转换成 char *
    int num1 = WideCharToMultiByte(CP_OEMCP, NULL, search_wch, -1, NULL, 0, NULL, FALSE);
    char* pchar = new char[num1];
    WideCharToMultiByte(CP_OEMCP, NULL, search_wch, -1, pchar, num1, NULL, FALSE);

    myself.add_interest(pchar);
}

