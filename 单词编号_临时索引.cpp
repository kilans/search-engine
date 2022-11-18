#include"单词编号_临时索引.h"
using namespace std;

void bian(Word_Node* temp)
{
    if (!temp)return;
    bian(temp->left);
    cout << temp->word << endl;
    bian(temp->right);
}
void read_csv(string filename, string page, Word_List* word_list, Index* &index)
{
    system("cls");
    fstream* file = new fstream;
    ofstream* ofile = new ofstream;
    ofstream* ofile2 = new ofstream;
    ofstream* ofile3 = new ofstream;
    ofstream* ofile4 = new ofstream;
    Word_Node *WN = NULL;
    queue<pair<string, int>> bucket[26];
    string htemp;
    int i = 0, count = 0, count2 = 1, perc,k;
    pair<int,pair<string,int>>term_id;
    char c;
    file->open(page, ios::in);
    *file >> i;             //记录页面数
    k = i;
    int* A = new int[i];            //记录各页面对应行
    index->wordcount = new int[i+1];  //记录各页面对应单词数
    ofile4->open("网页寻址文件.txt",ios::out);
    unsigned int ptr;
    while (count < i)
    {
        index->wordcount[count] = 0;
        *file >> A[count];
        ptr = file->tellg();
        *ofile4 << ptr<<" ";
        //ofile4->write((char*)&ptr,sizeof ptr);
        getline(*file, htemp);
        count++;
    }
    //index->wordcount[count+1] = 0;
    file->close();
    ofile4->close();
    file->open(filename, ios::in);
    ofile->open("临时索引文件.txt", ios::out | ios::binary);
    ofile2->open("单词编号文件.txt", ios::out);
    ofile3->open("单词计数文件.txt", ios::out);
    count = 0;
    cout << "单词编号文件生成中..." << endl;
    cout << "临时索引文件生成中..." << endl;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    while ((c = file->get()) != EOF)
    {

        string temp;
        if (count2 == A[count])                 //count2是行数，count是网页数
        {
            getline(*file, temp);  
            sort_partion(bucket, count, &ofile);
            count++;                            //换页
            count2++;
            SetConsoleCursorPosition(handle, { 0,2 });
            perc = (count * 100) / i;
            cout << perc << "%";
            continue;
        }
        string node;
        if (c == '\n')                          //换行
        {
            count2++;
            continue;
        }
        while ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 39 )
        {
            if (c != 39)
            {
                c = c | 0B00100000;                     //存储为小写
                node.push_back(c);
            }  
            else if (node.length()) node.push_back(c);          //排除首位单引号
            c = file->get();
        }
        if (node.empty())               continue;                               //不是单词
        int sun[2] = {0};
        for (int i = 0; i < node.length() && i < 2; i++)
        {
            if (node[i] >= 'a' && node[i] <= 'z')   sun[i] = node[i] - 97;    //判断属于字母 
        }                                                                       //给予编号
        term_id = word_list->insert(node, count,sun);       //返回该词的id
        if (!term_id.second.second)            continue;                          //返回0则是已经生成过临时索引且插入过词表
        index->count++;                                                         //记录索引数目
        index->wordcount[count-1]++;                                              //对应页面单词数目+1
        //index->insert(term_id.second, count);                                   //内存中插入临时索引 O(1)
        /*cout << sun[2] << endl;*/
        bucket[sun[1]].push((term_id.second));    
                                                                                  //第三位入桶；
        //*ofile << term_id.second.first<<term_id.second.second << " " << count << endl;                           //临时索引文件
        if (term_id.first)  *ofile2 << term_id.second.first<<term_id.second.second << " " << node << endl;          //单词编号稳健
       /* cout << node << endl;*/
    }
    sort_partion(bucket, count, &ofile);
    for (int i = 0; i < k; i++)              
        *ofile3 << index->wordcount[i]<< endl;
    ofile->close();
    file->close();
    ofile2->close();
    ofile3->close();
    ofile->open("词典索引文件.txt");
    int t = 0;
    *ofile << word_list->num << endl;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            {
                *ofile<< word_list->head[i][j]->count <<endl;
            }
    ofile->close();

    sort_partion(bucket, count, &ofile);
    SetConsoleCursorPosition(handle, { 0,2 });
    cout << "生成完毕！" << endl;
    
}
pair<int, pair<string,int>> Word_List::insert(string node, int count2,int sun[2])
{
    
    Word_Node* temp = this->search(node, sun);                          //该单词已存在
    if (temp->word == node)                                 
    {
        temp->count++;
        if (temp->cur_id != count2)                         //未生成索引
        {
            temp->cur_id = count2;
            return make_pair(0, temp->cod);
        }
        return make_pair(0,make_pair(" ",0));             //生成索引，返回其编号
    }
    Word_Node* tempNode = new Word_Node(sun,node,count2);
    tempNode->cod.second = ++this->head[sun[0]][sun[1]]->count;             //该索引目录下的单词个数
    this->num++;                                                            //总词数
    //tempNode->word = node;
    //tempNode->cur_id = count2;
    if (temp == this->head[sun[0]][sun[1]]) temp->next = tempNode;          //头结点插入
    else
    {
        if (node.length() < temp->word.length()) temp->left = tempNode;
        else temp->right = tempNode;
    }
    return make_pair(1, tempNode->cod);
}
Word_Node* Word_List::search(string node, int sun[2])
{

    Word_Node* pre = this->head[sun[0]][sun[1]];
    Word_Node* temp = pre->next;
    while (temp)
    {
        if (temp->word == node) return temp;  
        pre = temp;
        if (temp->word.length() > node.length())    temp = temp->left;
        else  temp = temp->right;
    }
    return pre;
}
bool Index::insert(pair<string,int> word_id,int doc_id)
{
    Index_Node* temp = new Index_Node(word_id, doc_id);
    temp->next = this->head->next;
    this->head->next = temp;
    this->count++;
    return 1;
}
void sort_partion(queue <pair<string, int>> bucket[26] , int net_id, ofstream** file)
{
    queue<pair<string,int>> temp;
    //system("pause");
    int a = 0;
    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < 26; i++)                                //出桶
        {
            while (!bucket[i].empty())
            {
                temp.push(bucket[i].front());
                //a++;
                //cout << bucket[i].front().first << endl;;
                bucket[i].pop();
            }

        }
        if (k == 1) break;
        for (int i = 0; i < 26; i++)
        {
            while (!temp.empty())                                       //入桶
            {
                bucket[temp.front().first[0-k] - 97].push(temp.front());                //进入第a个桶
                temp.pop();
            }
        }
    }

    while(!temp.empty())
    {
        //temps.word_order = temp.front();

        /*(*file)->write((char*)(&temp.front().first[0]), 1);
        (*file)->write((char*)(&temp.front().first[1]), 1);
        (*file)->write((char*)(&temp.front().first[2]), 1);
        (*file)->write((char*)(&temp.front().second), 4);
        (*file)->write((char*)(&net_id), 4);*/
       ////(*file)->write(" ", 1);       
       /* (*file)->write("\n", 1);*/   
        **file << temp.front().first << setw(5) << temp.front().second <<" "<< setw(4) << net_id << endl;
        temp.pop();
    }
    return;
}
bool Word_List::insert(pair<string, int> order, string word)
{
    int sun[2] = { 0 };
    for (int i = 0; i < order.first.length() && i < 2; i++)
    {
        if (order.first[i] >= 'a' && order.first[i] <= 'z')   sun[i] = order.first[i] - 97;    //判断属于字母 
    }

   //cout << order.first << order.second << " " << word << endl;
   //system("pause");
    Word_Node *temp = this->search(order.first,sun);
    Word_Node* newN = new Word_Node(sun, word, order);
    //cout << newN->cod.first << endl;
    //system("pause");
    if (temp == this->head[sun[0]][sun[1]]) temp->next = newN;          //头结点插入
    else
    {
        if (order.first.length() < temp->word.length()) temp->left = newN;
        else temp->right = newN;
    }
    return 1;

}