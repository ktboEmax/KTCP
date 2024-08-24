#define KTCP_EXPORT
#include "TCP.h"
#include <string.h>
using namespace std;
Ku_short Khtons(Ku_short Khostshort) {
	return htons(Khostshort);
}
Ku_long Khtonl(Ku_long Khostlong) {
	return htonl(Khostlong);
}

Ku_short Kntohs(Ku_short Knetshort) {
	return ntohs(Knetshort);
}
Ku_long Kntohl(Ku_long Knetlong) {
	return ntohl(Knetlong);
}

Kin_addr Kinet_addr(const char* Kcp, int af) {
	//return inet_addr(Kcp);
	struct in_addr add;
	inet_pton(af, Kcp, &add);
	return add;
}

const char* Kinet_ntop(const char* Kin,int af) {
	//return inet_ntoa(Kin);
	const int N = 36;
	char dst[N];
	return inet_ntop(af, Kin, dst,N);
}

const char* Kinet_ntop(const unsigned int* Kin, int af) {
	//return inet_ntoa(Kin);
	//const int* k = new int(123);
	const int N = 36;
	char *dst=new char[N];
	return inet_ntop(af, Kin, dst,N);
}

const char* Kinet_ntop(const unsigned long* Kin, int af ) {
	const int N = 36;
	char* dst = new char[N];
	return inet_ntop(af, Kin, dst,N);
}

Ksocket Ktcpser::Ksocketf(int af, int type, int protocal) {
	return socket(af,type,protocal);
}

