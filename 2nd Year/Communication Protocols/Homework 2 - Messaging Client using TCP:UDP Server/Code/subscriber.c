#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file) {
	fprintf(stderr, "Usage: %s ./subscriber <ID_Client> <IP_Server> <Port_Server>\n", file);
	exit(0);
}

int main(int argc, char **argv)
{

	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	int sockfd, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];

	if (argc != 4) {
		usage(argv[0]);
	}

	fd_set read_fds;	// Definesc o multime de citire pentru functia select()
	fd_set tmp_fds;		// Multime de citire folosita temporar
	int fdmax;			// Valoare maxima a file descriptorului din 
						//multimea read_fds

	FD_ZERO(&tmp_fds);
	FD_ZERO(&read_fds);

	// Initializare socket pentru conexiunea cu serverul
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "Nu se poate deschide socketul!");

	// Initializare si file descriptori
	FD_SET(sockfd, &read_fds);
	FD_SET(0, &read_fds);
	fdmax = sockfd;

	// Completare informatii pentru pentru socketul socketul TCP
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[3]));
	ret = inet_aton(argv[2], &serv_addr.sin_addr);
	DIE(ret == 0, "Adresa IP incorecta!");

	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "Eroare la conectarea cu serverul");

	ret = send(sockfd, argv[1], strlen(argv[1]) + 1, 0);
	DIE(ret < 0, "Nu se poate trimite catre server");

	int value = 1;
	ret = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&value,
	sizeof(int));
	DIE(ret < 0, "Nu s-a putut dezactiva algoritmul lui Neagle");

	while (1) {
  		// Citesc de la stdin sau din server
		tmp_fds = read_fds;
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "Eroare la selectare socket");

		// Daca primesc un mesaj de la stdin
		if (FD_ISSET(0, &tmp_fds)) {
			memset(buffer, 0, BUFLEN);
			fgets(buffer, BUFLEN - 1, stdin);

			buffer[strlen(buffer) - 1] = 0;

			if (strcmp(buffer, "exit") == 0) {
				ret = shutdown(sockfd, SHUT_RDWR);
				DIE(ret < 0, "Fail exit\n");
				break;
			} else {

				struct server_message msg;
				const char separator[2] = " ";
				char *word = strtok(buffer, separator);

				strcpy(msg.id, argv[1]);

				//Daca dau subscribe
				if (strcmp(word, "subscribe") == 0) {
					msg.command = 1;
					word = strtok(NULL, separator);
					strcpy(msg.topic, word);
					
					word = strtok(NULL, separator);
					char *sf = strdup(word);
					msg.sf = atoi(sf);
				//Daca dau unsubscribe
				} else if (strcmp(word, "unsubscribe") == 0) {
					msg.command = 0;
					word = strtok(NULL, separator);
					strcpy(msg.topic, word);

				} 
				// Trimit mesaj catre server
				ret = send(sockfd, (char*) &msg, sizeof(msg), 0);
				DIE(ret < 0, "Nimic primit de la server");
			
				if (msg.command == 1) {
					printf("Subscribed to topic.\n");
				} else {
					printf("Unsubscribed from topic.\n");
				}
			}

		  // Daca primesc mesaj de la server
		} else if (FD_ISSET(sockfd, &tmp_fds)) {
			memset(buffer, 0, (sizeof(struct tcp_message) + 1));

			ret = recv(sockfd, buffer, sizeof(struct tcp_message), 0);
			DIE(ret < 0, "Nimic primit de la server");

			struct tcp_message* msg = (struct tcp_message *)malloc(sizeof(struct tcp_message));
			memcpy(msg, &buffer, sizeof(struct tcp_message));

			// Inchid socketul
			if (strncmp(msg->type, "end", 3) == 0) {
				ret = shutdown(sockfd, SHUT_RDWR);
			    DIE(ret < 0, "Fail exit\n");
				exit(EXIT_SUCCESS);
			} else {
				// Afisez informatiile mesajului
				printf("%s:%hu - %s - %s - %s\n", msg->ip, msg->port,
				msg->topic, msg->type, msg->content);
			}
		}
	}

	close(sockfd);

	return 0;
}
