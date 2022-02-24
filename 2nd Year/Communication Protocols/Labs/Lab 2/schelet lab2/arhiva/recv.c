#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){

  msg r;
  init(HOST, PORT);

  /** Deschid fisierul de output (Sau il creez daca nu exista deja)**/
  int open_dest = open("destination.txt", O_WRONLY | O_CREAT, 0644);
  
  /** Pozitionez cursorul la inceputul fisierului de output **/
  lseek(open_dest, 0, SEEK_SET);

  /** Pentru a nu suptaincarca memoria, mai imi iau o variabile de tip msg pentru trimis doar ACK
      cand este cazul **/
  msg accept;
  
  while (1) {

    /** Verific daca mesajul a fost primit **/
    if (recv_message(&r)<0) {
      perror("Receive message");
      return -1;
    }

    /** Daca primesc mesajul de oprire, ies din while**/
    if (strncmp(r.payload, "HALT", 4) == 0)
    {
      break;
    }

    /** Daca mesajul primit este numele fisierului sau dimensiunea acestuia 
        sar peste scrierea in fisier **/
    if (strncmp(r.payload, "test.txt", 8) == 0)
    {
      goto skip_write;
    }

    if (strstr(r.payload, "bytes") != NULL) {
      goto skip_write;
    }

    /** Scriu pachetele in fisier **/
    printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);
    write(open_dest, r.payload, r.len);
  

    skip_write:

    /** Trimit mesajul de acknowledge catre sender **/
    sprintf(accept.payload, "%s", "ACK");
    accept.len = strlen(accept.payload);
    send_message(&accept);
    printf("[recv] ACK successfully sent.\n");
  }

  /** Inchid fisierul dupa transimterea datelor **/

  close(open_dest);

  return 0;
}
