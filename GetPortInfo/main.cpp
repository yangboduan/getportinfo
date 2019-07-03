//ref url:https://docs.microsoft.com/zh-cn/windows/win32/api/tcpmib/ns-tcpmib-_mib_tcptable
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)£»
// Need to link with Iphlpapi.lib and Ws2_32.lib

#include <iostream>
#include "getportinfo.h"  //getTcpPortInfo()  getUdpPortInfo()

using std::cout;
using std::endl;
using std::set;

int main()
{
	set<u_short> setTcpPort;
	cout << "tcp port set " << endl;
	if (getTcpPortInfo(setTcpPort) == 0) {
		int i = 0;
		for (auto it = setTcpPort.begin(); it != setTcpPort.end(); it++) {
			cout << "[" << i << "]  tcpp port:" << *it << endl;
			i++;
		}
	}
	

	set<u_short> setUdpPort;
	cout << "udp port set " << endl;
	if (getUdpPortInfo(setUdpPort) == 0) {
		int i = 0;
		for (auto it = setUdpPort.begin(); it != setUdpPort.end(); it++) {
			cout <<"["<<i<<"]  udp port:" <<*it << endl;
			i++;
		}
			
	}

	return 0;
}

