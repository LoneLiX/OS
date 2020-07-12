#include<iostream>
using namespace std;
int available[100] = { 0 };
int max[100][100] = { 0 };
int allocation[100][100] = { 0 }; 
int need[100][100] = { 0 }; 
int request[100] = { 0 };
//��ȫ���㷨��������
int work[100] = { 0 };
bool finish[100] = { false };

int resInUse = 0;//�Ѿ��������Դ����
int processNum = 0;//�Ѿ������Ľ�������
const int maxRes = 100;//�������Դ����
const int maxProcess = 100;//���������������
int listCount;
string resName[100];//��Դ��
string processName[100];//������
string safeList[100];//��ȫ����


//��������
void showRes();//��ʾ��ǰ��Դ���
void showProcess();
void systemRes();
void createProcess();
bool compareWorkNeed(int needLine[100], int workTemp[100]);//�����Ƚ�work��need�ĺ���
bool checkSafeList(bool finishTemp[100]);//��������Ƿ����н��̶�finish�ĺ���
int searchProcess(string name);//�������ҽ��̵ĺ���
bool safe(int availableTemp[100], int allocationTemp[100][100], int needTemp[100][100]);//��ȫ���㷨
bool allocate();
void showAllocateList();

void showProcess() {
	if (processNum == 0) {
		cout << "��ǰϵͳ�޽���" << endl;
	}
	else {
		cout << "��ǰϵͳ���У�" << processNum << "������,�ֱ��ǣ�" << endl;
		for (int i = 0; i < processNum; i++) {
			cout << processName[i]<< "\t" ;//markһ�� ������Ҫ�������ʽ!
		}
		cout << endl;
	}
	cout << "------------------------------------------" << endl;

}
void showRes() {
	if(resInUse == 0){
		cout << "��ǰϵͳ����Դ��������" << endl;
	}
	else {
		cout << "��ǰϵͳ���У�" << resInUse << "����Դ,�ֱ��ǣ�" << endl;
		for (int i = 0; i < resInUse; i++) {
			cout  << resName[i]<< "\t";//markһ�� ������Ҫ�������ʽ!
		}
		cout << endl;
		for (int i = 0; i < resInUse; i++) {
			cout  << available[i]<< "\t";//markһ�� ������Ҫ�������ʽ!
		}
		cout << endl;
	}
	cout << "------------------------------------------" << endl;
}

void systemRes() {
	cout << "������ϵͳ�д��ڵ���Դ����:";
	cin >> resInUse;
	cout << endl;
	if (resInUse > maxRes) {
		cout << "����ϵͳ������ڵ������Դ����������������" << endl;
		return;
	}
	for (int i = 0; i < resInUse; i++) {
		cout << "��������Դ" << i + 1 << "������:";
		cin >> resName[i];
		cout << endl;
		cout << "��������Դ" << resName[i] << "��������";
		cin >> available[i];
		cout << endl;
	}
	cout << "ϵͳ��Դ�������" << endl;
	cout << "------------------------------------------" << endl;
}

void createProcess() {
	int alloc = 0;
	cout << "������������Դ�Ľ�������";
	cin >> processNum;
	cout << endl;
	if (processNum > maxProcess) {
		cout << "����ϵͳ������ڵ�����������������������" << endl;
		return;
	}
	//���������н�����
	for (int i = 0; i < processNum; i++) {
		cout << "���������"<<i+1<<"�����֣�";
		cin >> processName[i];
		cout << endl;
	}
	//����max����
	for (int i = 0; i < processNum; i++) {
		cout << "���������" << processName[i] << "�Ը�����Դ���������" << endl;
		for (int j = 0; j < resInUse; j++) {
			cout << resName[j] << "��";
			cin >> alloc;
			if (alloc > available[j]) {
				cout << "����ϵͳӵ�д�����Դ�����ޣ�����ʧ��" << endl;
				return;
			}
			max[i][j] = alloc;
			cout << endl;
		}
	}
	//��ʼδ������Դ��need����=max����
	for (int i = 0; i < processNum; i++) {
		for (int j = 0; j < resInUse; j++) {
			need[i][j] = max[i][j];
			}
	}
}
bool compareWorkNeed(int needLine[100],int workTemp[100]) {
	for (int i = 0; i < resInUse; i++) {
		if (needLine[i] > workTemp[i]) {
			return false;
		}
	}
	return true;
}
bool checkSafeList(bool finishTemp[100]) {
	for (int i = 0; i < processNum; i++) {
		if (finishTemp[i] == false) {
			return false;
		}
	}
	return true;
}
bool safe(int availableTemp[100],int allocationTemp[100][100], int needTemp[100][100]) {//��������Ϊ���Է����ľ������
	int needLine[100]; //��ȡ��ǰ���̵�need���
	listCount = 0;
	for (int i = 0; i < resInUse; i++) {
		work[i] = availableTemp[i];//��ʼ��work����
	}
	for (int i = 0; i < processNum; i++) {
		finish[i] = false;//��ʼ��finish����
	}
	for (int i = 0; i < processNum; i++) {//Ѱ���ܹ���ɵĽ���
		for (int j = 0; j < resInUse; j++) {
			needLine[j] = need[i][j];
		}
		if (finish[i] == false&&compareWorkNeed(needLine,work)) {//�������finishΪfalse����needС��work
			finish[i] = true;//�޸�finishΪtrue
			for(int j = 0; j<resInUse;j++){
				work[j] += allocationTemp[i][j];
			}
			safeList[listCount] = processName[i];//���Ѿ���ɵĽ��̷��밲ȫ����
			listCount++;
		}
	}
	if (checkSafeList(finish)) {
		/*cout << "��ȫ,�˴η���ɹ�" << endl;
		cout << "���ڰ�ȫ����Ϊ��";
		for (int i = 0; i < processNum; i++) {
			cout << safeList[i] << " ";
		}
		cout << "------------------------------------------" << endl;*/
		return true;
	}
	else {
		/*cout << "����ʧ�ܣ������ڰ�ȫ����" << endl;
		cout << "------------------------------------------" << endl;*/
		return false;
	}
}
int searchProcess(string name) {
	for (int i = 0; i < processNum; i++) {
		if (name == processName[i])
			return i;
	}
	return 10000;
}

