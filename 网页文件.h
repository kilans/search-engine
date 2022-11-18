#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class NetNode
{
public:
	NetNode()
	{
		this->net_id = 0;
		this->net_row = 0;
		this->next = NULL;
	}
	NetNode(string A, int B)
	{
		this->domain_title = A;
		this->net_row = B;
	}
	int net_id;
	int net_row;
	string domain_title;
	NetNode* next;
};
class NetList
{
public:
	NetList()
	{
		this->num = 0;
		this->head = new NetNode();
		this->rear = this->head;
	}
	int num;
	NetNode *rear;
	NetNode* head;
	void init(string);
	bool insert(string,int);
};
