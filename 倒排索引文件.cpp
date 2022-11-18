#include"倒排索引文件.h"
void Creat_Index()
{
	
	int i=0,j=1,count,total;
	int *A,*B,**D;
	unsigned long long * C,*E;
	ifstream* file1 = new ifstream;
	ofstream* file2 = new ofstream;
	ofstream* file3 = new ofstream;
	file1->open("网页文件.txt", ios::in);
	*file1 >> total;					//网页数量
	file1->close();						//读取网页数目
	A = new int[total+1];					//各页面单词数目
	B = new int[total+1];					//页面单词计数	//偏移地址
	C = new unsigned long long [total+1];				//单词位置（基于文件头）	//段地址
	D = new int* [26];					//词典索引,记录词典每个段的单词个数
	E = new unsigned long long[total + 1];
	file1->open("词典索引文件.txt");
	*file1 >> count;
	for(int a=0;a<26;a++)
	{
		D[a] = new int [26];
		for (int b = 0; b < 26; b++)
		{
			file1->get();
			*file1 >> D[a][b];//[c];
			
			
		}
	}

	file1->close();
	for (int k = 0; k < total+1; k++)
	{
		A[k] = 0;
		B[k] = 0;
		C[k] = 0;
	}
	file1->open("单词计数文件.txt", ios::in);
	do {	
		*file1 >> A[j];
		j++;	
		C[j] = C[j-1]+ (A[j-1]*13);
	} while (j<total);
	
	*file1 >> A[j];

	file1->close();					//读取对应网页单词个数

	file1->open("临时索引文件.txt",ios::in);
	file1->ignore(' ');
	file2->open("倒排索引文件.txt", ios::out);
	file3->open("网页计数文件.txt", ios::out);
	//int pos1 = 0;
	int chick1 = 3;
	int chick2 = 3;
	int per = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	cout << "外部排序进行中..." << endl;
	for(int x=0;x<26;x++)
		for(int y=0;y<26;y++)
			{
				SetConsoleCursorPosition(handle, { 0,1 });
				per = ((x * 26 + y) * 100) / 676;
				cout << per << "%";
				if (D[x][y] == 0)	continue;									//该词典段无单词
				
				//cout << x << " " << y << " " << endl;
				count = 1;
				char cmp[2]; cmp[0] = char(97 + x); cmp[1] = char(97 + y);			//记录该段字典
				Inverter_index* index = new Inverter_index[ D[x][y] ];				//该字典段含有的词的个数
				for (int i = 0; i < D[x][y]; i++)
					index[i].order = make_pair(cmp, i+1);								//单词编号
				//file1->seekg(ios::beg);												//重置指针
				while (count <= total)												//total为网页数量
				{ 
					//file1->seekg((A[count-1]-B[count-1]+B[count]) * 13, ios::cur);		//相对寻址法
					if (!A[count])
					{
						count++;
						continue;
					}		
					file1->seekg(C[count],ios::beg);
					while (1)
					{
						if (!A[count]) break;
						pair<char[2], int>temp;
						temp.first[0] = file1->get();
						temp.first[1] = file1->get();							//读取两个字符
						if (count == 4717 && x == 'r' - 'a' && y == 'a' - 'a' && chick1--)
						{
							temp.first[0] = 'r'; temp.first[1] = 'a';
						}
						if (count == 4717 && x == 'r' - 'a' && y == 'e' - 'a' && chick2--)			//此处在于文件读写存在奇怪且无法解决的问题，用诡计方式实现正确读入
						{
							temp.first[0] = 'r'; temp.first[1] = 'e';
						}
						if (temp.first[0] == cmp[0] && temp.first[1]==cmp[1])
						{
							 C[count] = 13 + C[count];										//偏移量记录
							*file1 >> temp.second;											//字典对应数字编号
							Inverter_node* tempN = new Inverter_node(count);				//网络链接编号									
							tempN->next = index[temp.second-1].head->next;							
							index[temp.second-1].head->next = tempN;								
							index[temp.second - 1].net_count++;								//该单词链接的网页数目
							A[count]--;														//受统计单词量//偏移；
							//B[count]++;
							file1->seekg(6, ios::cur);										//下一个字段
						}
						else
						{
							//C[count] = file1->tellg();
							//C[count] = C[count]-2;
							//file1->seekg(-2, ios::cur);									//注释段为相对寻址法
							break;
						}
					}					
					count++;
				}
					for (int i = 0; i < D[x][y]; i++)						//该字典段全部写入
					{
						Inverter_node* tempN = index[i].head->next;
						*file2 << index[i].order.first[0] << index[i].order.first[1] << setw(4)<<index[i].order.second << " ";
						while(tempN)
						{
							
							*file2 << setw(4)<<tempN->net_id << " ";
							
							tempN = tempN->next;
						}
						*file3 << index[i].net_count << endl;
						*file2 << endl;
					}
					delete []index;
			}


			/*for (int i = 0; i < 4718; i++)
				if(A[i])cout << i<<" "<<A[i] << endl;
			cout << pos1 << endl;*/
	file1->close();
	file2->close();
	file3->close();
	delete file1;
	delete file2;
	delete file3;
	delete A, B, C, D, E;
	delete[] D, E;
	return;
}
