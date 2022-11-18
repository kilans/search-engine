#pragma once
#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include"单词编号_临时索引.h"
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
	
	Word* wordsrear;				//搜查序列
	Word* wordshead;
	ifstream file;
	Word_List* word_list;
	int  dictionary_count;
	int* dictionary;			//词典索引
	unsigned long long int* wordcount;				//倒排索引单词对应网页数目,用于计算偏移地址
	int* net_count;
	int* net;					//打印
	int net_total;				//网页总数
	int word_count;				//分词个数
	unsigned int* ptr;			//网页地址
	queue<int>*sort_bucket;
	queue<pair<pair<int,int>,int>>key;		//映射码
	void Words_Analyse();		//分析表
	void Search_Word();
	void Search_Net();
	void Net_Sort();
	void Search_Link();
	void Search_Main();
	


};