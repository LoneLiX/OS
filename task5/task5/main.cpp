#include<iostream>
using namespace std;
int available[100] = { 0 };
int max[100][100] = { 0 };
int allocation[100][100] = { 0 }; 
int need[100][100] = { 0 }; 
int request[100] = { 0 };
//安全性算法所需向量
int work[100] = { 0 };
bool finish[100] = { false };

int resInUse = 0;//已经定义的资源数量
int processNum = 0;//已经声明的进程数量
const int maxRes = 100;//最大定义资源数量
const int maxProcess = 100;//最大声明进程数量
int listCount;
string resName[100];//资源名
string processName[100];//进程名
string safeList[100];//安全队列


//函数声明
void showRes();//显示当前资源情况
void showProcess();
void systemRes();
void createProcess();
bool compareWorkNeed(int needLine[100], int workTemp[100]);//辅助比较work和need的函数
bool checkSafeList(bool finishTemp[100]);//辅助检查是否所有进程都finish的函数
int searchProcess(string name);//辅助查找进程的函数
bool safe(int availableTemp[100], int allocationTemp[100][100], int needTemp[100][100]);//安全性算法
bool allocate();
void showAllocateList();

void showProcess() {
	if (processNum == 0) {
		cout << "当前系统无进程" << endl;
	}
	else {
		cout << "当前系统共有：" << processNum << "个进程,分别是：" << endl;
		for (int i = 0; i < processNum; i++) {
			cout << processName[i]<< "\t" ;//mark一下 可能需要改输出格式!
		}
		cout << endl;
	}
	cout << "------------------------------------------" << endl;

}
void showRes() {
	if(resInUse == 0){
		cout << "当前系统无资源，请声明" << endl;
	}
	else {
		cout << "当前系统共有：" << resInUse << "种资源,分别是：" << endl;
		for (int i = 0; i < resInUse; i++) {
			cout  << resName[i]<< "\t";//mark一下 可能需要改输出格式!
		}
		cout << endl;
		for (int i = 0; i < resInUse; i++) {
			cout  << available[i]<< "\t";//mark一下 可能需要改输出格式!
		}
		cout << endl;
	}
	cout << "------------------------------------------" << endl;
}

void systemRes() {
	cout << "请输入系统中存在的资源数量:";
	cin >> resInUse;
	cout << endl;
	if (resInUse > maxRes) {
		cout << "超过系统允许存在的最大资源数量，请重新输入" << endl;
		return;
	}
	for (int i = 0; i < resInUse; i++) {
		cout << "请输入资源" << i + 1 << "的名称:";
		cin >> resName[i];
		cout << endl;
		cout << "请输入资源" << resName[i] << "的数量：";
		cin >> available[i];
		cout << endl;
	}
	cout << "系统资源定义完毕" << endl;
	cout << "------------------------------------------" << endl;
}

void createProcess() {
	int alloc = 0;
	cout << "请输入请求资源的进程数：";
	cin >> processNum;
	cout << endl;
	if (processNum > maxProcess) {
		cout << "超过系统允许存在的最大进程数量，请重新输入" << endl;
		return;
	}
	//先输入所有进程名
	for (int i = 0; i < processNum; i++) {
		cout << "请输入进程"<<i+1<<"的名字：";
		cin >> processName[i];
		cout << endl;
	}
	//定义max矩阵
	for (int i = 0; i < processNum; i++) {
		cout << "请输入进程" << processName[i] << "对各类资源的最大需求" << endl;
		for (int j = 0; j < resInUse; j++) {
			cout << resName[j] << "：";
			cin >> alloc;
			if (alloc > available[j]) {
				cout << "超过系统拥有此类资源的上限，申请失败" << endl;
				return;
			}
			max[i][j] = alloc;
			cout << endl;
		}
	}
	//初始未分配资源，need矩阵=max矩阵
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
bool safe(int availableTemp[100],int allocationTemp[100][100], int needTemp[100][100]) {//三个参数为尝试分配后的矩阵情况
	int needLine[100]; //获取当前进程的need情况
	listCount = 0;
	for (int i = 0; i < resInUse; i++) {
		work[i] = availableTemp[i];//初始化work向量
	}
	for (int i = 0; i < processNum; i++) {
		finish[i] = false;//初始化finish向量
	}
	for (int i = 0; i < processNum; i++) {//寻找能够完成的进程
		for (int j = 0; j < resInUse; j++) {
			needLine[j] = need[i][j];
		}
		if (finish[i] == false&&compareWorkNeed(needLine,work)) {//如果满足finish为false并且need小于work
			finish[i] = true;//修改finish为true
			for(int j = 0; j<resInUse;j++){
				work[j] += allocationTemp[i][j];
			}
			safeList[listCount] = processName[i];//将已经完成的进程放入安全队列
			listCount++;
		}
	}
	if (checkSafeList(finish)) {
		/*cout << "安全,此次分配成功" << endl;
		cout << "存在安全序列为：";
		for (int i = 0; i < processNum; i++) {
			cout << safeList[i] << " ";
		}
		cout << "------------------------------------------" << endl;*/
		return true;
	}
	else {
		/*cout << "分配失败，不存在安全序列" << endl;
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
	//试分配时的临时矩阵
	bool alloc = true;
	int availableTemp[100] = { 0 };
	int allocationTemp[100][100] = { 0 };
	int needTemp[100][100] = { 0 };
	cout << "请输入需要分配资源的进程名：";
	cin >> p_name;
	int processCount = searchProcess(p_name);
	if (processCount == 10000) {
		cout << "不存在此进程" << endl;
		return false;
	}
	cout << "查找到该进程" << endl;
	cout << "请输入为该进程分配的各类资源数量：" << endl;
	for (int i = 0; i < resInUse; i++) {
		cout << resName[i] << "：";
		cin >> request[i];
		if (request[i] > need[processCount][i] || request[i] > available[i]) {
			cout << "资源数量超过数量上限" << endl;
			for (int j = 0; j <= i; j++) {
				request[j] = 0;//重置request向量
			}
			return false;
		}
	}
	cout << "请求合法，进行试分配，执行安全性算法" << endl;//运行到这一行说明request没有问题,开始进行试分配;
	//试分配修改数据结构
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
		cout << "安全,此次分配成功,已分配" << endl;
		cout << "存在安全序列为：";
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
		cout << "分配失败，不存在安全序列,拒绝本次分配请求" << endl;
		cout << "------------------------------------------" << endl;
		showAllocateList();
		return false;
	}

}

void showAllocateList() {
	showRes();
	showProcess();
	cout << "\tMax矩阵\t" << endl;
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
	cout << "\tAllocation矩阵\t" << endl;
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
	cout << "\tNeed矩阵\t" << endl;
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
	cout << "\tavailable向量\t" << endl;
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
	cout << "请分配系统资源" << endl;
	systemRes();
	cout << "请声明进程信息" << endl;
	createProcess();
	showAllocateList();
	while (!exit) {
		cout << "请输入对应操作数以进行操作：1.为进程分配资源 2.退出" << endl;
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
			cout << "请输入正确操作数" << endl;
			break;
		}
	}
}
	


