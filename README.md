# KTCP 通信
## 本库旨在简化c++服务端与客户端之间的tcp通信流程，简化了代码并实现了跨平台使用，即实现了不同平台一套代码
## 服务端代码示例：

```cpp
#include "TCP.h"
#include <iostream>
using namespace std;

// 服务端示例代码
int main() {
    /*
    * 创建服务器对象，参数为使用ipv4协议
    */
    Ktcpser tcp(AF_INET);
    
    /*
    * 绑定相关参数, 第一个参数为端口，第二个为IP地址
    * 创建成功返回KSOCKET_SUC 
    * 失败则返回KSOCKET_ERR
    */
    tcp.Kbindf(9999, "127.0.0.1");
    // 以上代码等同于Ktcpser tcp(9999,"127.0.0.1");
    
    /*
    * 设置最大监听数量
    * 创建成功返回KSOCKET_SUC 
    * 失败则返回KSOCKET_ERR	
    */
    tcp.Klisten(10);
    
    /*
    * 接受客户端连接
    * Kaccept()返回连接的客户端
    */
    Ktcpsocket KTS = tcp.Kaccept();
    
    /*
    * GETKsocket_Sersocket()返回客户端对象，若不为KINVALID_SOCKET，则为连接成功
    */
    if (KTS.GETKsocket_Sersocket() != KINVALID_SOCKET) {
        /*
        * GETCIP()返回客户端IP
        * GETKsockaddr_in()返回客户端具体信息
        * GETKsockaddr_in().sin_port返回客户端端口
        * Ku_short Khtons(Ku_short Khostshort); 主机字节序转网络字节序
        * Ku_long Khtonl(Ku_long Khostlong); 主机字节序转网络字节序
        * Ku_short Kntohs(Ku_short Knetshort); 网络字节序转主机字节序
        * Ku_long Kntohl(Ku_long Knetlong); 网络字节序转主机字节序
        * Kin_addr Kinet_addr(const char* Kcp, int af=AF_INET); 点分十进制ip转大端整形
        * const char* Kinet_ntop(const char* Kin, int af=AF_INET); 大端整形转点分十进制ip
        * const char* Kinet_ntop(const unsigned int* Kin, int af = AF_INET); 大端整形转点分十进制ip
        * const char* Kinet_ntop(const unsigned long* Kin, int af = AF_INET); 大端整形转点分十进制ip
        */
        
        cout << Kinet_ntop(&KTS.GETCIP()) << " " << Kntohs(KTS.GETKsockaddr_in().sin_port) << endl;
    }

    // 发送信息与接收信息
    while (true) {    
        /*
        * KsendS(string)发送消息给客户端
        * KrecvS()返回客户端给服务端发的消息，返回值为string，若客户端断开连接返回"KSOCKET_ERR"
        * KsendC(const char*)发送消息给客户端，若发送成功返回KSOCKET_SUC，若失败则返回KSOCKET_ERR;
        * KrecvC()返回服务器发的消息，若客户端关闭则返回nullptr
        */
        KTS.KsendS("test");
        string rv = KTS.KrecvS();
        if (rv != "KSOCKET_ERR")
            cout << rv << endl;
    }

    return 0;
}
```
## 客户端代码示例：
```cpp
#include "TCP.h"
#include <iostream>
using namespace std;

// 客户端示例代码
int main() {
    /*
    * 创建客户端对象，参数为地址族协议
    * Kconnect连接服务器，第一个参数为服务器端口，第二个端口为服务器IP
    */
    Ktcpcli cli(AF_INET);
    cli.Kconnect(9999, "127.0.0.1");
    // 以上代码等同于Ktcpcli cli(9999, "127.0.0.1");
    
    /*
    * Ksends(string)发送消息给服务器，若发送成功返回KSOCKET_SUC，若失败则返回KSOCKET_ERR;
    * KrecvS()返回服务器发的消息，若服务器关闭则返回"KSOCKET_ERR"
    * KsendC(const char*)发送消息给服务器，若发送成功返回KSOCKET_SUC，若失败则返回KSOCKET_ERR;
    * KrecvC()返回服务器发的消息，若服务器关闭则返回nullptr
    */
    cli.KsendS("test");
    while (true) {
        cout << cli.KrecvS();
    }
    
    return 0;
}

