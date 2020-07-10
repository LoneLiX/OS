#include<iostream>
#include<string>
using namespace std;

/*typedef struct Lnode
{
	string p_name = "";//进程名
	char state = 'R';//状态
	int priority = 0;//优先级
	int time = 0;//要求时间
	struct Lnode* next = NULL;//下一个节点
}PCBNode;*/
class PCBNode {
public:
	string p_name = "";//进程名
	char state = 'R';//状态
	int priority = 0;//优先级
	int time = 0;//要求时间
	PCBNode* next = NULL;//下一个节点
};
void CreatePCBList(PCBNode*& pcbList, int n)//带头结点
{
	PCBNode* newPCB,* last;
	//pcbList = (PCBNode*)malloc(sizeof(PCBNode));
	pcbList = new(PCBNode);
	last = pcbList;
	for (int i = 0; i < n; i++) {
		newPCB = new(PCBNode);
		newPCB->p_name = "P" + to_string(i);
		newPCB->state = 'R';
		cout << "请输入"<<newPCB->p_name<<"进程优先级"<<endl;
		cin >> newPCB->priority;
		
		cout <<"请输入该进程要求运行时间"<<endl;
		cin >> newPCB->time;
		last->next = newPCB;
		last = newPCB;
	}
	last->next = NULL;
}

int lenList(PCBNode* pcbList)//输出链表长度
{
	if (pcbList->next== NULL)
		return 0;
	PCBNode* p = pcbList->next;
	int len = 0;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}
void printList(PCBNode* pcbList) {
	if (pcbList->next == NULL)
		return;
	PCBNode* p = pcbList->next;
	cout << "正在运行中：" << p->p_name << endl;
	cout << "就绪队列为:";
	while (p != NULL)
	{
		cout << p->p_name;
		p = p->next;
	}
	cout << endl;
}

void sortList(PCBNode*& pcbList)//排序
{
	int len = lenList(pcbList);
	//cout << "len:" << len << endl;//调试用
	if (len == 0) {
		return;
	}
	PCBNode* p = pcbList->next;
	for (int i = 0; i < len - 1; i++)
	{
		p = pcbList->next;
		for (int j = 0; j < len - i - 1; j++)
		{
			if (p->priority < p->next->priority)
			{
				string tmpName = p->p_name;
				char tmpState = p->state;
				int tmpPriority = p->priority;
				int tmpTime = p->time;
				p->p_name = p->next->p_name;
				p->state = p->next->state;
				p->priority = p->next->priority;
				p->time = p->next->time;
				p->next->p_name = tmpName;
				p->next->state = tmpState;
				p->next->priority = tmpPriority;
				p->next->time = tmpTime;
			}
			p = p->next;
		}
	}
}

void Start(PCBNode*& readyList, PCBNode*& endList)
{
	while (readyList->next!= NULL) {
		sortList(readyList);
		PCBNode* Running = readyList->next;
		if (Running->time != 0) {
			if (Running->priority != 0) {
				Running->priority--;
				Running->time--;
			}
			else {
				Running->time--;
			}
			printList(readyList);
		}
		else {
			Running->state = 'E';
			endList->next = Running;
			readyList->next = Running->next;
			delete(Running);

		}
		
		
	}
}

int main() {
	PCBNode* readyList;
	PCBNode* endList = new(PCBNode);
	int pcbNum;
	cout << "请输入创建的进程数" << endl;
	cin >> pcbNum;
	CreatePCBList(readyList, pcbNum);
	Start(readyList, endList);
	system("pause");
	return 0;
}
