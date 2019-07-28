//ref url:https://docs.microsoft.com/zh-cn/windows/win32/api/tcpmib/ns-tcpmib-_mib_tcptable
#define _CRT_SECURE_NO_WARNINGS //�رղ���ȫ���������������ʾ
#pragma warning(disable:4996)��
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
	//��������ļ���ios::trunc������ļ��Ѿ����ڣ������ݽ��ڴ��ļ�֮ǰ���ض�
	outfile.open("portlist.txt", ios::out | ios::trunc);
	
	//��ȡʱ��
	time_t cTime = time(NULL);
	char sTime[64] = { 0 };
	//��ʽ��ʱ��
	struct tm* localTime = localtime(&cTime);
	strftime(sTime, sizeof(sTime), "%Y-%m-%d %X", localTime);

	//���ļ���д��ʱ��
	outfile << sTime << endl;
	
	
	set<u_short> setTcpPort;
	cout << "tcp port set " << endl;
	outfile << "tcp port set " << endl;
	if (getTcpPortInfo(setTcpPort) == 0) {
		int i = 0;
		for (auto it = setTcpPort.begin(); it != setTcpPort.end(); it++) {
			cout << "[" << i << "]  tcp port:" << *it << endl;
			//���ļ���д��tcp�˿���Ϣ
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
			//���ļ���д��UDP�˿���Ϣ
			outfile << "[" << i << "]  udp port:" << *it << endl;
			i++;
		}
			
	}
	outfile.close();  // ִ���������ر��ļ����
	return 0;
}

