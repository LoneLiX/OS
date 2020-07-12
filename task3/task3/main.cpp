#include<iostream>
using namespace std;
int bitMap[8][8];//λʾͼ 8*2*4 = 64
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
//��ʼ��ͷβ�ڵ�
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
//��ʼ��λʾͼ
void initBitMap() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			bitMap[i][j] = 0;
}
//�ж�λʾͼ�п��п�������Ƿ������������
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
//�����Ƿ���ĳ��ID���ļ�
FileIndex*searchFile(int id) {
	FileIndex* search = head->next;
	if (id < 0 || id >= 10000) {
		cout << "��������ȷID" << endl;
		return NULL;
	}

	while (search) {
		if (search->node.ID == id) {
			//cout << "�ҵ�IDΪ" << id << "���ļ�" << endl;
			return search;
		}
		search = search->next;
	}
	cout << "δ�ҵ�IDΪ" << id << "���ļ�" << endl;
	return NULL;
}
bool idLegal(int id) {
	FileIndex* search = head->next;
	if (id >= 10000 || id < 0) {
		cout << "��ЧID" << endl;
		return false;
	}
	else {
		while (search) {
			if (search->node.ID == id) {
				cout << "ID�ѱ�ռ��" << endl;
				return false;
			}
			search = search->next;
		}
		return true;
	}
}
void assign() {
	int id, request;
	cout << "�������ļ�ID��";
	cin >> id;
	if(!idLegal(id)){
		//cout << "��ЧID" << endl;
		return;
	}
	cout << "�������ļ���С��";
	cin >> request;
	if (request <= 0 || request > 64) {
		cout << "��Ч�ļ���С" << endl;
		return;
	}
	else if (!searchFreeSpace(request)){
		cout << "ʣ��ռ䲻��" << endl;
		return;
	}
	else {
		cout << "----------------------------------------------" << endl;
		cout << "����ɹ�" << endl;
		cout << "����������ַΪ��" << endl;
		cout << "�����\t" << "�ŵ���\t" << "�����¼��" << endl;
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
		newFile->next = head->next;//���ļ�����Ŀ¼
		head->next->prior = newFile;
		newFile->prior = head;
		head->next = newFile;
	}
	show();
}
void release() {
	int id;
	cout << "��������Ҫɾ�����ļ�ID��";
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
	cout << "-----------------��ǰ���̴洢�ļ�-----------------" << endl;
	while (search) {
		if (search->node.ID == 10000) {
			break;
			//cout << "��ǰ�������ļ�" << endl;
			//cout << "------------------------------------------" << endl;
		}
		else {
			cout << "�ļ�IDΪ��" << search->node.ID << endl;
			cout << "�ļ���СΪ��" << search->node.size << endl;
			cout << "------------------------------------------" << endl;
		}
		search = search->next;
	}
	cout << "-----------------λʾͼ-----------------" << endl;
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
		cout << "�������Ӧ����Բ�����1.����ռ� 2.�ͷſռ� 3.�˳�" << endl;
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
			cout << "��������ȷ������" << endl;
			break;
		}
	}
}
