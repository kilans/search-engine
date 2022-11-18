#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include<iomanip>
#include<queue>
#include<stdlib.h>
using namespace std;
class Word_Node
{
public:
    Word_Node()
    {
        this->next = NULL;
        this->pre = NULL;
        this->count = 0;
        this->cur_id = 0;
        this->left = NULL;
        this->right = NULL;
    }
    Word_Node(int sun[3], string word, pair<string, int >cod)
    {
        this->word = word;
        this->cod = cod;
    }
    Word_Node(int sun[3],string word,int id)
    {
        this->word = word;
        this->cur_id = id;
        for (int i = 0; i < 2; i++)
            this->cod.first.push_back(sun[i] + 97);
    }
    Word_Node* next;
    Word_Node* left;
    Word_Node* right;
    Word_Node* pre;
    string word;
    pair<string,int >cod;

    int count;          //出现的次数
    int cur_id;         //当前对应的网页页面
};
class Word_List
{
public:
    Word_List()
    {
        this->head = new Word_Node  **[26];
        for (int i = 0; i < 26; i++)
        {
            this->head[i] = new Word_Node  *[26];
            for (int j = 0; j < 26; j++)
            {
                this->head[i][j] = new Word_Node ;
                /*for (int k = 0; k < 26; k++)
                    this->head[i][j][k] = new Word_Node;*/

            }
        }
        this->num = 0;
    }
    Word_Node*** head;         //二阶字典，
    pair<int, pair<string, int>> insert(string, int,int *);
    bool insert(pair<string, int>,string);
    Word_Node* search(string, int*);
    int num;
};
class Index_Node
{
public:
    Index_Node()
    {
        this->next = NULL;
        this->doc_id = 0;
    }
    Index_Node( pair<string, int> word_order ,int b)
    {
        this->word_order = word_order;
        this->doc_id = b;
        this->next = NULL;
    }
    pair<string, int> word_order;
    int doc_id;
    Index_Node* next;
};
class Index //索引
{
public:
    Index()
    {
        this->head = new Index_Node;
        this->rear = NULL;
        this->count = 0;
    }
    Index_Node* head;
    Index_Node* rear;
    int *wordcount;
    int count;              //索引数目
    bool insert(pair<string ,int >, int);
};
void read_csv(string, string, Word_List*, Index* &);
void sort_partion(queue <pair<string,int>> *, int,ofstream**);