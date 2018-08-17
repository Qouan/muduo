#include<muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include<algorithm>
#include <ctype.h>
#include <fcntl.h>
//#include<string>
//#include<stdlib.h>
//#include<stdio.h>
using namespace muduo;
using namespace muduo::net;
const char*g_file=NULL;
char buf[4096];
string readFile(const char*filename)
{
    int fd=open(filename,O_RDONLY);
	if(fd<0)LOG_INFO<<"error:"<<g_file;
	read(fd,buf,4096);
	string str=buf;
	close(fd);
	return str;
}

void onConnection(const TcpConnectionPtr&conn)
{
	LOG_INFO<<conn->localAddress().toIpPort()<<"->"
		<<conn->peerAddress().toIpPort()<<"is"
		<<(conn->connected()?"UP":"DOWN");
	if(conn->connected())
	{
		LOG_INFO<<"FileServer-Sending file file"<<g_file
			<<" to "<<conn->peerAddress().toIpPort();
		string fileContend=readFile(g_file);
		LOG_INFO<<fileContend<<"\n";
		conn->send(fileContend);
		conn->shutdown();
		LOG_INFO<<"FileServer-done";
	}
}
int main(int argc,char*argv[])
{
	LOG_INFO<<"pid= "<<getpid();
	if(argc>1)
	{
		g_file=argv[1];

		EventLoop loop;
		InetAddress listenAddr(2021);
		TcpServer server(&loop,listenAddr,"FileServer");
		server.setConnectionCallback(onConnection);
		server.start();
		loop.loop();
	}
	else
	{
		fprintf(stderr, "Usage:%s file_for_downloading\n",argv[0]);
	}
}
