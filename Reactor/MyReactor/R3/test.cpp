#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include <iostream>
#include <unistd.h>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

//连接建立
using TcpConnectionPtr = shared_ptr<TcpConnection>;
void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!!" << endl;
}

//消息到达
void onMessage(const TcpConnectionPtr &con)
{
    //接收客户端的数据
    string msg = con->receive();
    cout << ">>recv msg from client: " << msg << endl;

    //做业务逻辑的处理

    //业务逻辑处理完毕之后，需要将数据msg发给客户端
    con->send(msg);

}

//连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}

void test()
{
    TcpServer server("127.0.0.1", 8888);
    //注册回调
    server.setAllCB(std::move(onNewConnection)
                          , std::move(onMessage)
                          , std::move(onClose));
    server.start();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}
