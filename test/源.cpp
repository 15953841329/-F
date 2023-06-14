#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include<stdio.h>
#include<winsock2.h>    //该头文件需在windows.h之前
#include<windows.h>
#include<string>
#include<iostream>
#pragma comment(lib,"ws2_32.lib") 
using namespace std;

void getIP()
{
    WSADATA WSAData;                                //WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息。
    if (WSAStartup(MAKEWORD(2, 0), &WSAData))        // 初始化Windows sockets API
    {
        printf("WSAStartup failed %s\n", WSAGetLastError());
        exit(-1);        //异常退出 
    }

    char hostName[256];
    if (gethostname(hostName, sizeof(hostName)))        //获取主机名
    {
        printf("Error: %u\n", WSAGetLastError());
        exit(-1);        //异常退出 
    }
    printf("主机名：             %s\n", hostName);

    hostent* host = gethostbyname(hostName);    // 根据主机名获取主机信息. 
    if (host == NULL)
    {
        printf("Error: %u\n", WSAGetLastError());
        exit(-1);
    }

    cout << "主机地址类型:        " << host->h_addrtype << endl
        << "地址清单:            " << host->h_addr_list << endl
        << "别名列表:            " << host->h_aliases << endl
        << "地址长度:            " << host->h_length << endl
        << "正式的主机名:        " << host->h_name << endl;

    for (int i = 0; host->h_addr_list[i] != 0; i++)
    {
        cout << "该主机IP" << i + 1 << ":           " << inet_ntoa(*(struct in_addr*)*host->h_addr_list) << endl;
    }
    cout << "-----------------------------------------------" << endl;
    WSACleanup();
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
   /* getIP();
    getSysInfo();*/

    return 0;
}