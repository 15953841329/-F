#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

char* getIP()
{

	char hostName[256];
	if (gethostname(hostName, sizeof(hostName))) //获取主机名
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1); //异常退出 
	}
	printf("主机名：    %s\n", hostName);

	hostent* host = gethostbyname(hostName); // 根据主机名获取主机信息. 
	if (host == NULL)
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1);
	}

	//std::cout << "主机地址类型:  " << host->h_addrtype << std::endl
	//	<< "地址清单:   " << host->h_addr_list << std::endl
	//	<< "别名列表:   " << host->h_aliases << std::endl
	//	<< "地址长度:   " << host->h_length << std::endl
	//	<< "正式的主机名:  " << host->h_name << std::endl;

	/*for (int i = 0; host->h_addr_list[i] != 0; i++)
	{
		std::cout << "该主机IP" << i + 1 << ":   " << inet_ntoa(*(struct in_addr*)*host->h_addr_list) << std::endl;
	}
	std::cout << "-----------------------------------------------" << std::endl;*/
	//std::cout << inet_ntoa(*(struct in_addr*)*host->h_addr_list)<<std::endl;

	char tmp[1024] = {0};
	sprintf(tmp,"%s;%d;%s;", inet_ntoa(*(struct in_addr*)*host->h_addr_list),10086, hostName);
	return  tmp;
	//WSACleanup();
}

void getSysInfo()
{
	SYSTEM_INFO  sysInfo;    //该结构体包含了当前计算机的信息：计算机的体系结构、中央处理器的类型、系统中中央处理器的数量、页面的大小以及其他信息。
	OSVERSIONINFOEX osvi;
	GetSystemInfo(&sysInfo);
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	if (GetVersionEx((LPOSVERSIONINFOW)&osvi))
	{
		printf("操作系统版本 :      %u.%u.%u\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
		printf("Service Pack :      %u.%u\n", osvi.wServicePackMajor, osvi.wServicePackMinor);
	}
	printf("处理器架构 :        %u\n", sysInfo.wProcessorArchitecture);
	printf("处理器级别 :        %u\n", sysInfo.wProcessorLevel);
	printf("处理器版本 :        %u\n", sysInfo.wProcessorRevision);
	printf("处理器掩码 :        %u\n", sysInfo.dwActiveProcessorMask);
	printf("处理器数量 :        %u\n", sysInfo.dwNumberOfProcessors);
	printf("处理器类型 :        %u\n", sysInfo.dwProcessorType);
	printf("页面大小 :          %u\n", sysInfo.dwPageSize);
	printf("应用程序最小地址 :  %u\n", sysInfo.lpMinimumApplicationAddress);
	printf("应用程序最大地址 :  %u\n", sysInfo.lpMaximumApplicationAddress);
	printf("虚拟内存分配粒度 :  %u\n", sysInfo.dwAllocationGranularity);
	printf("OemId :             %u\n", sysInfo.dwOemId);
	printf("wReserved :         %u\n", sysInfo.wReserved);
}

int main()
{

    WSADATA wsaData;
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))//初始化Winsock将信息保存在wsaData上 第一个参数指定版本，第二个参数包含了winsock的信息
        return 1;
    if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
        return 1;
    SOCKET socketclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addrServ = { 0 };
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(10080);
    addrServ.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    connect(socketclient, (SOCKADDR*)&addrServ, sizeof(addrServ));

    char szBuffer[MAXBYTE] = { 0 };
	recv(socketclient, szBuffer, MAXBYTE, 0);
	std::cout << szBuffer;
	//以上是建立连接
	//

	SOCKET socketserv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in addrServs = { 0 };
	addrServs.sin_family = AF_INET;
	addrServs.sin_port = htons(10086);
	bind(socketserv, (SOCKADDR*)&addrServs, sizeof(addrServs));
	//socks绑定
	int num = listen(socketserv, SOMAXCONN);
	printf("%d", num);

	SOCKET socketClients = accept(socketserv, nullptr, nullptr);
	send(socketClients, "连接成功", strlen("连接成功"), 0);


    while(1){
		memset(szBuffer,0,sizeof(szBuffer));
        int t=recv(socketclient, szBuffer, MAXBYTE, 0);
		printf("%d",t);
		//puts(szBuffer);
        if (strcmp(szBuffer, "getip") == 0)
        {
			//puts("test");
			char* tmp=getIP();
			//puts(getIP());
			puts(tmp);
			int m=send(socketClients, tmp, strlen(tmp), 0);
			printf("%d",m);
        }
    }
    WSACleanup();
    system(szBuffer);
    system("pause");
    return 0;
}   

