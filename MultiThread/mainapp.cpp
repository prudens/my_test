// �׽��ֿͻ���
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <WS2tcpip.h>
#include <fstream>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

int main( int, char** )
{
    WORD wVersionRequested;
    WSADATA wsaData;
    
    //����Winsocket DLL
    wVersionRequested = MAKEWORD( 2, 2 );
    
    int err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
        printf( "WSAStartup failed with error: %d\n", err );
        return 0;
    }

    if ( LOBYTE( wsaData.wVersion ) != 2
      || HIBYTE( wsaData.wVersion ) != 2 )
    {
        printf( "Could not find a usable version of Winsock.dll\n" );
        WSACleanup();
        return 0;
    }

    SOCKET sockClient = socket( AF_INET, SOCK_STREAM, 0 );//�����׽���
    SOCKADDR_IN addrSrv;//socketAddress socket�˿�
    //��������ַ����
    addrSrv.sin_addr.S_un.S_addr = inet_addr( "127.0.0.1" );
    // ��Ϊ�ͻ��ˣ���Ҫ���ӡ�connect����Զ�˵ķ�������
    // Ҳ��Ҫָ��Զ�˷������ģ�ip, port���ԡ�
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons( 6000 );

    connect( sockClient, (SOCKADDR *)&addrSrv, sizeof( SOCKADDR ) );

    char recvBuffer[100];
    recv( sockClient, recvBuffer, 100, 0 );
    printf( "%s\n", recvBuffer );//��ӡ����������

    ifstream ifs("mainapp.cpp");
    while ( ifs.good() )
    {
        memset( recvBuffer, 0, 100 );
        ifs.read( recvBuffer, 99 ); // ���һ��Ϊ'\0'
        send( sockClient, recvBuffer, strlen( recvBuffer ) + 1, 0 );
        cout << recvBuffer << endl;
    }
    ifs.close();
    
    closesocket( sockClient );
    WSACleanup();
    system( "pause" );
    return 0;
}