Ksocketenum Ktcpser::Kbindf(unsigned short int sin_port,const char* sin_addr,short int sin_family ) {
	Ksockaddr_inCreate(sin_family, sin_port, sin_addr);
	int ret = bind(Ksocket_Ser, (struct sockaddr*)&KserverAddr, sizeof(KserverAddr));
	return ret == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

Ksocketenum Ktcpser::Kbindf(Ksockaddr_in& name) {
	int ret= bind(Ksocket_Ser, (struct sockaddr*)&name, sizeof(name));
	//cout<<"123";
	return ret==0?KSOCKET_SUC:KSOCKET_ERR;
}

Ksocketenum Ktcpser::Klisten(int num) {
	int ref = listen(Ksocket_Ser, num);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}


string Ktcpsocket::KrecvS()
{
	const int N = 10240;
	char buffer[N];
	int size = recv(Ksocket_Sersocket,buffer, N, 0);
	if (size > 0) 
		return std::string(buffer);
	return "KSOCKET_ERR";
}

char* Ktcpsocket::KrecvC()
{
	const int N=10240;
	char *charCecv=new char[N];
	int size = recv(Ksocket_Sersocket,charCecv,N,0);
	if (size > 0)
		return charCecv;
	else
		delete[] charCecv;
	return nullptr;
}


Ksocketenum Ktcpsocket::KsendS(const string sbuf)
{
	int ref=KsendC(sbuf.c_str());
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}


Ksocketenum Ktcpsocket::KsendC(const char* cbuf)
{
	int ref = send(Ksocket_Sersocket, cbuf, strlen(cbuf)+1 , 0);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

Ksockaddr_in& Ktcpsocket::GETKsockaddr_in()
{
	return KsocketAddr;
}

void Ktcpsocket::SETKsocket_Sersocket(Ksocket VKsocket_Sersocket)
{
	Ksocket_Sersocket = VKsocket_Sersocket;
}

Ksocket& Ktcpsocket::GETKsocket_Sersocket()
{
	return Ksocket_Sersocket;
}

Ksocket Ktcpcli::Ksocketf(int af, int type, int protocal)
{
	return socket(af, type, protocal);
}

string Ktcpcli::KrecvS()
{
	const int N = 10240;
	char buffer[N];
	int size = recv(Ksocket_Cli, buffer, N, 0);
	if (size > 0)
		return std::string(buffer);
	return "KSOCKET_ERR";
}


Ksocketenum Ktcpcli::KsendC(const char* cbuf)
{
	int ref = send(Ksocket_Cli, cbuf, strlen(cbuf) + 1, 0);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}


char* Ktcpcli::KrecvC()
{
	const int N = 10240;
	char* charCecv = new char[N];
	int size = recv(Ksocket_Cli, charCecv, N, 0);
	if (size > 0)
		return charCecv;
	else
		delete[] charCecv;
	return nullptr;
}

Ksocketenum Ktcpcli::KsendS(const string sbuf)
{
	int ref = KsendC(sbuf.c_str());
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

Ksocketenum Ktcpcli::Kconnect(unsigned short int sin_port, const char* sin_addr, bool isQT)
{
	Ksockaddr_inCreate(sin_port, sin_addr, AF_INET);
	int ref = 0;
	if (isQT) {
		ref = ::connect(Ksocket_Cli, (struct sockaddr*)&KserverAddr, sizeof(KserverAddr));
	}
	else {
		ref = connect(Ksocket_Cli, (struct sockaddr*)&KserverAddr, sizeof(KserverAddr));
	}
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

Ksocket& Ktcpcli::GETKsocket_Cli()
{
	return Ksocket_Cli;
}

#ifdef  _WIN32
KWSAData Kwsa;
Ktcpsocket Ktcpser::Kaccept() {
	Ktcpsocket client;
	int addrlen = sizeof(client.GETKsockaddr_in());
	Ksocket ref = accept(Ksocket_Ser, (struct sockaddr*)&(client.GETKsockaddr_in()),&addrlen);
	client.SETKsocket_Sersocket(ref);
	return client;
}

void Ktcpser::Ksockaddr_inCreate(short int sin_family, unsigned short int sin_port, const char* sin_addr) {
	KserverAddr.sin_family = sin_family;
	KserverAddr.sin_port = Khtons(sin_port);
	KserverAddr.sin_addr.S_un.S_addr = Kinet_addr(sin_addr).S_un.S_addr;
}


Ktcpser::Ktcpser(int sin_family)
{
	WSAStartup(MAKEWORD(2, 2), &Kwsa);
	Ksocket_Ser = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Ser == INVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
}
Ktcpser::Ktcpser(unsigned short int sin_port,const char* sin_addr,short int sin_family)
{
	WSAStartup(MAKEWORD(2, 2), &Kwsa);
	Ksocket_Ser = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Ser == INVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
	Ksockaddr_inCreate(sin_family, sin_port, sin_addr);
	//cout<<Kbindf(sin_port, sin_addr, sin_family);
	Kbindf(KserverAddr);
	//cout<<Kbindf(KserverAddr)<<endl;
	//cout<<Kbindf(sin_port, sin_addr, sin_family);
}


Ktcpser::~Ktcpser()
{
	KSOCKET_close();
	WSACleanup();
}

Ksocketenum Ktcpser::KSOCKET_close()
{
	int ref=closesocket(Ksocket_Ser);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}



Ktcpsocket::~Ktcpsocket()
{
	closesocket(Ksocket_Sersocket);
}


Ktcpcli::Ktcpcli(int sin_family)
{
	WSAStartup(MAKEWORD(2, 2), &Kwsa);
	Ksocket_Cli = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Cli == INVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
}

Ktcpcli::Ktcpcli(unsigned short int sin_port, const char* sin_addr, short int sin_family)
{
	WSAStartup(MAKEWORD(2, 2), &Kwsa);
	Ksocket_Cli = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Cli == INVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
	Kconnect(sin_port, sin_addr);
	//cout << Kconnect(sin_port, sin_addr) << endl;
}

Ktcpcli::~Ktcpcli()
{
	KSOCKET_close();
	WSACleanup();
}

ULONG& Ktcpsocket::GETCIP() {
	return CIP;
}
ULONG& Ktcpcli::GETCIP() {
	return CIP;
}


Ksocketenum Ktcpcli::KSOCKET_close()
{
	int ref = closesocket(Ksocket_Cli);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

void Ktcpcli::Ksockaddr_inCreate(unsigned short int sin_port, const char* sin_addr, short int sin_family)
{
	KserverAddr.sin_family = sin_family;
	KserverAddr.sin_port = Khtons(sin_port);
	KserverAddr.sin_addr.S_un.S_addr = Kinet_addr(sin_addr).S_un.S_addr;

}
#elif __linux__
#include <unistd.h>
Ktcpsocket Ktcpser::Kaccept() {
	Ktcpsocket client;
	unsigned int addrlen = sizeof(client.GETKsockaddr_in());
	Ksocket ref = accept(Ksocket_Ser, (struct sockaddr*)&(client.GETKsockaddr_in()),&addrlen);
	client.SETKsocket_Sersocket(ref);
	return client;
}


void Ktcpser::Ksockaddr_inCreate(short int sin_family, unsigned short int sin_port, const char* sin_addr) {
	KserverAddr.sin_family = sin_family;
	KserverAddr.sin_port = Khtons(sin_port);
	KserverAddr.sin_addr.s_addr = Kinet_addr(sin_addr).s_addr;
}


Ktcpser::Ktcpser(int sin_family)
{

	Ksocket_Ser = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Ser == KINVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
}
Ktcpser::Ktcpser(unsigned short int sin_port,const char* sin_addr,short int sin_family)
{

	Ksocket_Ser = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Ser == KINVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
	Ksockaddr_inCreate(sin_family, sin_port, sin_addr);
	Kbindf(KserverAddr);
	//cout<<Kbindf(KserverAddr)<<endl;
	//cout<<"0";
	//cout<<Kbindf(sin_port, sin_addr, sin_family);
}


Ktcpser::~Ktcpser()
{
	KSOCKET_close();

}

Ksocketenum Ktcpser::KSOCKET_close()
{
	int ref=close(Ksocket_Ser);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

Ktcpsocket::~Ktcpsocket()
{
	close(Ksocket_Sersocket);
}


Ktcpcli::Ktcpcli(int sin_family)
{
	//WSAStartup(MAKEWORD(2, 2), &Kwsa);
	Ksocket_Cli = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Cli == KINVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
}

uint32_t& Ktcpcli::GETCIP(){
	return CIP;
}

uint32_t& Ktcpsocket::GETCIP(){
	return CIP;
}


Ktcpcli::Ktcpcli(unsigned short int sin_port, const char* sin_addr, short int sin_family)
{
	//WSAStartup(MAKEWORD(2, 2), &Kwsa);
	Ksocket_Cli = Ksocketf(sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (Ksocket_Cli == KINVALID_SOCKET) {
		printf("创建套接字失败\n");
		return;
	}
	Kconnect(sin_port, sin_addr);
}

Ktcpcli::~Ktcpcli()
{
	KSOCKET_close();
	//WSACleanup();
}


Ksocketenum Ktcpcli::KSOCKET_close()
{
	int ref = close(Ksocket_Cli);
	return ref == 0 ? KSOCKET_SUC : KSOCKET_ERR;
}

void Ktcpcli::Ksockaddr_inCreate(unsigned short int sin_port, const char* sin_addr, short int sin_family)
{
	KserverAddr.sin_family = sin_family;
	KserverAddr.sin_port = Khtons(sin_port);
	KserverAddr.sin_addr.s_addr = Kinet_addr(sin_addr).s_addr;

}
#endif 

