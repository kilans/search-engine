#include"���ʱ��_��ʱ����.h"
#include"��ҳ�ļ�.h"
class Inverter_node
{
public:
	Inverter_node()
	{
		this->next = NULL;
	}
	Inverter_node(int cod)
	{
		this->next = NULL;
		this->net_id = cod;
	};
	int net_id;									//��Ӧ��ҳ
	
	Inverter_node* next;											//��¼ID
};
class Inverter_index										//ģ������
{
public:
	Inverter_index()
	{
		this->head = new Inverter_node(0);
		this->net_count = 0;
	}
	Inverter_node * head;
	pair<string, int>order;
	int net_count;
};
void Creat_Index();