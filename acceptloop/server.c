#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>


int read_from_client(int ifdClient){

	unsigned char ucBuffer[1024];
	int iBytesRead;	

	iBytesRead = read(ifdClient, ucBuffer, 1024);

	printf("read %d bytes, value %d\n", iBytesRead, ucBuffer[0]);

	if(iBytesRead == 0){
		return(-1);
	}

	return(iBytesRead);

}


int main(int argc, char *argv[]){

	int ifdServer, ifdClient, iReturnValue, iBytesRead, i;
	struct sockaddr_in oServerDefinition;
	fd_set active_fd_set, read_fd_set;

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

	FD_ZERO(&active_fd_set);
	FD_SET(ifdServer, &active_fd_set);

	while(1){


		read_fd_set = active_fd_set;
		if(select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0){
			perror ("select");
			return(-1);
		}

		for (i = 0; i < FD_SETSIZE; ++i)
			if (FD_ISSET (i, &read_fd_set)){

				if (i == ifdServer){
				int new;
				new = accept (ifdServer, (struct sockaddr *) NULL, NULL);

				if (new < 0){
					perror ("accept");
					return(-1);
				}

				printf("new connection\n");

				FD_SET (new, &active_fd_set);
			}else{

				/* Data arriving on an already-connected socket. */
				if (read_from_client (i) < 0){
					close (i);
					FD_CLR (i, &active_fd_set);
				}
			}
		}



	}

	close(ifdServer);
}
