#include "comm.hpp"

static void Usage(std::string proc_)
{
	std::cout<<"Usage: "<<proc_<<" port"<<std::endl;
}
void *HanlderRequest(void *arg)
{
	int sock = (int)arg;
	Request_t rq;
	Response_t rsp;
	for(;;)
	{	
		ssize_t s = recv(sock,&rq,sizeof(rq),0);
		if(s<0)
		{
			std::cout<<"recv error!!" <<std::endl;
			continue;
		}
		else if(s == 0)
		{
			std::cout<<"client quit!!"<<std::endl;
			break;
		}
		else
		{
			char op = rq.op;
			switch(op)
			{
				case '+':
					rsp.result = rq.x + rq.y;
					break;
				case '-':
					rsp.result = rq.x - rq.y;
					break;
				case '*':
					rsp.result = rq.x * rq.y;
					break;
				case '/':
					if(rq.y == 0)
					{
						rsp.status = -1;
					}
					else
					{	
						rsp.result = rq.x / rq.y;
					}
					break;
				default:
					rsp.status = -2;
					break;		
			}
			send(sock,&rsp,sizeof(rsp),0);
		}
	}
	close(sock);
}
//./server prot
int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		Usage(argv[0]);
		exit(1);
	}
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0)
	{
		std::cout<<"socket error!!"<<std::endl;
		exit(2);
	}
	struct sockaddr_in local;
	bzero(&local,sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[1]));
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		std::cout<<"bind error!!"<<std::endl;
		exit(3);
	}
	
	if(listen(listen_sock,5)<0)
	{
		exit(4);
	}
	
	struct sockaddr_in client;
	for(;;)
	{
		socklen_t len = sizeof(client);
		int sock = accept(listen_sock,(struct sockaddr*)&client,&len);
		if(sock<0)
		{
			continue;
		}
		pthread_t tid;
		pthread_create(&tid,NULL,HanlderRequest,(void*)sock);
	}
	

	return 0;
}
