#include<muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include<algorithm>
#include <ctype.h>
using namespace muduo;
using namespace muduo::net;
void onmessage(const TcpConnectionPtr&conn,
Buffer*buf,Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO<<conn->name()<<" echo "<<msg.size()<< "bytes, "
        <<"data receieved t "<<time.toFormattedString()<<msg<<"\n";
    for(auto&a:msg)
    {
        a=static_cast<char>(toupper(a));
    }
    conn->send(msg);
    if(!conn->connected())
        conn->shutdown();
}
int main()
{
    EventLoop loop;
    TcpServer server(&loop,InetAddress(8080),"echo");
    server.setMessageCallback(onmessage);
    server.start();
    loop.loop();
}
