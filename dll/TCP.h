
#pragma once
#ifdef KTCP_EXPORT
#define KTCPAPI __declspec(dllexport)
#else
#define KTCPAPI __declspec(dllimport)
#endif
#ifdef  _WIN32
#include <winsock2.h>
#include <string>
#include <WS2tcpip.h>
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
using namespace std;
typedef SOCKET Ksocket;
typedef struct sockaddr Ksockaddr;
typedef struct sockaddr_in Ksockaddr_in;
typedef WSAData KWSAData;
typedef u_short Ku_short;
typedef u_long Ku_long;
typedef struct in_addr Kin_addr;
#define KINVALID_SOCKET INVALID_SOCKET
#elif __linux__
#include <arpa/inet.h>
#include <string>
#include <string.h>
using namespace std;
#define KINVALID_SOCKET -1
typedef uint16_t Ku_short;
typedef uint16_t Ku_long;
typedef sockaddr_in Ksockaddr_in;
typedef int Ksocket;
typedef in_addr Kin_addr;
#endif 
KTCPAPI Ku_short Khtons(Ku_short Khostshort);
KTCPAPI Ku_long Khtonl(Ku_long Khostlong);

KTCPAPI Ku_short Kntohs(Ku_short Knetshort);
KTCPAPI Ku_long Kntohl(Ku_long Knetlong);

KTCPAPI Kin_addr Kinet_addr(const char* Kcp, int af=AF_INET);	// windows

KTCPAPI const char* Kinet_ntop(const char* Kin,int af=AF_INET);
KTCPAPI const char* Kinet_ntop(const unsigned int* Kin, int af = AF_INET);
KTCPAPI const char* Kinet_ntop(const unsigned long* Kin, int af = AF_INET);
KTCPAPI enum Ksocketenum {
	KSOCKET_SUC,
	KSOCKET_ERR
};

class KTCPAPI Ktcpsocket {
public:

	~Ktcpsocket();
	string KrecvS();
	char* KrecvC();
	Ksocketenum KsendS(const string sbuf);
	Ksocketenum KsendC(const char* cbuf);
	Ksockaddr_in& GETKsockaddr_in();
	void SETKsocket_Sersocket(Ksocket VKsocket_Sersocket);
	Ksocket& GETKsocket_Sersocket();
	#ifdef  _WIN32
	ULONG& GETCIP();
	#elif __linux__
	uint32_t& GETCIP();
	#endif	
private:
	Ksockaddr_in KsocketAddr;
	Ksocket Ksocket_Sersocket;
	#ifdef  _WIN32
	ULONG& CIP = KsocketAddr.sin_addr.S_un.S_addr;
	#elif __linux__
	uint32_t& CIP = KsocketAddr.sin_addr.s_addr;
	#endif	
};

class KTCPAPI Ktcpser {
public:
	Ktcpser(unsigned short int sin_port, const char* sin_addr, short int sin_family=AF_INET);
	Ktcpser(int sin_family = AF_INET);
	~Ktcpser();
	Ksocket Ksocketf(int af, int type,int protocal);
	Ksocketenum Kbindf(unsigned short int sin_port,const char* sin_addr, short int sin_family = AF_INET);
	void Ksockaddr_inCreate(short int sin_family, unsigned short int sin_port, const char* sin_addr);
	Ksocketenum Kbindf(Ksockaddr_in& name);
	Ksocketenum Klisten(int num);
	Ktcpsocket Kaccept();
	Ksocketenum KSOCKET_close();

private:
	Ksockaddr_in KserverAddr;
	Ksocket Ksocket_Ser;

	//Ktcpsocket* KTcpSocket;
};
class KTCPAPI Ktcpcli {
public:
	Ktcpcli(int sin_family = AF_INET);
	Ktcpcli(unsigned short int sin_port, const char* sin_addr, short int sin_family = AF_INET);
	~Ktcpcli();
	Ksocket Ksocketf(int af, int type, int protocal);
	string KrecvS();
	char* KrecvC();
	Ksocketenum KsendS(const string sbuf);
	Ksocketenum KsendC(const char* cbuf);
	Ksocketenum KSOCKET_close();
	void Ksockaddr_inCreate(unsigned short int sin_port, const char* sin_addr, short int sin_family = AF_INET);
	Ksocketenum Kconnect(unsigned short int sin_port, const char* sin_addr, bool isQT = false);
	Ksocket& GETKsocket_Cli();
	#ifdef  _WIN32
	ULONG& GETCIP();
	#elif __linux__
	uint32_t& GETCIP();
	#endif	

private:
	Ksockaddr_in KserverAddr;
	Ksocket Ksocket_Cli;
	#ifdef  _WIN32
	ULONG& CIP = KserverAddr.sin_addr.S_un.S_addr;
	#elif __linux__
	uint32_t& CIP = KserverAddr.sin_addr.s_addr;
	#endif	
};
