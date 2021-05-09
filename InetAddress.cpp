#include "InetAddress.h"
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib") 
InetAddress::InetAddress(uint16_t port,std::string ip)
{

    SOCKADDR_IN addrSrv;

	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	addrSrv.sin_family = AF_INET;

	addrSrv.sin_port = htons(6000);

    //addr_变量清零
    memset(&addr_, 0, sizeof(addr_));  //每个字节都用0填充

    //
    //网络字节序是大端的
    addr_.sin_family = AF_INET;
    //h(hight) to ns 字节序转换成大端
    addr_.sin_port = port;
    //addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}
std::string InetAddress::toIp() const
{
   return inet_ntoa(addr_.sin_addr);
}
std::string InetAddress::toIpPort() const
{
    std::string addr =  inet_ntoa(addr_.sin_addr);
    u_short port = ntohs(addr_.sin_port);
    std::string buf = addr +":"+ std::to_string(port);
    return buf;
}
uint16_t InetAddress::toPort() const
{
    return ntohs(addr_.sin_port);
}
InetAddress::~InetAddress()
{
}
