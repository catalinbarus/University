#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc, char *argv[])
{
	msg t;
	int i, res;
	
	printf("[SENDER] Starting.\n");	
	init(HOST, PORT);

	printf("[SENDER]: BDP=%d\n", atoi(argv[1]));

	/* Lungimea sliding window-ului meu este de BDP / MSGSIZE = 12500 / 1400 = 8,92
	   pe care il aproximez la 8. */


	/* Trimit continutul primelor 8 frame-uri (dimensiunea ferestrei) din sliding window */
	for (i = 0; i < 8; i++) {
		
		memset(&t, 0, sizeof(msg));
		sprintf(t.payload, "%d", i);
		t.len = 1;


		/* Determin suma de control pentru size-ul frame-ului meu curent */
		t.checksum = 0;

		for (int j = 0; j < t.len; j++) {
			t.checksum = t.checksum ^ t.payload[j];
		}
		
	    printf("[SENDER]: Frame %d has been sent. Checksum %d sent.\n", i, t.checksum);

		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
	}

	/* Trimit restul de frame-uri pana la COUNT si verific in acelasi timp daca
	   s-a primit ACK */
	for (i = 8; i < COUNT; i++) {
		
		memset(&t, 0, sizeof(msg));
		sprintf(t.payload, "%d", i);

		if(i >= 10) {
			t.len = 2;
		}
		else {
		t.len = 1;
		}
		
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}

		/* Determin suma de control pentru size-ul frame-ului meu curent */
		t.checksum = 0;
		
		for (int j = 0; j < t.len; j++) {
			t.checksum = t.checksum ^ t.payload[j];
		}
		
		
	    printf("[SENDER]: Frame %d has been sent. Checksum %d sent.\n", i, t.checksum);

		sprintf(t.payload, "%d", i);
		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}

	}

	/* Verific daca s-a primit ACK pentru primele 8 frame-uri (dimensiunea ferestrei) trimise */
	for (i = 0; i < 7; i++){
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}
	}

	printf("[SENDER] Job done, all sent.\n");
		
	return 0;
}
