//ref url:https://docs.microsoft.com/zh-cn/windows/win32/api/tcpmib/ns-tcpmib-_mib_tcptable
#define _CRT_SECURE_NO_WARNINGS //关闭不安全函数报警或错误提示
#pragma warning(disable:4996)；
// Need to link with Iphlpapi.lib and Ws2_32.lib

#include <iostream>
#include "getportinfo.h"  //getTcpPortInfo()  getUdpPortInfo()
#include <fstream>

#include <time.h> 
using std::cout;
using std::endl;
using std::set;
using std::ofstream;
using std::ios;


int main()
{
	
	ofstream outfile;
	//创建或打开文件，ios::trunc如果该文件已经存在，其内容将在打开文件之前被截断
	outfile.open("portlist.txt", ios::out | ios::trunc);
	
	//获取时间
	time_t cTime = time(NULL);
	char sTime[64] = { 0 };
	//格式化时间
	struct tm* localTime = localtime(&cTime);
	strftime(sTime, sizeof(sTime), "%Y-%m-%d %X", localTime);

	//向文件中写入时间
	outfile << sTime << endl;
	
	
	set<u_short> setTcpPort;
	cout << "tcp port set " << endl;
	outfile << "tcp port set " << endl;
	if (getTcpPortInfo(setTcpPort) == 0) {
		int i = 0;
		for (auto it = setTcpPort.begin(); it != setTcpPort.end(); it++) {
			cout << "[" << i << "]  tcp port:" << *it << endl;
			//向文件中写入tcp端口信息
			outfile << "[" << i << "]  tcp port:" << *it << endl;
			i++;
		}
	}
	

	set<u_short> setUdpPort;
	cout << "udp port set " << endl;
	outfile<< "udp port set " << endl;
	if (getUdpPortInfo(setUdpPort) == 0) {
		int i = 0;
		for (auto it = setUdpPort.begin(); it != setUdpPort.end(); it++) {
			cout <<"["<<i<<"]  udp port:" <<*it << endl;
			//向文件中写入UDP端口信息
			outfile << "[" << i << "]  udp port:" << *it << endl;
			i++;
		}
			
	}
	outfile.close();  // 执行完操作后关闭文件句柄
	return 0;
}

