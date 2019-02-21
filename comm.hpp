#pragma once

#include<iostream>
#include<strings.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<pthread.h>

typedef struct{
	int x;
	int y;
	char op;
}Request_t;

typedef struct{
	int status;	//判断计算是否合法
	int result;
}Response_t;

