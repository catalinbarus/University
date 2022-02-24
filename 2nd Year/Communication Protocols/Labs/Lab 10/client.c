#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    char **cookies;
    char **data_for_login;
    int sockfd;

        
    // Exercitiul 1 
    printf("Prima comanda - GET dummy\n");

    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("34.118.48.238", "/api/v1/dummy", NULL, NULL, 0);
    //afisez detaliile despre cerere
    printf("%s\n", message);
    send_to_server(sockfd, message);

    //retin si afisez mesajul de la server
    response = receive_from_server(sockfd);
    printf("Primit de la sever:\n");
    printf("%s\n", response);

    ///inchid conexiunea
    close_connection(sockfd);


    // Exercitiul 2
    printf("\n");
    printf("A 2-a comanda - POST dummy \n");

    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
    message = compute_post_request("34.118.48.238", "/api/v1/dummy", "application/x-www-form-urlencoded", 
        NULL, 0, NULL, 0);
    //afisez detaliile despre cerere
    printf("%s\n", message);
    send_to_server(sockfd, message);

    //retin si afisez mesajul de la server
    response = receive_from_server(sockfd);
    printf("Primit de la sever:\n");
    printf("%s\n", response);

    //inchid conexiunea
    close_connection(sockfd);


    // Exercitiul 3
    printf("\n");
    printf("A 3-a comanda - Logare server\n");

    //aloc spatiu pentru user si parola
    data_for_login = (char **) malloc(2 * sizeof(char *));

    for(int i = 0; i < 2; i++) {
    	data_for_login[i] = (char *) malloc(30 * sizeof(char));

    	if(i == 0) {
    		strcpy(data_for_login[0], "username=student");
    	} else {
    		strcpy(data_for_login[1], "password=student");
    	}
    } 

    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
    message = compute_post_request("34.118.48.238", "/api/v1/auth/login", "application/x-www-form-urlencoded", 
        	 data_for_login, 2, NULL, 0);
    //afisez detaliile despre cerere
    printf("%s\n", message);
    send_to_server(sockfd, message);

    //retin si afisez mesajul de la server
    response = receive_from_server(sockfd);
    printf("Primit de la sever:\n");
    printf("%s\n", response);

    //inchid conexiunea
    close_connection(sockfd);


    // Exercitiul 4
    printf("\n");
    printf("A 4-a comanda - GET weather key\n");
    cookies = (char **) malloc(sizeof(char *));
    cookies[0] = (char *) malloc(100 * sizeof(char));

  	//!!Observatie : Cookie ul este harcodat, deci s-ar putea sa dea eroare 401 pentru 
  	//aceasta comanda
  	//Pentru rezolvare, se ia cu paste ce se gaseste la campul Set-Cookie de la exercitiul anterior
  	//si se inlocuieste cu acea valoare stringul copiat in cookies[0] 
    strcpy(cookies[0], "connect.sid=s%3AbZAPJaNkSV3ZHOfGhuWc4URhoRtK37n6.5WQQIB916Jv40X3Hai9Lm6gdUm8mg7Lknnal%2BRVgdA4");
    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);

    message = compute_get_request("34.118.48.238", "/api/v1/weather/key", NULL, cookies, 1);

    //afisez detaliile despre cerere
    printf("%s\n", message);
    send_to_server(sockfd, message);

    //retin si afisez mesajul de la server
    response = receive_from_server(sockfd);
    printf("Primit de la sever:\n");
    printf("%s\n", response);

    //inchid conexiunea
    close_connection(sockfd);


    // Exercitiul 5
    printf("\n");
    printf("A 5-a comanda - Delogare server\n");

    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("34.118.48.238", "/api/v1/auth/logout", NULL, NULL, 0);
    
    //afisez detaliile despre cerere
    printf("%s\n", message);
    send_to_server(sockfd, message);

    //retin si afisez mesajul de la server
    response = receive_from_server(sockfd);
    printf("Primit de la sever:\n");
    printf("%s\n", response);

    //inchid conexiunea
    close_connection(sockfd);


    //eliberare memorie
    free(message);
    free(response);
    
    for(int i = 0; i < 2; i++){
    	free(data_for_login[i]);
    }

    free(data_for_login);
    free(cookies[0]);
    free(cookies);
 	

    return 0;
}
