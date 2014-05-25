#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <process.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

#define MAX_PENDING_CONNECT 5

unsigned  int __stdcall ClientConnect( void * args );
int main( int, char** )
{
    WORD wVersionRequested = MAKEWORD( 2, 2 );
    WSADATA wsaData;

    //��Windows�µ������̽ӿ����Winsock1 �� Winsock2 �����һ������

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

    // �ṩtcpЭ��
    SOCKET sockSrv = socket( AF_INET, SOCK_STREAM, 0 );
   
    SOCKADDR_IN addrSrv;// sockaddr_in��sockaddr�ǲ��еĽṹ

    addrSrv.sin_addr.S_un.S_addr = htonl( INADDR_ANY );
    // ����local.sin_addr.s_addr��ip��ַ��
    // ��Ϊ����������Ҫ�󶨡�bind�������ص�IP��ַ�Ͻ��м�����listen����
    // ������Ļ����Ͽ����ж��������Ҳ���ж��IP��ַ��
    // ��ʱ����Ҫѡ������ĸ�IP���棬���ָ��ΪINADDR_ANY��
    // ��ôϵͳ����Ĭ�ϵ���������IP��ַ����
    // ��Ϊ�ͻ��ˣ���Ҫ���ӡ�connect����Զ�˵ķ�������
    // Ҳ��Ҫָ��Զ�˷������ģ�ip, port���ԡ�
    // ��Ȼ������������£������ܽ�IP��ַָ��ΪINADDR_ANY��ϵͳ�����ġ�
    addrSrv.sin_family = AF_INET; 
    addrSrv.sin_port = htons( 6000 );
   
    bind( sockSrv, (SOCKADDR*)&addrSrv, sizeof( SOCKADDR ) );

    //�������һ�����ڷ�������,����ĵڶ�������Ϊ���������������
    // ע�⣬��������Ѿ�������Ŀ
    listen( sockSrv, MAX_PENDING_CONNECT );

    SOCKADDR_IN addrClient;//��sockaddr�ȼ۵����ݽṹ
    int len = sizeof( SOCKADDR );

    while ( 1 )
    {
        //��������������л��������Ϣ�������µ��׽��֣������ظ��׽��ֵ��ļ���������
        // �´������׽������ڷ�������ͻ�����ͨ�ţ���ԭ�����׽�����Ȼ���ڼ���״̬�� 

        //acceptһ����Ҫ���ڷ�������,�ڶ�������ͬ������ʹ��SOCKADDR_IN�������
        // ����ע�⣬����ò����������洢��������ʱ��ͻ��˵������Ϣ��

        //����������accept�����Ӵ��ڼ���״̬�����׽���s�Ŀͻ��������������ȡ��������ǰ��һ���ͻ�����
        //���Ҵ���һ���µ��׽�������ͻ��׽��ִ�������ͨ����������ӳɹ����ͷ����´������׽��ֵ���������
        //�Ժ���ͻ��׽��ֽ������ݵ����´������׽��֣����ʧ�ܾͷ��� INVALID_SOCKET��
        //�ú����ĵ�һ������ָ�����ڼ���״̬�����׽��֣�
        //����ϵͳ���õڶ������������������ӵĿͻ����̵�Э���ַ����cliaddrָ����ָ����
        //����ϵͳ���õ��������������ظõ�ַ�����������Ĵ�С��
        //������ǶԿͻ�Э���ַ������Ȥ����ô���԰�cliaddr��addrlen����Ϊ��ָ��NULL�� 
        SOCKET sockConn = accept( sockSrv, (SOCKADDR *)&addrClient, &len );

        CloseHandle( (HANDLE)_beginthreadex( NULL,
            0,
            ClientConnect,
            (void*)&sockConn,
            0,
            NULL ) );
    }
    
    return 0;
}


unsigned  int __stdcall ClientConnect( void * args )
{
    SOCKET socket = *(SOCKET*)args;
    SOCKADDR_IN addrClient;//��sockaddr�ȼ۵����ݽṹ
    int len = sizeof(SOCKADDR_IN);
    if ( getpeername( socket, (sockaddr*)&addrClient, &len )
         == SOCKET_ERROR )
    {
        cout << "getpeername fail error code: "<<WSAGetLastError() << endl;
    }

    char sendbuffer[100];
    sprintf_s( sendbuffer, "welcome %s here", inet_ntoa( addrClient.sin_addr ) );
    // �ú��������໥�������ݣ�������Ҫע����ǣ�
    // ��������ʹ�øú���ʱ�򣬵�һ������Ϊaccept���������ص�socket�ṹֵ��
    send( socket, sendbuffer, strlen( sendbuffer ) + 1, 0 );
    char recvchar[100];
    ofstream of( "test.txt" );

    while ( true )
    {
        int nBytes = recv( socket, recvchar, 100, 0 );
        if ( nBytes == 0 )
        {
            cout << "�׽����Ѿ��رգ�" << endl;
            break;
        }
        cout << recvchar << endl;
        of << recvchar;
    }
    of.close( );
    closesocket( socket );//�������ر�һ���׽ӿڡ�
    return 0;
}