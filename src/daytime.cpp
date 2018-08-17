#include<muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
using namespace muduo;
using namespace muduo::net;
void onmessage(const TcpConnectionPtr&conn,
Buffer*buf,Timestamp time)
{
  string msg(buf->retrieveAllAsString());
  LOG_INFO<<conn->name()<<"discards "<<msg.size()
  <<" bytes receieved at "<<time.toString();
}

void onConnection(const TcpConnectionPtr&conn)
{
  LOG_INFO<<"DaytimeServer-"<<conn->peerAddress().toIpPort()<<"->"
  <<conn->localAddress().toIpPort()<<"is"<<(conn->connected()?"Up":"Down");

  if(conn->connected())
  {
    conn->send(Timestamp::now().toFormattedString()+"\n");
    conn->shutdown();
  }
}

int main()
{
  EventLoop loop;
  TcpServer server(&loop,InetAddress(1079),"Finger");
  server.setConnectionCallback(onConnection);
  server.start();
  loop.loop();
}

