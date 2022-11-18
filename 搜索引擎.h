#pragma once
#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include"���ʱ��_��ʱ����.h"
using namespace std;
class Word
{
public:
	Word()
	{
		this->next = NULL;
		this->nets = NULL;
	}
	Word(string A)
	{
		this->word = A;
		this->next = NULL;
		this->nets = NULL;
		
	}
	string word;
	Word* next;
	int* nets;
};
class Search_Engine
{
public:
	Search_Engine();
	
	Word* wordsrear;				//�Ѳ�����
	Word* wordshead;
	ifstream file;
	Word_List* word_list;
	int  dictionary_count;
	int* dictionary;			//�ʵ�����
	unsigned long long int* wordcount;				//�����������ʶ�Ӧ��ҳ��Ŀ,���ڼ���ƫ�Ƶ�ַ
	int* net_count;
	int* net;					//��ӡ
	int net_total;				//��ҳ����
	int word_count;				//�ִʸ���
	unsigned int* ptr;			//��ҳ��ַ
	queue<int>*sort_bucket;
	queue<pair<pair<int,int>,int>>key;		//ӳ����
	void Words_Analyse();		//������
	void Search_Word();
	void Search_Net();
	void Net_Sort();
	void Search_Link();
	void Search_Main();
	


};