#pragma once
#include <winsock2.h> //u_short
#include<set>

using std::set;
int getTcpPortInfo(set<u_short>& setTcpPort);
int getUdpPortInfo(set<u_short>& setUdpPort);

