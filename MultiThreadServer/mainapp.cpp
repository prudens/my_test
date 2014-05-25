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

    //是Windows下的网络编程接口软件Winsock1 或 Winsock2 里面的一个命令

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

    // 提供tcp协议
    SOCKET sockSrv = socket( AF_INET, SOCK_STREAM, 0 );
   
    SOCKADDR_IN addrSrv;// sockaddr_in和sockaddr是并列的结构

    addrSrv.sin_addr.S_un.S_addr = htonl( INADDR_ANY );
    // 所以local.sin_addr.s_addr是ip地址。
    // 作为服务器，你要绑定【bind】到本地的IP地址上进行监听【listen】，
    // 但是你的机器上可能有多块网卡，也就有多个IP地址，
    // 这时候你要选择绑定在哪个IP上面，如果指定为INADDR_ANY，
    // 那么系统将绑定默认的网卡【即IP地址】。
    // 作为客户端，你要连接【connect】到远端的服务器，
    // 也是要指定远端服务器的（ip, port）对。
    // 当然，在这种情况下，不可能将IP地址指定为INADDR_ANY，系统会疯掉的。
    addrSrv.sin_family = AF_INET; 
    addrSrv.sin_port = htons( 6000 );
   
    bind( sockSrv, (SOCKADDR*)&addrSrv, sizeof( SOCKADDR ) );

    //这个函数一般用于服务器端,这里的第二个参数为待连接最大数量，
    // 注意，不是最大已经连接数目
    listen( sockSrv, MAX_PENDING_CONNECT );

    SOCKADDR_IN addrClient;//与sockaddr等价的数据结构
    int len = sizeof( SOCKADDR );

    while ( 1 )
    {
        //从连接请求队列中获得连接信息，创建新的套接字，并返回该套接字的文件描述符。
        // 新创建的套接字用于服务器与客户机的通信，而原来的套接字仍然处于监听状态。 

        //accept一样主要用于服务器端,第二个参数同样可以使用SOCKADDR_IN来替代，
        // 但是注意，这里，该参数是用来存储建立连接时候客户端的相关信息。

        //服务程序调用accept函数从处于监听状态的流套接字s的客户连接请求队列中取出排在最前的一个客户请求，
        //并且创建一个新的套接字来与客户套接字创建连接通道，如果连接成功，就返回新创建的套接字的描述符，
        //以后与客户套接字交换数据的是新创建的套接字；如果失败就返回 INVALID_SOCKET。
        //该函数的第一个参数指定处于监听状态的流套接字；
        //操作系统利用第二个参数来返回所连接的客户进程的协议地址（由cliaddr指针所指）；
        //操作系统利用第三个参数来返回该地址（参数二）的大小。
        //如果我们对客户协议地址不感兴趣，那么可以把cliaddr和addrlen均置为空指针NULL。 
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
    SOCKADDR_IN addrClient;//与sockaddr等价的数据结构
    int len = sizeof(SOCKADDR_IN);
    if ( getpeername( socket, (sockaddr*)&addrClient, &len )
         == SOCKET_ERROR )
    {
        cout << "getpeername fail error code: "<<WSAGetLastError() << endl;
    }

    char sendbuffer[100];
    sprintf_s( sendbuffer, "welcome %s here", inet_ntoa( addrClient.sin_addr ) );
    // 该函数用来相互发送数据，但是需要注意的是，
    // 服务器端使用该函数时候，第一个参数为accept函数所返回的socket结构值。
    send( socket, sendbuffer, strlen( sendbuffer ) + 1, 0 );
    char recvchar[100];
    ofstream of( "test.txt" );

    while ( true )
    {
        int nBytes = recv( socket, recvchar, 100, 0 );
        if ( nBytes == 0 )
        {
            cout << "套接字已经关闭！" << endl;
            break;
        }
        cout << recvchar << endl;
        of << recvchar;
    }
    of.close( );
    closesocket( socket );//本函数关闭一个套接口。
    return 0;
}