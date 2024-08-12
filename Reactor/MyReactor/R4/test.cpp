#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "ThreadPool.h"
#include "TcpServer.h"
#include <iostream>
#include <unistd.h>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

//连接建立
using TcpConnectionPtr = shared_ptr<TcpConnection>;

ThreadPool *tPool = nullptr;

class MyTask{
public:
	//处理发送过来的信息，和连接
	MyTask(const string &msg,const TcpConnectionPtr &con)
	:_msg(msg)
	,_con(con)
	{
			
	}

	void process(){
		_con->sendInLoop(_msg);
	}

private:
	string _msg;
	TcpConnectionPtr _con;

};



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

	MyTask task(msg,con);

	tPool->addTask(std::bind(&MyTask::process,task));
}

//连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}

void test()
{
	ThreadPool pool(4,10);
	pool.start();
	tPool = &pool;

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
