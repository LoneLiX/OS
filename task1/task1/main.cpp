#include<iostream>
#include<string>
using namespace std;

/*typedef struct Lnode
{
	string p_name = "";//������
	char state = 'R';//״̬
	int priority = 0;//���ȼ�
	int time = 0;//Ҫ��ʱ��
	struct Lnode* next = NULL;//��һ���ڵ�
}PCBNode;*/
class PCBNode {
public:
	string p_name = "";//������
	char state = 'R';//״̬
	int priority = 0;//���ȼ�
	int time = 0;//Ҫ��ʱ��
	PCBNode* next = NULL;//��һ���ڵ�
};
void CreatePCBList(PCBNode*& pcbList, int n)//��ͷ���
{
	PCBNode* newPCB,* last;
	//pcbList = (PCBNode*)malloc(sizeof(PCBNode));
	pcbList = new(PCBNode);
	last = pcbList;
	for (int i = 0; i < n; i++) {
		newPCB = new(PCBNode);
		newPCB->p_name = "P" + to_string(i);
		newPCB->state = 'R';
		cout << "������"<<newPCB->p_name<<"�������ȼ�"<<endl;
		cin >> newPCB->priority;
		
		cout <<"������ý���Ҫ������ʱ��"<<endl;
		cin >> newPCB->time;
		last->next = newPCB;
		last = newPCB;
	}
	last->next = NULL;
}

int lenList(PCBNode* pcbList)//���������
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
	cout << "���������У�" << p->p_name << endl;
	cout << "��������Ϊ:";
	while (p != NULL)
	{
		cout << p->p_name;
		p = p->next;
	}
	cout << endl;
}

void sortList(PCBNode*& pcbList)//����
{
	int len = lenList(pcbList);
	//cout << "len:" << len << endl;//������
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
	cout << "�����봴���Ľ�����" << endl;
	cin >> pcbNum;
	CreatePCBList(readyList, pcbNum);
	Start(readyList, endList);
	system("pause");
	return 0;
}
