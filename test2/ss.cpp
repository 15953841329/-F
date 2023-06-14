#include <iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))//初始化Winsock将信息保存在wsaData上 第一个参数指定版本，第二个参数包含了winsock的信息
        return 1;
    if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
        return 1;


    SOCKET socketserv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addrServ = { 0 };
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(10080);
    bind(socketserv, (SOCKADDR*)&addrServ, sizeof(addrServ));
    //socks绑定
    listen(socketserv, SOMAXCONN);
    SOCKET socketClient = accept(socketserv, nullptr, nullptr);
    while (1)
        send(socketClient, "ipconfig", strlen("ipconfig"), 0);


    WSACleanup();
    system("pause");
    return 0;
}

