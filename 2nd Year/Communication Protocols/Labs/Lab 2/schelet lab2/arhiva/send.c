#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

void fatal(char * mesaj_eroare)
{
    perror(mesaj_eroare);
    exit(0);
}

//O implmenetare pentru functia itoa, cea ofificala nu mergea pe masina mea virtuala
void size_itoa(int n, char *str) {

  sprintf(str, "%d", n);
}

int main(int argc, char** argv){
  init(HOST,PORT);
  
  /** Imi iau intante diferite de msg pentru a nu supraincarca memoria **/
  msg t, message_size, message_name;

  char buf[1000000];

  /** Deschid fisierul meu de input **/
  int open_sursa = open("test.txt", O_RDONLY);

  if (open_sursa < 0) {
    fatal("Error: Cannot open file.\n");
  }

  int size = read(open_sursa, buf, sizeof(buf));

  char file_size[1400];

  size_itoa(size, file_size);

  /** Trimit numele fisierului catre receiver **/
  sprintf(message_name.payload, "%s", "test.txt");
  message_name.len = strlen(message_name.payload);
  send_message(&message_name);
  printf("[send] Filename successfully sent.\n");

  /** Trimit dimensiunea fisierului catre receiver **/
  sprintf(message_size.payload, "%s", file_size);
  message_size.len = strlen(message_size.payload);

  /** Fac o concatenare a sirului bytes la size pentru a nu il lua in calcul cand
      voi scrie in fisier **/
  strcat(message_size.payload, " bytes");
  printf("%s\n", message_size.payload);
  send_message(&message_size);
  printf("[send] Filesize successfully sent.\n");

  int frame_size;

  /** Ma mut la inceptul fisierului pentru a citi toate datele din fisier **/
  lseek(open_sursa, 0, SEEK_SET);

  /** Citesc cel mult MAX_LEN bytes in fiecare pachet de date **/
  while ((frame_size = read(open_sursa, t.payload, MAX_LEN)) > 0) {

    t.len = frame_size;
    send_message(&t);

    /** Verific cazul in care nu s-a primit ACK de la receiver **/
    if (recv_message(&t)<0){
      perror("Receive error ...");
      return -1;
    }
    else {
      printf("[send] Got reply with payload: %s\n", t.payload);
    }

  }

  /** Mesaj de oprire, pentru a stii exact cand sa opresc transferul de date **/
  msg halt_message;
  sprintf(halt_message.payload, "%s", "HALT");
  halt_message.len = strlen(halt_message.payload);
  send_message(&halt_message);

  return 0;
}
