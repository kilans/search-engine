#include"网页文件.h"
bool NetList::insert(string name,int row)
{
	NetNode* temp = new NetNode (name,row);
	temp->net_id = ++this->num;
	this->rear->next = temp;
	this->rear = temp;
	temp->next = NULL;
	return 1;
}
void NetList::init(string filename)
{
	fstream* file = new fstream;
	int i, count=0, count2 = 0, term_id;
	char c;
	file->open(filename, ios::in);
	cout <<"提取文件中..."<< endl;
	while (!file->eof())
	{
		string temp;
		getline(*file, temp);
		count++;
		if (temp[0] == 'h' && temp[1] == 't' && temp[2] == 't' && temp[3] == 'p')
		{
			this->insert(temp, count);
			count2++;
			
			continue;
		}	
	}	
	file->close();
	NetNode* temp = this->head->next;
	file->open("网页文件.txt",ios::out);
	*file << this->num << endl;
	for(int i=0;i<this->num;i++)
	{
		*file << temp->net_row;
		*file << temp->domain_title;
		*file << temp->net_id<< endl;
		temp = temp->next;
	}

	system("cls");
	cout << "提取完毕！" << endl;
	file->close();
	return;

}