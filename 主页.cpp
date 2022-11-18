
#include"网页文件.h"
#include"倒排索引文件.h"
#include"搜索引擎.h"
#include <chrono>
int main()
{
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();//计时器


    string filename1 = "news.csv";
    string filename2 = "网页文件.txt";
    NetList* netlist = new NetList;
    netlist->init(filename1);                                         //网页文件获取
    delete netlist;
    Word_List* word_list = new Word_List;
    Index* index = new Index;
    read_csv(filename1,filename2,word_list, index);                   //单词编号文件_临时索引文件
    Creat_Index();                                                    //倒排索引文件创立
    /*
            上述均为文件创造过程，第一次使用需要解析文件
    */
    Search_Engine *search_engine = new Search_Engine;                 //有了上述文件生成之后，可以直接进入搜索引擎加载构造
    search_engine->Search_Main();
    delete search_engine;


    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    cout << "run time = " << time_used.count() << " seconds. " << endl;
    return 0;
}
