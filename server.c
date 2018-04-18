
     #include <netinet/in.h>
       #include <stdio.h>
       #include <sys/types.h>
       #include <sys/socket.h>
       #include <netdb.h>
	#include <stdlib.h>
	#include <strings.h>
	#include <unistd.h>
     
    
    
      void error(char *msg)
      {
        perror(msg);
        exit(1);
       }
    
      int main(int argc, char *argv[])
      {
       int sock, length, fromlen, n;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[1024];
	
	if(argc < 2 )
{	fprintf(stderr, "ERROR, no port provided\n");

}
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
	error("opening socket");
	}
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	fprintf (s.getsocketname()[0]);
	server.sin_port=htons(atoi(argv[1]));
	if (bind(sock,(struct sockaddr *)&server,length)<0)
	{
	error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);
	while(1)
	{
	n = recvfrom(sock, buf, 1024,0,(struct sockaddr *)&from, &fromlen);
	if(n<0)
	{
	error("recvfrom");

	}
	write(1,"Recived a datagram: ",21);
	write(1,buf,n);
	n = sendto(sock,"Got your message\n",17,0,(struct sockaddr *)&from, fromlen);
	if(n <0)
	{		
	error("sendto");
	}
	}	

     }
