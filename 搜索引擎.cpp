#include"��������.h"
Search_Engine::Search_Engine()
{
	system("cls");
	cout << "������..." << endl;
	
	this->net_total = 0;
	this->word_count = 0;
	this->wordshead = new Word();
	this->wordsrear = this->wordshead;
	this->word_list = new Word_List;
	int i = 0;
	file.open("��ҳ�ļ�.txt",ios::in);
	file >> this->net_total;
	this->net = new int[this->net_total]{ 0 };				//������ҳȨ�ؼ���
	file.close();

	this->file.open("��ҳѰַ�ļ�.txt", ios::in);
	ptr = new unsigned int[this->net_total]{ 0 };
	for (int i = 0; i < this->net_total; i++)
	{
		file >> ptr[i];
	}
	file.close();

	this->dictionary = new int[26];					//26*26;
	file.open("�ʵ������ļ�.txt", ios::in);
	file >> this->dictionary_count;						//�ܵ�����Ŀ	
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
	file.open("��ҳ�����ļ�.txt", ios::in);
	this->wordcount = new unsigned long long int[this->dictionary_count];	//
	this->net_count = new int[this->dictionary_count];
	this->wordcount[0] = 0;
	while (i < this->dictionary_count)			//���������ĵ�ַλ�ü���
	{
		//cout << i << " " << this->wordcount[i] << endl;
		file >> this->net_count[i];
		i++;
		this->wordcount[i] = this->wordcount[i-1] + this->net_count[i-1]*5 + 9;				//��ҳ��*5+���ֱ��(5)+���з�+�ֵ��	
		//this->wordcount[i] = this->wordcount[i-1]+(this->wordcount[i]*5 + 3);			
		file.get();
		
		//system("pause");

	}
	file.close();
	
	file.open("���ʱ���ļ�.txt", ios::in);
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

	cout << "��ӭʹ�ã�" << endl;
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
		if (!sun.empty() && (c == ' ' || c == ',' || c == '-' || i==temp.size()))		//string�ǿ�
		{
			word = new Word(sun);
			this->wordsrear->next = word;
			this->wordsrear = word;					//β�巨
			this->word_count++;						//�Ѳ����еĵ�������
			//cout << word->word << endl;
			sun.resize(0);
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 39)
		{
			if (c != 39)
			{
				c |= 0B00100000;		//Сд��
				sun.push_back(c);
			}
			else if (!sun.empty())	sun.push_back(c);			//��ֹ��λ�����š�
		}
		i++;
	}
	return;
}
void Search_Engine::Search_Word()
{
	
	int* A;
	//unsigned long long int find;
	Word* tempW = this->wordshead->next;												//��ѯ������
	Word_Node* tempN = NULL;
	while (tempW)
	{
		A = new int[2]{ 0 };
		for (int i = 0; i < tempW->word.size() && i < 2; i++)
			if (tempW->word[i] <= 'z' && tempW->word[i] >= 'a')	A[i] = tempW->word[i] - 97;	//��ȡ������  	
		Word_Node* tempN = this->word_list->search(tempW->word,A);							//���ʹ�ϣ�������Ҵ���
		//cout << tempN->word << endl;
		if (tempN->word == tempW->word)												//�õ�ӳ����	
		{ 
			key.push(make_pair(make_pair(A[0],A[1]), tempN->cod.second));
		}		
		tempW = tempW->next;
	}
	this->word_count = key.size();								//������Ч�ִʸ���	
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
	this->file.open("���������ļ�.txt", ios::in);
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
		dic= this->dictionary[j];												//���ֵ��������
		j = dic+temp.second-1;
		dic = this->wordcount[dic+temp.second-1];								//��ȷ�ֽ�λ��
		file.seekg(dic+7, ios::beg);											//Խ�������
		while (i < this->net_count[j])
		{
			file >> order;
			this->net[order-1]++;				//0~total-1�ı��ͳ��
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
	this->sort_bucket = new queue<int>[this->word_count];				//��Ч�ִʸ�����Ԥʾ�������ҳ����
	for (int i = 0; i < this->net_total; i++)
	{
		if (!this->net[i])	continue;
		this->sort_bucket[this->net[i] - 1].push(i);						//Ͱ�ı�Ŵ�����ҳȨ��-1��Ͱ��intֵ+1������ҳ���
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
	file.open("��ҳ�ļ�.txt", ios::in);
	for (int i = this->word_count-1; i>=0; i--)
	{
		while (!this->sort_bucket[i].empty())
		{
			tar=this->sort_bucket[i].front();		//Ŀ����ҳ
			file.seekg(ptr[tar], ios::beg);			//
			getline(file, temp,',');				//��ȡ��ҳ����
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
	this->Words_Analyse();			//�ִ�
	this->Search_Word();			//ͨ���ִʣ����ҵ��ʱ��õ�ӳ����
	if (this->key.empty())			//û�в��ҵ���ش���;
	{
		cout << "������ƥ�䣡" << endl;
		system("pause");
		return;
	}
	this->Search_Net();				//ͨ��ӳ���룬���뵹���������Ҷ�Ӧ��ҳ
	this->Net_Sort();				//��ҳ��������;
	this->Search_Link();			//��������;
	return;
}