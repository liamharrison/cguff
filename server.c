#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

	int ifdServer, ifdClient, iReturnValue, iBytesRead;
	struct sockaddr_in oServerDefinition;
	char cBuffer[1];

	ifdServer = 0;
	ifdClient = 0;

	ifdServer = socket(AF_INET, SOCK_STREAM, 0);
	memset(&oServerDefinition, 0, sizeof(oServerDefinition));

	oServerDefinition.sin_family = AF_INET;
	oServerDefinition.sin_addr.s_addr = htonl(INADDR_ANY);
	oServerDefinition.sin_port = htons(5000); 

	iReturnValue = bind(ifdServer, (struct sockaddr *)&oServerDefinition, sizeof(oServerDefinition));
	if(iReturnValue != 0){
		perror("bind");
		return(-1);
	}

	iReturnValue = listen(ifdServer, 10); 
	if(iReturnValue != 0){
		perror("bind");
		return(-1);
	}

	ifdClient = accept(ifdServer, (struct sockaddr *)NULL, NULL); 

	iBytesRead = read(ifdClient, cBuffer, 1);
	if(iBytesRead != 1){
		printf("wrong number of bytes read\n");
		return(-1);
	}

	printf("recieved value %d\n");

	close(ifdClient);
	close(ifdServer);
}
