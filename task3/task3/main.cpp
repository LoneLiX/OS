#include<iostream>
using namespace std;
int bitMap[8][8];//位示图 8*2*4 = 64
class File
{
public:
	int ID;
	int size;
	int alloc[8][8] = { 0 };
};
class FileIndex
{
public:
	File node;
	FileIndex* prior;
	FileIndex* next;
};
FileIndex* head = new(FileIndex);
FileIndex* last = new(FileIndex);
void show();
//初始化头尾节点
void initFileIndex() {
	head->node.ID = 10000;
	head->node.size = 0;
	head->prior = NULL;
	head->next = last;
	last->node.ID = 10000;
	last->node.size = 0;
	last->prior = head;
	last->next = NULL;
}
//初始化位示图
void initBitMap() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			bitMap[i][j] = 0;
}
//判断位示图中空闲块的数量是否大于申请数量
bool searchFreeSpace(int size) {
	int freeSpace = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (bitMap[i][j] == 0) {
				freeSpace++;
			}
		}
	}
	if (freeSpace >= size) {
		return true;
	}
	else
		return false;
}
//查找是否有某个ID的文件
FileIndex*searchFile(int id) {
	FileIndex* search = head->next;
	if (id < 0 || id >= 10000) {
		cout << "请输入正确ID" << endl;
		return NULL;
	}

	while (search) {
		if (search->node.ID == id) {
			//cout << "找到ID为" << id << "的文件" << endl;
			return search;
		}
		search = search->next;
	}
	cout << "未找到ID为" << id << "的文件" << endl;
	return NULL;
}
bool idLegal(int id) {
	FileIndex* search = head->next;
	if (id >= 10000 || id < 0) {
		cout << "无效ID" << endl;
		return false;
	}
	else {
		while (search) {
			if (search->node.ID == id) {
				cout << "ID已被占用" << endl;
				return false;
			}
			search = search->next;
		}
		return true;
	}
}
void assign() {
	int id, request;
	cout << "请输入文件ID：";
	cin >> id;
	if(!idLegal(id)){
		//cout << "无效ID" << endl;
		return;
	}
	cout << "请输入文件大小：";
	cin >> request;
	if (request <= 0 || request > 64) {
		cout << "无效文件大小" << endl;
		return;
	}
	else if (!searchFreeSpace(request)){
		cout << "剩余空间不足" << endl;
		return;
	}
	else {
		cout << "----------------------------------------------" << endl;
		cout << "申请成功" << endl;
		cout << "分配的物理地址为：" << endl;
		cout << "柱面号\t" << "磁道号\t" << "物理记录号" << endl;
		FileIndex* newFile = new(FileIndex);
		newFile->node.ID = id;
		newFile->node.size = request;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (request <= 0) {
					break;
				}
				if (bitMap[i][j] == 0) {
					bitMap[i][j] = 1;
					newFile->node.alloc[i][j] = 1;
					cout << i << "\t" << j / 4 << "\t" << j % 4 << endl;
					request--;
				}
			}
		}
		newFile->next = head->next;//将文件插入目录
		head->next->prior = newFile;
		newFile->prior = head;
		head->next = newFile;
	}
	show();
}
void release() {
	int id;
	cout << "请输入想要删除的文件ID：";
	cin >> id;
	if (searchFile(id) == NULL) {
		return;
	}
	else {
		FileIndex* releaseFile = searchFile(id);
		releaseFile->node.size = 0;
		releaseFile->node.ID = 10000;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (releaseFile->node.alloc[i][j] == 1) {
					bitMap[i][j] = 0;
				}
			}
		}
		releaseFile->next->prior = releaseFile->prior;
		releaseFile->prior->next = releaseFile->next;
		delete(releaseFile);
	}
	show();
}

void show() {
	FileIndex* search = head->next;
	cout << "-----------------当前磁盘存储文件-----------------" << endl;
	while (search) {
		if (search->node.ID == 10000) {
			break;
			//cout << "当前磁盘无文件" << endl;
			//cout << "------------------------------------------" << endl;
		}
		else {
			cout << "文件ID为：" << search->node.ID << endl;
			cout << "文件大小为：" << search->node.size << endl;
			cout << "------------------------------------------" << endl;
		}
		search = search->next;
	}
	cout << "-----------------位示图-----------------" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << bitMap[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
}
int main()
{
	initFileIndex();
	initBitMap();
	int select;
	while (1) {
		//show();
		cout << "请输入对应编号以操作：1.分配空间 2.释放空间 3.退出" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			assign();
			break;
		case 2:
			release();
			break;
		case 3:
			break;
		default:
			cout << "请输入正确操作数" << endl;
			break;
		}
	}
}
