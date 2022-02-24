#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "helpers.h"
#include <stdbool.h>


struct runningGames{
	int idx1;
	int idx2;
	int gameBoard[3][3];
};

bool isInGame(struct runningGames games[], int dest, int size) {

	for (int i = 0; i < size; i++) {
		if (games[i].idx1 == dest || games[i].idx2 == dest) {
			return true;
		}
	}
	return false;

}

int findPlayer(struct runningGames games[], int idx, int size) {


	int found = -1;
	for (int i = 0; i < size; i++) {
		if (games[i].idx1 == idx || games[i].idx2 == idx) {
			found = i;
		}
	}

	return found;
}

bool isWinner(struct runningGames game, int i) {

	if (game.gameBoard[0][0] == game.gameBoard[0][1] && game.gameBoard[0][1] == game.gameBoard[0][2] && game.gameBoard[0][0] == i) {



		return true;

	}

	if (game.gameBoard[1][0] == game.gameBoard[1][1] && game.gameBoard[1][1] == game.gameBoard[1][2] && game.gameBoard[1][0] == i) {

		return true;

	}

	if (game.gameBoard[2][0] == game.gameBoard[2][1] && game.gameBoard[2][1] == game.gameBoard[2][2] && game.gameBoard[2][0] == i) {

		return true;

	}

	if (game.gameBoard[0][0] == game.gameBoard[1][0] && game.gameBoard[1][0] == game.gameBoard[2][0] && game.gameBoard[0][0] == i) {

		return true;

	}

	if (game.gameBoard[0][1] == game.gameBoard[1][1] && game.gameBoard[1][1] == game.gameBoard[2][1] && game.gameBoard[0][1] == i) {

		return true;

	}

	if (game.gameBoard[0][2] == game.gameBoard[1][2] && game.gameBoard[1][2] == game.gameBoard[2][2] && game.gameBoard[0][2] == i) {

		return true;

	}

	if (game.gameBoard[0][0] == game.gameBoard[1][1] && game.gameBoard[1][1] == game.gameBoard[2][2] && game.gameBoard[0][0] == i) {

		return true;

	}

	if (game.gameBoard[0][2] == game.gameBoard[1][1] && game.gameBoard[1][1] == game.gameBoard[2][0] && game.gameBoard[0][2] == i) {

		return true;

	}

	return false;

}



