#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

char* getIP()
{

	char hostName[256];
	if (gethostname(hostName, sizeof(hostName))) //��ȡ������
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1); //�쳣�˳� 
	}
	printf("��������    %s\n", hostName);

	hostent* host = gethostbyname(hostName); // ������������ȡ������Ϣ. 
	if (host == NULL)
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1);
	}

	//std::cout << "������ַ����:  " << host->h_addrtype << std::endl
	//	<< "��ַ�嵥:   " << host->h_addr_list << std::endl
	//	<< "�����б�:   " << host->h_aliases << std::endl
	//	<< "��ַ����:   " << host->h_length << std::endl
	//	<< "��ʽ��������:  " << host->h_name << std::endl;

	/*for (int i = 0; host->h_addr_list[i] != 0; i++)
	{
		std::cout << "������IP" << i + 1 << ":   " << inet_ntoa(*(struct in_addr*)*host->h_addr_list) << std::endl;
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

    WSADATA wsaData;
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))//��ʼ��Winsock����Ϣ������wsaData�� ��һ������ָ���汾���ڶ�������������winsock����Ϣ
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
	//�����ǽ�������
	//

	SOCKET socketserv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in addrServs = { 0 };
	addrServs.sin_family = AF_INET;
	addrServs.sin_port = htons(10086);
	bind(socketserv, (SOCKADDR*)&addrServs, sizeof(addrServs));
	//socks��
	int num = listen(socketserv, SOMAXCONN);
	printf("%d", num);

	SOCKET socketClients = accept(socketserv, nullptr, nullptr);
	send(socketClients, "���ӳɹ�", strlen("���ӳɹ�"), 0);


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

