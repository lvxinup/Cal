#include "comm.hpp"

static void Usage(std::string proc_)
{
	std::cout<<"Usage: "<<proc_<<" port"<<std::endl;
}
//./client ip prot
int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		std::cout<<"socket error!!"<<std::endl;
		exit(2);
	}
	struct sockaddr_in server;
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
		
	if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
	{
		std::cout<<"connect error!!" <<std::endl;
		exit(3);
	}
		
	Request_t rq;
	Response_t rsp;
	for(;;)
	{	
		std::cout<<"please enter<x,y>";
		std::cin>>rq.x>>rq.y;
		std::cout<<"please enter your op< + - * / >";
		std::cin>>rq.op;
		send(sock,&rq,sizeof(rq),0);
		recv(sock,&rsp,sizeof(rsp),0);
		std::cout<<"status: "<<rsp.status<<std::endl;
		std::cout<<"result: "<<rsp.result<<std::endl;
	}
	

	return 0;
}
