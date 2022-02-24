#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "helpers.h"

void usage(char *file) {
    fprintf(stderr, "Usage: %s ./server <PORT_DORIT>\n", file);
    exit(0);
}

struct storeClients {
	char id[11];
	int fd;
};

struct Clients {
	int fd;
	struct client client;
};

int main(int argc, char **argv) {


	// Dezactivez bufferingul
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    int ret;
    fd_set read_fds;
    fd_set tmp_fds;
    int fdmax;
    struct sockaddr_in tcp_addr;
    struct sockaddr_in udp_addr;
    struct sockaddr_in client_addr;
    socklen_t tcp_socket_len = sizeof(struct sockaddr);
    char buffer[BUFLEN];
    struct client new_client;

    struct storeClients client_to_socket[1000];

    struct Clients clients[1000];
    int sizeClients = 0;

    // Verific daca s-a dat numarul exact de argumente
    // in linia de comanda
    if (argc < 2 || argc > 2) {
		usage(argv[0]);
	}

	// Verific portul
    int portno = atoi(argv[1]);
	DIE(portno < 1024, "Port gresit");

    // Initializare socketul TCP
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    DIE(tcp_sock < 0, "Socket TCP error");

    // Initializare socketul UDP
    int udp_socket = socket(PF_INET, SOCK_DGRAM, 0);
    DIE(udp_socket < 0, "Socket UDP error");


    // Completare campuri socketi
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(portno);
    tcp_addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(tcp_sock, (struct sockaddr *) &tcp_addr, sizeof(struct sockaddr_in));
	DIE(ret < 0, "Nu se poate face bind cu socket-ul TCP\n");

    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(portno);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(udp_socket, (struct sockaddr *) &udp_addr, sizeof(struct sockaddr_in));
	DIE(ret < 0, "Nu se poate face bind cu socket-ul UDP\n");

    FD_ZERO(&read_fds);
    FD_SET(tcp_sock, &read_fds);
    FD_SET(udp_socket, &read_fds);

    // Verific daca serverul poate primi conexiuni
    // de la clienti
    ret = listen(tcp_sock, MAX_CLIENTS);
	DIE(ret < 0, "Nu se poate face listen");

    FD_SET(0, &read_fds);
    if (udp_socket < tcp_sock) {
        fdmax = tcp_sock;
    } else {
        fdmax = udp_socket;
    }

    int timeToExit = 0;

    // Definesc variabila folosita pentru switch-uri
    int fdCases;
 
    while (timeToExit == 0) {
        bzero(buffer, BUFLEN);
        tmp_fds = read_fds;

        ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "Nu se poate face select");

		for (int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {

				if (i == 0) {
					fdCases = 0;
				} else if (i == tcp_sock) {
					fdCases = 1;
				} else if (i == udp_socket) {
					fdCases = 2;
				} else {
					fdCases = 3;
				}

				// Verific toate cazurile de multiplexare
				switch(fdCases) {

					case 0:
						{
							// Primesc comanda de la stdin
							fgets(buffer, BUFLEN - 1, stdin);

		                    if (strcmp(buffer, "exit\n") == 0) {
		                        timeToExit = 1;

		                        struct tcp_message end_mes = {};
		                        strcpy(end_mes.type, "end");

		                        // Inchid socketii pentru clientii activi
		                        for (int j = 1; j <= fdmax; j++) {
		                            if (FD_ISSET(j, &read_fds)) {

		                            	int verify;
		                                verify = send(j, (char*) &end_mes,
		                                 sizeof(struct tcp_message), 0);
		                                DIE(verify < 0, "Nu se poate da exit\n");
		                                close(j); 
		                            }
		                        }
		                       
		                        // Inchid conexiunea
		                        ret = shutdown(tcp_sock, SHUT_RDWR);
		                        DIE(ret < 0, "Nu pot da exit TCP general\n");
		                        break;

		                    }
						}
						break;

					case 1:
						{
							// Primesc o cerere de conexiune de pe un socket inactiv
		                    // ce va fi acceptata de catre server
		                    int client_sock = accept(i, (struct sockaddr *)&client_addr,
		                    &tcp_socket_len);
		                    DIE(client_sock < 0, "Fail accept");

		                    int value = 1;
		                    ret = setsockopt(client_sock, IPPROTO_TCP, TCP_NODELAY,
		                     (char *)&value, sizeof(int));
		                    DIE(ret < 0, "Fail Neagle");

		                    FD_SET(client_sock, &read_fds);
		                    if (fdmax < client_sock) {
		                        fdmax = client_sock;
		                    }

		                    // Primesc date
		                    ret = recv(client_sock, buffer, BUFLEN - 1, 0);
		                    DIE(ret < 0, "Nu s-a primit nimic de la clientul TCP!");

		                    strcpy(new_client.id, buffer);

		                    struct storeClients* ptr = client_to_socket;
							struct storeClients* endptr = client_to_socket + sizeof(client_to_socket)/sizeof(client_to_socket[0]);

							// Verific daca am gasit clientul in lista de clienti
							int ok = 0;
							while (ptr < endptr) {

								if (strcmp(ptr->id, new_client.id) == 0) {
									ok = 1;
									break;
								}
								ptr++;
							}

							// Daca nu s-a gasit in lista de clienti
							if (ok == 0) {

							    struct Clients client;
							    client.fd = client_sock;
							    client.client = new_client;

							    clients[sizeClients] = client;
							    sizeClients++;

							    printf("New client %s connected from %s:%hu.\n",
		                        new_client.id, inet_ntoa(client_addr.sin_addr),
		                        ntohs(client_addr.sin_port));
							} else {
								// Se reconecteaza un client vechi
								printf("New client %s connected from %s:%hu.\n",
		                        new_client.id, inet_ntoa(client_addr.sin_addr),
		                        ntohs(client_addr.sin_port));
							}

						}
						break;

					case 2:
						{
							// Primesc un mesaj de la un client UDP
							continue;
						}
						break;

					case 3:
						{
							// Primesc o comanda de la un client TCP

		                    ret = recv(i, buffer, BUFLEN - 1, 0);
		                    DIE(ret < 0, "Nu s-a primit nimic de la clientul TCP\n");

		                     if (ret > 0) {

		                     	struct server_message *message = 
		                        (struct server_message *)malloc(sizeof(struct server_message));
					            memcpy(message, &buffer, sizeof(struct server_message));

		                     } else if (ret == 0) {
		                        printf("Client %s disconnected.\n",
		                        clients[i].client.id);
		                        //client_to_socket[clients[i].fd] = -10;
		                        close(i);
		                        FD_CLR(i, &read_fds);

		                        // Recalculez fdmax
		                        int k = fdmax;
		                        while (k > 2) {
		                            if (FD_ISSET(k, &read_fds)) {
		                                fdmax = k;
		                                break;
		                            }
		                            k--;
		                        }
		                    }
						}
						break;
				}
			}

		}
	}

	// Inchid toate conexiunile
	for (int i = 1; i <= fdmax; i++) {
        close(i);
    }

}