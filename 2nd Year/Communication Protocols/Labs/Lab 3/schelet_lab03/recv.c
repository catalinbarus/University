#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(void)
{
	msg r;
	int i, res;
	
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	
	for (i = 0; i < COUNT; i++) {
		
		res = recv_message(&r);
		if (res < 0) {
			perror("[RECEIVER] Receive error. Exiting.\n");
			return -1;
		}

		r.checksum = 0;
		
		for (int j = 0; j < r.len; j++) {
			r.checksum = r.checksum ^ r.payload[j];
		}

		int finalChesksum = r.checksum;

		msg sum;

		/* Calculez checksum-ul individual de cel transmis din send.c */
		sum.checksum = 0;

		for (int j = 0; j < r.len; j++) {
			sum.checksum = sum.checksum ^ r.payload[j];
		}

		/* Verific daca checksum-ul din send.c difera de cel din recv.c */


		/* Daca checksumurile difera trimit mesajul NACK */
		if (sum.checksum != r.checksum) {
			sprintf(r.payload, "%s", "NACK");
			r.len = strlen(r.payload) + 1;
			res = send_message(&r);
			if (res < 0) {
				perror("[RECEIVER] Send NACK error. Exiting.\n");
				return -1;
			}
		/* Daca checmsum-urile sunt la fel, trimit mesajul ACK */
		} else {

			sprintf(r.payload, "%s", "ACK");
			res = send_message(&r);
			if (res < 0) {
				perror("[RECEIVER] Send ACK error. Exiting.\n");
				return -1;
			}

			printf("[RECEIVER]: ACK %d has been sent. Checksum %d sent\n", i, finalChesksum);
		}
	}

	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
