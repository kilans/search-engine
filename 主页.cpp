
#include"��ҳ�ļ�.h"
#include"���������ļ�.h"
#include"��������.h"
#include <chrono>
int main()
{
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();//��ʱ��


    string filename1 = "news.csv";
    string filename2 = "��ҳ�ļ�.txt";
    NetList* netlist = new NetList;
    netlist->init(filename1);                                         //��ҳ�ļ���ȡ
    delete netlist;
    Word_List* word_list = new Word_List;
    Index* index = new Index;
    read_csv(filename1,filename2,word_list, index);                   //���ʱ���ļ�_��ʱ�����ļ�
    Creat_Index();                                                    //���������ļ�����
    /*
            ������Ϊ�ļ�������̣���һ��ʹ����Ҫ�����ļ�
    */
    Search_Engine *search_engine = new Search_Engine;                 //���������ļ�����֮�󣬿���ֱ�ӽ�������������ع���
    search_engine->Search_Main();
    delete search_engine;


    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    cout << "run time = " << time_used.count() << " seconds. " << endl;
    return 0;
}
