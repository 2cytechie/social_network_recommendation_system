#pragma once
#include<string>
#include<vector>

class Tree {
	// ������
private:
	std::string data;
	std::vector<Tree*> children;

	// ���ķ���	1��������    2������    3�����    4��ɾ��    5������

public:
	Tree() {

	}

	~Tree(){}

	void find(std::string data);
	void insert(std::string data);
	void remove(std::string data);

};