void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;
	int n, i, ret;
	socklen_t clilen;

	struct runningGames games[10];
	int currentGames = 0;


	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds

	if (argc < 2) {
		usage(argv[0]);
	}

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	ret = listen(sockfd, MAX_CLIENTS);
	DIE(ret < 0, "listen");

	// se adauga noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
	FD_SET(0, &read_fds);
	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

	int ok = 0;

	while (ok == 0) {
		tmp_fds = read_fds; 
		
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {

				if (i == 0) {
					
                    // primire comanda stdin
                    memset(buffer, 0, BUFLEN);
                    fgets(buffer, BUFLEN - 1, stdin);

                    if (strncmp(buffer, "exit", 4) == 0) {
                        ok = 1;

                        char exit_msg[5];
                        strcpy(exit_msg, "end");

                        // inchiderea socketilor clientilor activi
                        for (int j = 4; j <= fdmax; j++) {
                            if (FD_ISSET(j, &read_fds)) {
                                send(j, exit_msg, strlen(exit_msg), 0);
                                DIE(ret < 0, "Nu se poate da exit\n"); 
                            }
                        }
                       

                        ret = shutdown(sockfd, SHUT_RDWR);
                        DIE(ret < 0, "Nu pot da exit TCP general\n");
                        break;

                    } 

                } else if (i == sockfd) {
					// a venit o cerere de conexiune pe socketul inactiv (cel cu listen),
					// pe care serverul o accepta
					clilen = sizeof(cli_addr);
					newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
					DIE(newsockfd < 0, "accept");

					// se adauga noul socket intors de accept() la multimea descriptorilor de citire
					FD_SET(newsockfd, &read_fds);
					if (newsockfd > fdmax) { 
						fdmax = newsockfd;
					}

					printf("Noua conexiune de la %s, port %d, socket client %d\n",
							inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
									
					
				} else {
					// s-au primit date pe unul din socketii de client,
					// asa ca serverul trebuie sa le receptioneze
					memset(buffer, 0, BUFLEN);
					n = recv(i, buffer, sizeof(buffer), 0);
					DIE(n < 0, "recv");


					if (n == 0) {
						// conexiunea s-a inchis
						printf("Socket-ul client %d a inchis conexiunea\n", i);
						close(i);
						
						// se scoate din multimea de citire socketul inchis 
						FD_CLR(i, &read_fds);
					} else {
						
					
						//task 3


						int dest = atoi(buffer);

						if (strncmp(buffer + 2, "start", 5) == 0) {

						
							if (i == dest) {
								memset(buffer, 0, BUFLEN);
								strcpy(buffer, "[ERROR] You cannot play by yourself!");
								send(i, buffer, strlen(buffer), 0);

							} else if (isInGame(games, dest, currentGames)) {

								memset(buffer, 0, BUFLEN);
								strcpy(buffer, "[ERROR] Player already in game!");
								send(i, buffer, strlen(buffer), 0);

							} else if(isInGame(games, i, currentGames)){

								memset(buffer, 0, BUFLEN);
								strcpy(buffer, "[ERROR] You are already in game!");
								send(i, buffer, strlen(buffer), 0);

							} else {

								memset(buffer, 0, BUFLEN);
								strcpy(buffer, "[GAME] New game started!");
								send(i, buffer, strlen(buffer), 0);
								send(dest, buffer, strlen(buffer), 0);

								games[currentGames].idx1 = i;
								games[currentGames].idx2 = dest;

								for (int m = 0; m < 3; m++) {
									for (int n = 0; n < 3; n++) {

										games[currentGames].gameBoard[m][n] = -1;
									}
								}

								currentGames++;
							}

						}

						if (strstr(buffer, "move") != NULL) {
							int row = atoi(buffer + 4);
							int collumn = atoi(buffer + 6);

							if (findPlayer(games, i, currentGames) != -1) {
								games[findPlayer(games, i, currentGames)].gameBoard[row - 1][collumn - 1] = i;
							}

							if (isWinner(games[findPlayer(games, i, currentGames)], i) == true) {

								memset(buffer, 0, BUFLEN);
								strcpy(buffer, "You won!");
								send(i, buffer, strlen(buffer), 0);

								int loser;

								if (games[findPlayer(games, i, currentGames)].idx1 == i) {

									loser = games[findPlayer(games, i, currentGames)].idx2;
									
								} else {

									loser = games[findPlayer(games, i, currentGames)].idx1;

								}

								memset(buffer, 0, BUFLEN);
							    strcpy(buffer, "You lost!");
								send(loser, buffer, strlen(buffer), 0);

								if (currentGames > 1) {

									int thisGame = findPlayer(games, i, currentGames);
									games[thisGame].idx1 = games[currentGames - 1].idx1;
									games[thisGame].idx2 = games[currentGames - 1].idx2;

									for (int m = 0; m < 3; m++) {
										for (int n = 0; n < 3; n++) {
											games[thisGame].gameBoard[m][n] = games[currentGames - 1].gameBoard[m][n];
										}
									}
									currentGames--;
									
								} else {
									currentGames--;
								}
							}
						}

						if (strncmp(buffer, "interrupt", 9) == 0) {


							char exit_msg[5];
                        	strcpy(exit_msg, "end");

                        	send(i, exit_msg, strlen(exit_msg), 0);
                            DIE(ret < 0, "Nu se poate da exit\n");

                            int loser;

								if (games[findPlayer(games, i, currentGames)].idx1 == i) {

									loser = games[findPlayer(games, i, currentGames)].idx2;
									
								} else {

									loser = games[findPlayer(games, i, currentGames)].idx1;

								}


                            send(loser, exit_msg, strlen(exit_msg), 0);
                            DIE(ret < 0, "Nu se poate da exit\n");
                            printf("[SERVER] Match interrupted between clients %d and %d.\n", i, loser);

						}


						//int bytes_send = send(dest, buffer + 2, strlen(buffer) - 2, 0);
						//DIE( bytes_send < 0, "error sending buffer");
						//printf ("S-a primit de la clientul de pe socketul %d mesajul: %s\n", i, buffer);
			}
		}
	}
}
}

	close(sockfd);

	return 0;
}
