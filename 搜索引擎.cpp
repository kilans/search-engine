#include"搜索引擎.h"
Search_Engine::Search_Engine()
{
	system("cls");
	cout << "加载中..." << endl;
	
	this->net_total = 0;
	this->word_count = 0;
	this->wordshead = new Word();
	this->wordsrear = this->wordshead;
	this->word_list = new Word_List;
	int i = 0;
	file.open("网页文件.txt",ios::in);
	file >> this->net_total;
	this->net = new int[this->net_total]{ 0 };				//用于网页权重计数
	file.close();

	this->file.open("网页寻址文件.txt", ios::in);
	ptr = new unsigned int[this->net_total]{ 0 };
	for (int i = 0; i < this->net_total; i++)
	{
		file >> ptr[i];
	}
	file.close();

	this->dictionary = new int[26];					//26*26;
	file.open("词典索引文件.txt", ios::in);
	file >> this->dictionary_count;						//总单词数目	
	this->dictionary = new int[676];
	this->dictionary[0] = 0;
	int test = 0;
	for (int j = 1; j < 676; j++)
	{
			file.get();
			file >> this->dictionary[j];
			this->dictionary[j] += this->dictionary[j - 1];
	}
	file.close();
	i = 0;
	file.open("网页计数文件.txt", ios::in);
	this->wordcount = new unsigned long long int[this->dictionary_count];	//
	this->net_count = new int[this->dictionary_count];
	this->wordcount[0] = 0;
	while (i < this->dictionary_count)			//倒排索引的地址位置计算
	{
		//cout << i << " " << this->wordcount[i] << endl;
		file >> this->net_count[i];
		i++;
		this->wordcount[i] = this->wordcount[i-1] + this->net_count[i-1]*5 + 9;				//网页数*5+数字编号(5)+换行符+字典段	
		//this->wordcount[i] = this->wordcount[i-1]+(this->wordcount[i]*5 + 3);			
		file.get();
		
		//system("pause");

	}
	file.close();
	
	file.open("单词编号文件.txt", ios::in);
	//file.ignore(' ');
	i = 0;
	while(i<this->dictionary_count)
	{
		pair<string, int> order;
		string word1;
		order.first.push_back(file.get());
		order.first.push_back(file.get());
		file >> order.second;
		file >> word1;
		i++;
		//cout << order.first << order.second << " " << word1 << endl;
		file.get();
		this->word_list->insert(order, word1);
		/*int A[2] = { 0 };
		A[0] = word1[0] - 97;
		if (word1[1]) A[1] = word1[1] - 97;
		cout << this->word_list->search(word1,A)->word << endl;
		cout << word1 << endl;
		
		system("pause");*/
	}
	//
	//for(int i=0;i<26;i++)
	//	for (int j = 0; j < 26; j++)
	//	{
	//		Word_Node* tempN = this->word_list->head[i][j]->next;
	//		while (tempN)
	//		{
	//			cout << tempN->cod.first << " "<<tempN->cod.second << " " << tempN->word << endl;
	//			tempN = tempN->left;
	//		}
	//	}

	

	file.close();

	cout << "欢迎使用！" << endl;
}
void Search_Engine::Words_Analyse()
{
	string temp;
	string sun;
	char c;
	getline(cin, temp);
	int i = 0;
	Word* word = NULL;	
	while (i <= temp.size())
	{
		c = temp[i];
		if (!sun.empty() && (c == ' ' || c == ',' || c == '-' || i==temp.size()))		//string非空
		{
			word = new Word(sun);
			this->wordsrear->next = word;
			this->wordsrear = word;					//尾插法
			this->word_count++;						//搜查序列的单词数量
			//cout << word->word << endl;
			sun.resize(0);
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 39)
		{
			if (c != 39)
			{
				c |= 0B00100000;		//小写化
				sun.push_back(c);
			}
			else if (!sun.empty())	sun.push_back(c);			//防止首位单引号、
		}
		i++;
	}
	return;
}
void Search_Engine::Search_Word()
{
	
	int* A;
	//unsigned long long int find;
	Word* tempW = this->wordshead->next;												//查询序列首
	Word_Node* tempN = NULL;
	while (tempW)
	{
		A = new int[2]{ 0 };
		for (int i = 0; i < tempW->word.size() && i < 2; i++)
			if (tempW->word[i] <= 'z' && tempW->word[i] >= 'a')	A[i] = tempW->word[i] - 97;	//截取索引码  	
		Word_Node* tempN = this->word_list->search(tempW->word,A);							//访问哈希树，查找词语
		//cout << tempN->word << endl;
		if (tempN->word == tempW->word)												//得到映射码	
		{ 
			key.push(make_pair(make_pair(A[0],A[1]), tempN->cod.second));
		}		
		tempW = tempW->next;
	}
	this->word_count = key.size();								//重置有效分词个数	
	/*system("pause");
	while (!this->key.empty())
	{
		cout << key.front().first.first <<" "<<key.back().first.second << endl;
		key.pop();
	}
	system("pause");*/
	
	return;

}
void Search_Engine::Search_Net()
{
	this->file.open("倒排索引文件.txt", ios::in);
	pair<pair<int,int>, int> temp;
	long long int dic;
	int i,j,order;
	//cout << key.size() << endl;
	//system("pause");
	while(!this->key.empty())
	{
		i = 0;
		temp = this->key.front();
		this->key.pop();
		//cout << temp.first.first<<" "<< temp.first.second <<" "<< temp.second << endl;
		j = (temp.first.first) * 26 + (temp.first.second);
		dic= this->dictionary[j];												//该字典段所在行
		j = dic+temp.second-1;
		dic = this->wordcount[dic+temp.second-1];								//精确字节位；
		file.seekg(dic+7, ios::beg);											//越过编码段
		while (i < this->net_count[j])
		{
			file >> order;
			this->net[order-1]++;				//0~total-1的编号统计
			//cout << order << " ";
			i++;
		}
		//cout << endl;
	}

	/*for (int i = 0; i < this->net_total; i++)
	{
		if(this->net[i]==2)cout <<i+1<<" "<< this->net[i] << endl;
	}*/

	file.close();
	return;
}
void Search_Engine::Net_Sort()
{
	
	cout << this->word_count << endl;
	this->sort_bucket = new queue<int>[this->word_count];				//有效分词个数，预示着最大网页计数
	for (int i = 0; i < this->net_total; i++)
	{
		if (!this->net[i])	continue;
		this->sort_bucket[this->net[i] - 1].push(i);						//桶的标号代表网页权重-1，桶内int值+1代表网页编号
	}	
	//
	//for (int i = 0; i < this->word_count; i++)
	//{
	//	while (!this->sort_bucket[i].empty())
	//	{
	//		cout << this->sort_bucket[i].front() << " ";
	//		this->sort_bucket[i].pop();
	//	}
	//	system("pause");
	//	cout << endl;
	//}
	//for (int i = templ; i <=low; i++)
	//{
	//	cout << this->net[i]<<" ";
	//}
	//cout << endl;
	
	//for (int i = low; i <= temph; i++)
	//{
	//	cout << this->net[i] << " ";
	//}
	//cout << endl;
	//system("pause");
	return;
}
void Search_Engine::Search_Link()
{
	int tar;
	string temp;
	file.open("网页文件.txt", ios::in);
	for (int i = this->word_count-1; i>=0; i--)
	{
		while (!this->sort_bucket[i].empty())
		{
			tar=this->sort_bucket[i].front();		//目标网页
			file.seekg(ptr[tar], ios::beg);			//
			getline(file, temp,',');				//截取网页链接
			//cout <<i+1<<" "<< temp << endl;
			this->sort_bucket[i].pop();
		}
		system("pause");
	}
	file.close();
	return;
}
void Search_Engine::Search_Main()
{
	this->Words_Analyse();			//分词
	this->Search_Word();			//通过分词，查找单词表，得到映射码
	if (this->key.empty())			//没有查找到相关词语;
	{
		cout << "无搜索匹配！" << endl;
		system("pause");
		return;
	}
	this->Search_Net();				//通过映射码，进入倒排索引查找对应网页
	this->Net_Sort();				//网页计数排序;
	this->Search_Link();			//查找链接;
	return;
}