#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <graphics.h>
#include <vector>

#include "button.h"
#include "people.h"

#include <iostream>

const int MAX_ID_LEN = 8;                   // id��󳤶�
const int MAX_BUTTON_SIZE = 9;              // ����ʾ����󳤶�
const int ERROR_ID = 10000000;
extern People myself;

inline std::vector<std::string> get_interests(std::string id) {
    std::ifstream file("SocialMediaUsersDataset.csv");
    if (file.is_open()) {
        // �洢��ͷ��Ϣ
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;
        // ������ͷ����ȡ����
        while (std::getline(ssHeader, headerCell, ',')) {
            headers.push_back(headerCell);
        }

        int idx = -1;
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == "Interests") {
                idx = i;
                break;
            }
        }

        if (idx != -1) {
            std::string line;
            // �洢��ȡ��column������
            std::vector<std::string> data;
            int id_height = std::stoi(id) - 10000000;
            while (std::getline(file, line)) {
                id_height--;
                if (id_height == 0) {
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
            return data;
        }

        file.close();
    }
}

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
inline std::vector<Button*> search_friends(wchar_t* search_wch,bool is_id_search) {
    // ת������
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

    // �����ļ���ƥ����û�
    std::vector<Button*> search_friends_list;

    std::ifstream file("SocialMediaUsersDataset.csv");
    if (file.is_open()) {
        // �洢��ͷ��Ϣ
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;

        // ������ͷ����ȡ����
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
        idx = is_id_search ? id_idx : name_idx;

        if (idx != -1) {
            int max_button_size = MAX_BUTTON_SIZE;
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string cell;

                if (line.find(search_str) != std::string::npos) {
                    int currentColumnIndex = 0;

                    // �����ָ�����
                    std::vector<std::string> data;

                    while (std::getline(ss, cell, ',')) {
                        // �Ȱ�ID����
                        data.push_back(cell);
                        if (currentColumnIndex == idx) {
                            if (is_id_search) {
                                cell = std::to_string(std::stoi(cell) + ERROR_ID);
                            }

                            while (std::getline(ss, cell, ',')) {
                                data.push_back(cell);
                            }

                            Button* search_friend = new Button();
                            std::string button_data = std::to_string(std::stoi(data[id_idx]) + ERROR_ID) + "    " + data[name_idx];
                            search_friend->set_button_type(Button::TextType::left);
                            search_friend->set_data(button_data);
                            search_friends_list.push_back(search_friend);
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

// ��Ҫ��Button�е�data���и�ֵ
inline std::vector<Button*> is_friend(std::vector<Button*> search_friends_list) {
    const LPCTSTR add_str = _T("��Ӻ���");
    const LPCTSTR is_add_str = _T("�����");

    std::vector<Button*> button_is_friend;
    std::vector<std::string> friend_id_list = myself.get_friends();
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

inline std::vector<Button*> recommendations_friends() {
    std::vector<Button*> recommendations_friends_list;

    std::ifstream file("SocialMediaUsersDataset.csv");

    if (file.is_open()) {
        // �洢��ͷ��Ϣ
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;

        // ������ͷ����ȡ����
        while (std::getline(ssHeader, headerCell, ',')) {
            headers.push_back(headerCell);
        }

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

        size_t i = 0;
        while (std::getline(file, line)) {
            i++;
            std::cout << i << std::endl;

            // �洢��ȡ��column������
            std::vector<std::string> interestsdata;

            int start_idx = line.find('\"');
            int end_idx = line.find_last_of('\"');
            std::string interests_data = line.substr(start_idx, end_idx - start_idx);
            std::stringstream ss(interests_data);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                interestsdata.push_back(cell.substr(2, cell.size() - 3));
            }

            // �����ȡ����Ȥ���ݲ�����otherInter��
            Interests otherInter;
            for (const auto& inter : interestsdata) {
                otherInter.add_interest(inter);
            }

            if (similar(myself.get_interests(), otherInter) > 0.01) {
                // �����ָ�����
                std::vector<std::string> data;

                std::stringstream ss(line);
                std::string cell;
                while (std::getline(ss, cell, ',')) {
                    data.push_back(cell);
                }

                std::string button_data = std::to_string(std::stoi(data[id_idx]) + ERROR_ID) + "    " + data[name_idx];

                Button* recommendations_friend = new Button();
                recommendations_friend->set_data(button_data);
                recommendations_friend->set_button_type(Button::TextType::left);

                recommendations_friends_list.push_back(recommendations_friend);

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
        // �洢��ͷ��Ϣ
        std::vector<std::string> headers;

        std::string firstLine;
        std::getline(file, firstLine);

        std::stringstream ssHeader(firstLine);
        std::string headerCell;

        // ������ͷ����ȡ����
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

            // �������������
            int idx = std::stoi(myself.get_friends()[i]) - ERROR_ID;
            std::string line;

            while (std::getline(datafile, line) && idx > 0) {
                idx--;
            }

            // �����ָ�����
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
    //LPCTSTR ת���� char *
    int num1 = WideCharToMultiByte(CP_OEMCP, NULL, search_wch, -1, NULL, 0, NULL, FALSE);
    char* pchar = new char[num1];
    WideCharToMultiByte(CP_OEMCP, NULL, search_wch, -1, pchar, num1, NULL, FALSE);

    myself.add_interest(pchar);
}

