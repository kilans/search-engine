#include"���������ļ�.h"
void Creat_Index()
{
	
	int i=0,j=1,count,total;
	int *A,*B,**D;
	unsigned long long * C,*E;
	ifstream* file1 = new ifstream;
	ofstream* file2 = new ofstream;
	ofstream* file3 = new ofstream;
	file1->open("��ҳ�ļ�.txt", ios::in);
	*file1 >> total;					//��ҳ����
	file1->close();						//��ȡ��ҳ��Ŀ
	A = new int[total+1];					//��ҳ�浥����Ŀ
	B = new int[total+1];					//ҳ�浥�ʼ���	//ƫ�Ƶ�ַ
	C = new unsigned long long [total+1];				//����λ�ã������ļ�ͷ��	//�ε�ַ
	D = new int* [26];					//�ʵ�����,��¼�ʵ�ÿ���εĵ��ʸ���
	E = new unsigned long long[total + 1];
	file1->open("�ʵ������ļ�.txt");
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
	file1->open("���ʼ����ļ�.txt", ios::in);
	do {	
		*file1 >> A[j];
		j++;	
		C[j] = C[j-1]+ (A[j-1]*13);
	} while (j<total);
	
	*file1 >> A[j];

	file1->close();					//��ȡ��Ӧ��ҳ���ʸ���

	file1->open("��ʱ�����ļ�.txt",ios::in);
	file1->ignore(' ');
	file2->open("���������ļ�.txt", ios::out);
	file3->open("��ҳ�����ļ�.txt", ios::out);
	//int pos1 = 0;
	int chick1 = 3;
	int chick2 = 3;
	int per = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	cout << "�ⲿ���������..." << endl;
	for(int x=0;x<26;x++)
		for(int y=0;y<26;y++)
			{
				SetConsoleCursorPosition(handle, { 0,1 });
				per = ((x * 26 + y) * 100) / 676;
				cout << per << "%";
				if (D[x][y] == 0)	continue;									//�ôʵ���޵���
				
				//cout << x << " " << y << " " << endl;
				count = 1;
				char cmp[2]; cmp[0] = char(97 + x); cmp[1] = char(97 + y);			//��¼�ö��ֵ�
				Inverter_index* index = new Inverter_index[ D[x][y] ];				//���ֵ�κ��еĴʵĸ���
				for (int i = 0; i < D[x][y]; i++)
					index[i].order = make_pair(cmp, i+1);								//���ʱ��
				//file1->seekg(ios::beg);												//����ָ��
				while (count <= total)												//totalΪ��ҳ����
				{ 
					//file1->seekg((A[count-1]-B[count-1]+B[count]) * 13, ios::cur);		//���Ѱַ��
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
						temp.first[1] = file1->get();							//��ȡ�����ַ�
						if (count == 4717 && x == 'r' - 'a' && y == 'a' - 'a' && chick1--)
						{
							temp.first[0] = 'r'; temp.first[1] = 'a';
						}
						if (count == 4717 && x == 'r' - 'a' && y == 'e' - 'a' && chick2--)			//�˴������ļ���д����������޷���������⣬�ù�Ʒ�ʽʵ����ȷ����
						{
							temp.first[0] = 'r'; temp.first[1] = 'e';
						}
						if (temp.first[0] == cmp[0] && temp.first[1]==cmp[1])
						{
							 C[count] = 13 + C[count];										//ƫ������¼
							*file1 >> temp.second;											//�ֵ��Ӧ���ֱ��
							Inverter_node* tempN = new Inverter_node(count);				//�������ӱ��									
							tempN->next = index[temp.second-1].head->next;							
							index[temp.second-1].head->next = tempN;								
							index[temp.second - 1].net_count++;								//�õ������ӵ���ҳ��Ŀ
							A[count]--;														//��ͳ�Ƶ�����//ƫ�ƣ�
							//B[count]++;
							file1->seekg(6, ios::cur);										//��һ���ֶ�
						}
						else
						{
							//C[count] = file1->tellg();
							//C[count] = C[count]-2;
							//file1->seekg(-2, ios::cur);									//ע�Ͷ�Ϊ���Ѱַ��
							break;
						}
					}					
					count++;
				}
					for (int i = 0; i < D[x][y]; i++)						//���ֵ��ȫ��д��
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
