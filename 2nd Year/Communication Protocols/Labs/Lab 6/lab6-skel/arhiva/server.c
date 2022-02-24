/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	if (argc!=3)
		usage(argv[0]);
	
	struct sockaddr_in my_sockaddr, from_station ;
	char buf[BUFLEN];


	/*Deschidere socket*/
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	
	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
	my_sockaddr.sin_family = AF_INET;
	my_sockaddr.sin_port = htons(12345);
	my_sockaddr.sin_addr.s_addr = INADDR_ANY;

	
	/* Legare proprietati de socket */
	int b = bind(sock, (struct sockaddr*) &my_sockaddr, sizeof(my_sockaddr));

	printf("[SERVER] System has been successfully started.\n");
	
	
	/* Deschidere fisier pentru scriere */
	DIE((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");
	

	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/

	socklen_t socklen = sizeof(from_station);
	int r;
	
	while( (r = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*) &from_station, &socklen)) != -1)
	{
		write(fd, buf, r);
		if (r < 0) {
			perror("[SERVER] Error at receiving data from socket.\n");
			close(sock);
			return 1;
		}	
	}


	/*Inchidere socket*/	
	close(sock);
	
	/*Inchidere fisier*/
	close(fd);

	return 0;
}
