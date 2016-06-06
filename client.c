#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

	int ifdSocket, iReturnValue;
	struct sockaddr_in oServerDefinition;
	char cBuffer[1];

	ifdSocket = 0;

	if((ifdSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return(-1);
	} 

	memset(&oServerDefinition, '0', sizeof(oServerDefinition)); 

	oServerDefinition.sin_family = AF_INET;
	oServerDefinition.sin_port = htons(5000); 

	if(inet_pton(AF_INET, "127.0.0.1", &oServerDefinition.sin_addr) <= 0){
		perror("inet_pton");
		return(-1);
	} 

	if(connect(ifdSocket, (struct sockaddr *)&oServerDefinition, sizeof(oServerDefinition)) < 0){
		perror("connect");
		return(-1);
	} 

	cBuffer[0] = 128;

	iReturnValue = write(ifdSocket, cBuffer, 1);
	if(iReturnValue != 1){
		printf("wrong number of bytes written %d\n", iReturnValue);
	}

	return(0);
}
