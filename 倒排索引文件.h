#include"单词编号_临时索引.h"
#include"网页文件.h"
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
	int net_id;									//对应网页
	
	Inverter_node* next;											//记录ID
};
class Inverter_index										//模糊索引
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