bool allocate() {
	string p_name;
	//�Է���ʱ����ʱ����
	bool alloc = true;
	int availableTemp[100] = { 0 };
	int allocationTemp[100][100] = { 0 };
	int needTemp[100][100] = { 0 };
	cout << "��������Ҫ������Դ�Ľ�������";
	cin >> p_name;
	int processCount = searchProcess(p_name);
	if (processCount == 10000) {
		cout << "�����ڴ˽���" << endl;
		return false;
	}
	cout << "���ҵ��ý���" << endl;
	cout << "������Ϊ�ý��̷���ĸ�����Դ������" << endl;
	for (int i = 0; i < resInUse; i++) {
		cout << resName[i] << "��";
		cin >> request[i];
		if (request[i] > need[processCount][i] || request[i] > available[i]) {
			cout << "��Դ����������������" << endl;
			for (int j = 0; j <= i; j++) {
				request[j] = 0;//����request����
			}
			return false;
		}
	}
	cout << "����Ϸ��������Է��䣬ִ�а�ȫ���㷨" << endl;//���е���һ��˵��requestû������,��ʼ�����Է���;
	//�Է����޸����ݽṹ
	for (int i = 0; i < resInUse; i++) {
		availableTemp[i] = available[i] - request[i];
	}
	for (int i = 0; i < processNum; i++) {
		for (int j = 0; j < resInUse; j++) {
			allocationTemp[i][j] = allocation[i][j];
			needTemp[i][j] = need[i][j];
		}
	}
	for (int i = 0; i < resInUse; i++) {
		allocationTemp[processCount][i] += request[i];
		needTemp[processCount][i] -= request[i];
	}
	if (safe(availableTemp, allocationTemp, needTemp)) {
		cout << "��ȫ,�˴η���ɹ�,�ѷ���" << endl;
		cout << "���ڰ�ȫ����Ϊ��";
		for (int i = 0; i < processNum; i++) {
			cout << safeList[i] << " ";
		}
		cout << "------------------------------------------" << endl;
		for (int i = 0; i < resInUse; i++) {
			available[i] = availableTemp[i];
		}
		for (int i = 0; i < processNum; i++) {
			for (int j = 0; j < resInUse; j++) {
				allocation[i][j] = allocationTemp[i][j];
				need[i][j] = needTemp[i][j];
			}
		}
		showAllocateList();
		return true;
	}
	else {
		cout << "����ʧ�ܣ������ڰ�ȫ����,�ܾ����η�������" << endl;
		cout << "------------------------------------------" << endl;
		showAllocateList();
		return false;
	}

}

void showAllocateList() {
	showRes();
	showProcess();
	cout << "\tMax����\t" << endl;
	cout << "\t";
	for (int i = 0; i < resInUse; i++) {
		cout << resName[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < processNum; i++) {
		cout << processName[i] << "\t";
		for (int j = 0; j < resInUse; j++) {
			cout << max[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "\tAllocation����\t" << endl;
	cout << "\t";
	for (int i = 0; i < resInUse; i++) {
		cout << resName[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < processNum; i++) {
		cout << processName[i] << "\t";
		for (int j = 0; j < resInUse; j++) {
			cout << allocation[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "\tNeed����\t" << endl;
	cout << "\t";
	for (int i = 0; i < resInUse; i++) {
		cout << resName[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < processNum; i++) {
		cout << processName[i] << "\t";
		for (int j = 0; j < resInUse; j++) {
			cout << need[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "\tavailable����\t" << endl;
	cout << "\t";
	for (int i = 0; i < resInUse; i++) {
		cout << resName[i] << "\t";
	}
	cout << endl;
	cout << "\t";
	for (int i = 0; i < resInUse; i++) {
		cout << available[i] << "\t";
	}
	cout << endl;
	cout << "------------------------------------------" << endl;

}
int main() {
	int select;
	bool exit = false;
	cout << "�����ϵͳ��Դ" << endl;
	systemRes();
	cout << "������������Ϣ" << endl;
	createProcess();
	showAllocateList();
	while (!exit) {
		cout << "�������Ӧ�������Խ��в�����1.Ϊ���̷�����Դ 2.�˳�" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			allocate();
			break;
		case 2:
			exit = true;
			break;
		default:
			cout << "��������ȷ������" << endl;
			break;
		}
	}
}
	


