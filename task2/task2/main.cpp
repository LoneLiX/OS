#include<iostream>
using namespace std;
const int max_space = 128;
class FreeSpace
{
public:
	int ID;//分区号
	int address;//地址
	int space;//长度
	bool state;//是否占用
};
class FreeList 
{
public:
	FreeSpace node;
	FreeList* prior;
	FreeList* next;
};
FreeList* head = new(FreeList), * tail = new(FreeList);
void initList()
{
	head->prior = NULL;
	head->next = tail;
	head->node.space = 0;
	head->node.state = 1;
	tail->prior = head;
	tail->next = NULL;
	tail->node.address = 0;
	tail->node.ID = 10000;//空闲的块默认id为10000
	tail->node.space = max_space;
	tail->node.state = 0;
}
bool first_fit(int id, int length)
{
	FreeList* search = head->next;
	FreeList* freeNode = new(FreeList);
	freeNode->node.ID = id;
	freeNode->node.space = length;
	freeNode->node.state = 1;
	while (search) {
		if (search->node.space >= length && search->node.state == 0) {
			if (search->node.space == length) {
				search->node.ID = id;
				search->node.state = 1;
				delete(freeNode);
				return true;
			}
			else if (search->node.space > length) {
				freeNode->node.address = search->node.address;
				search->node.address += length;
				search->node.space -= length;
				search->prior->next = freeNode;
				freeNode->next = search;
				freeNode->prior = search->prior;
				search->prior = freeNode;
				return true;
			}
		}
		search = search->next;
	}
	delete(freeNode);
	return false;
}
void showFreeList()
{
	FreeList* search = head->next;
	cout << "------------内存布局情况--------------" << endl;
	while (search)
	{
		if (search->node.ID == 10000) {
			cout << "分区未分配" << endl;
			cout << "起始地址：" << search->node.address << endl;
			cout << "分区长度：" << search->node.space << endl;
			if (search->node.state)
				cout << "分区状态：占用" << endl;
			else
				cout << "分区状态：空闲" << endl;
			cout << "--------------------------------" << endl;
		}
		else {
			cout << "分区号：" << search->node.ID << endl;
			cout << "起始地址：" << search->node.address << endl;
			cout << "分区长度：" << search->node.space << endl;
			if (search->node.state)
				cout << "分区状态：占用" << endl;
			else
				cout << "分区状态：空闲" << endl;
			cout << "--------------------------------" << endl;
		}
		search = search->next;
	}
}
bool alloc()
{
	int id, length;
	cout << "请输入作业编号：";
	cin >> id;
	if (id >= 10000) {
		cout << "超过ID上限，请重新输入" << endl;
		return false;
	}
	cout << "请输入作业所需空间大小：";
	cin >> length;
	if (length <= 0) {
		cout << "无效作业空间，请重新输入" << endl;
		return false;
	}
	if (first_fit(id, length)) {
		cout << "分配成功" << endl;
		showFreeList();
		return true;
	}
	else {
		cout << "分配失败" << endl;
		return false;
	}
}

void release()
{
	int id;
	FreeList* search = head->next;
	cout << "请输入释放的作业编号：";
	cin >> id;
	while (search) {
		if (search->node.ID == id) {
			search->node.ID = 10000;
			search->node.state = 0;
			if (search->prior->node.state == 0){
				search->prior->node.space += search->node.space;
				search->prior->next = search->next;
				search->next->prior = search->prior;
				FreeList* temp = search->prior;
				if (temp->next->node.state == 0) {
					temp->node.space += temp->next->node.space;
					if (temp->next->next == NULL){
						temp->next = search->next->next;
					}
					else {
					temp->next->next->prior = temp;
					temp->next = temp->next->next;
					}
				}
			}
			else if (search->next->node.state == 0){
				search->node.space += search->next->node.space;
				if (search->next->next == NULL){
					search->next = search->next->next;
				}
				else {
					search->next->next->prior = search;
					search->next = search->next->next;
				}

			}
			break;
		}
		search = search->next;
	}
	showFreeList();
}

int main()
{
	initList();
	showFreeList();
	int select;
	while (1) {
		cout << "请输入操作数以继续操作：1.分配空间 2.释放空间" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			alloc();
			break;
		case 2:
			release();
			break;
		default:
			cout << "请输入正确操作数" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}

