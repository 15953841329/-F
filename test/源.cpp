#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include<stdio.h>
#include<winsock2.h>    //��ͷ�ļ�����windows.h֮ǰ
#include<windows.h>
#include<string>
#include<iostream>
#pragma comment(lib,"ws2_32.lib") 
using namespace std;

void getIP()
{
    WSADATA WSAData;                                //WSADATA�ṹ�������������AfxSocketInitȫ�ֺ������ص�Windows Sockets��ʼ����Ϣ��
    if (WSAStartup(MAKEWORD(2, 0), &WSAData))        // ��ʼ��Windows sockets API
    {
        printf("WSAStartup failed %s\n", WSAGetLastError());
        exit(-1);        //�쳣�˳� 
    }

    char hostName[256];
    if (gethostname(hostName, sizeof(hostName)))        //��ȡ������
    {
        printf("Error: %u\n", WSAGetLastError());
        exit(-1);        //�쳣�˳� 
    }
    printf("��������             %s\n", hostName);

    hostent* host = gethostbyname(hostName);    // ������������ȡ������Ϣ. 
    if (host == NULL)
    {
        printf("Error: %u\n", WSAGetLastError());
        exit(-1);
    }

    cout << "������ַ����:        " << host->h_addrtype << endl
        << "��ַ�嵥:            " << host->h_addr_list << endl
        << "�����б�:            " << host->h_aliases << endl
        << "��ַ����:            " << host->h_length << endl
        << "��ʽ��������:        " << host->h_name << endl;

    for (int i = 0; host->h_addr_list[i] != 0; i++)
    {
        cout << "������IP" << i + 1 << ":           " << inet_ntoa(*(struct in_addr*)*host->h_addr_list) << endl;
    }
    cout << "-----------------------------------------------" << endl;
    WSACleanup();
}
void getSysInfo()
{
    SYSTEM_INFO  sysInfo;    //�ýṹ������˵�ǰ���������Ϣ�����������ϵ�ṹ�����봦���������͡�ϵͳ�����봦������������ҳ��Ĵ�С�Լ�������Ϣ��
    OSVERSIONINFOEX osvi;
    GetSystemInfo(&sysInfo);
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    if (GetVersionEx((LPOSVERSIONINFOW)&osvi))
    {
        printf("����ϵͳ�汾 :      %u.%u.%u\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
        printf("Service Pack :      %u.%u\n", osvi.wServicePackMajor, osvi.wServicePackMinor);
    }
    printf("�������ܹ� :        %u\n", sysInfo.wProcessorArchitecture);
    printf("���������� :        %u\n", sysInfo.wProcessorLevel);
    printf("�������汾 :        %u\n", sysInfo.wProcessorRevision);
    printf("���������� :        %u\n", sysInfo.dwActiveProcessorMask);
    printf("���������� :        %u\n", sysInfo.dwNumberOfProcessors);
    printf("���������� :        %u\n", sysInfo.dwProcessorType);
    printf("ҳ���С :          %u\n", sysInfo.dwPageSize);
    printf("Ӧ�ó�����С��ַ :  %u\n", sysInfo.lpMinimumApplicationAddress);
    printf("Ӧ�ó�������ַ :  %u\n", sysInfo.lpMaximumApplicationAddress);
    printf("�����ڴ�������� :  %u\n", sysInfo.dwAllocationGranularity);
    printf("OemId :             %u\n", sysInfo.dwOemId);
    printf("wReserved :         %u\n", sysInfo.wReserved);
}
int main()
{
   /* getIP();
    getSysInfo();*/

    return 0;
}