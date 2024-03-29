#include "getportinfo.h"
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;


#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */

int getTcpPortInfo(set<u_short>& setTcpPort) {

	// Declare and initialize variables
	PMIB_TCPTABLE pTcpTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	pTcpTable = (MIB_TCPTABLE*)MALLOC(sizeof(MIB_TCPTABLE));
	if (pTcpTable == NULL) {
		printf("Error allocating memory\n");
		return 1;
	}

	dwSize = sizeof(MIB_TCPTABLE);

	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) ==
		ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE*)MALLOC(dwSize);
		if (pTcpTable == NULL) {
			printf("Error allocating memory\n");
			return 1;
		}
	}


	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR) {
		for (int i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
			if (pTcpTable->table[i].dwState == MIB_TCP_STATE_LISTEN) {
				//printf("[%d] Local Port: %d \n", i, ntohs((u_short)pTcpTable->table[i].dwLocalPort));
				setTcpPort.insert(ntohs((u_short)pTcpTable->table[i].dwLocalPort));
			}
		}
	}
	else {
		printf("\tGetTcpTable failed with %d\n", dwRetVal);
		FREE(pTcpTable);
		return 1;
	}

	if (pTcpTable != NULL) {
		FREE(pTcpTable);
		pTcpTable = NULL;
	}
	return 0;
}



int getUdpPortInfo(set<u_short>& setUdpPort) {
	// Declare and initialize variables
	PMIB_UDPTABLE pUdpTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	pUdpTable = (MIB_UDPTABLE*)MALLOC(sizeof(MIB_UDPTABLE));
	if (pUdpTable == NULL) {
		printf("Error allocating memory\n");
		return 1;
	}

	dwSize = sizeof(MIB_UDPTABLE);

	if ((dwRetVal = GetUdpTable(pUdpTable, &dwSize, TRUE)) ==
		ERROR_INSUFFICIENT_BUFFER) {
		FREE(pUdpTable);
		pUdpTable = (MIB_UDPTABLE*)MALLOC(dwSize);
		if (pUdpTable == NULL) {
			printf("Error allocating memory\n");
			return 1;
		}
	}


	if ((dwRetVal = GetUdpTable(pUdpTable, &dwSize, TRUE)) == NO_ERROR) {
		for (int i = 0; i < (int)pUdpTable->dwNumEntries; i++) {
			/*if (pUdpTable->table[i].dwState == MIB_UDP_STATE_LISTEN) {*/
				//printf("[%d] Local Port: %d \n", i, ntohs((u_short)pUdpTable->table[i].dwLocalPort));
			setUdpPort.insert((u_short)pUdpTable->table[i].dwLocalPort);
			/*}*/
		}
	}
	else {
		printf("\tGetUdpTable failed with %d\n", dwRetVal);
		FREE(pUdpTable);
		return 1;
	}

	if (pUdpTable != NULL) {
		FREE(pUdpTable);
		pUdpTable = NULL;
	}
	return 0;
}