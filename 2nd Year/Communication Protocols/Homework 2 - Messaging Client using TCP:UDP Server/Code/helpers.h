#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <netinet/tcp.h>


#define DIE(assertion, call_description)	\
	do {									\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",	\
					__FILE__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);				\
		}									\
	} while(0)

// Strcutura pentru mesaj TCP
struct tcp_message {
    char ip[16];
    uint16_t port;
    char topic[50];
    char type[10];
    char content[1500];
};

// Strcutura pentru un mesaj de la un client TCP la server
struct server_message {
    int command;
    char topic[50];
    int sf;
    char id[10];
};

// Strcutura pentru mesaj UDP
struct udp_message {
    char topic[50];
    uint8_t type;
    char content[1500];
};

struct client {
    char id[11];
};

#define BUFLEN	    1501 // Dimensiunea maxima datelor
#define MAX_CLIENTS	500	// Numarul maxim posibil de clienti

void usage(char *file);

#endif
