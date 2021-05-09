#pragma once
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include<WinSock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wsock32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

//封装socket地址类型
class InetAddress
{

public:
    explicit InetAddress(uint16_t port,std::string ip="127.0.0.1");
    explicit InetAddress(const sockaddr_in &addr):addr_(addr)
    {

    }
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const sockaddr_in* getSockAddr() const {return &addr_;}
    ~InetAddress();
private:
    sockaddr_in addr_;    
};


