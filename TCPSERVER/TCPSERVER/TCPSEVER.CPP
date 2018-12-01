#include<winsock2.h>
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")


int main()
{
	WSADATA data;
	WORD w=MAKEWORD(2,0);
	char sztext[]="Welcome,guy,here is hananiah\r\n";

	//Initialize the library of socket
	::WSAStartup(w,&data);
	SOCKET s,s1;
	s=::socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in server_addr,client_addr;
	int n=sizeof(server_addr);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(75);
	server_addr.sin_addr.S_un.S_addr=INADDR_ANY;
	//Bind the ip and port of server -end
    ::bind(s,(sockaddr*)&server_addr,sizeof(server_addr));
	//Start to listen if some one try to connect
	::listen(s,2);
	printf("My server is already started... ...\r\n");

	while(true)
	{
		//accept any guy's connection
		s1=::accept(s,(sockaddr*)&client_addr,&n);
		if(s1!=NULL)
		{
			printf("Client-end's IP:%s,---Hey,boy,you successfully connect to my server.\r\n",inet_ntoa(client_addr.sin_addr));
			::send(s1,sztext,sizeof(sztext),0);
		}
		//close sockets
		::closesocket(s);
		::closesocket(s1);
		::WSACleanup();

		//If any input,just over
		if(getchar())						
		{
		    return 0;						
		}
		else
		{
			::Sleep(100);
		}
	}
}